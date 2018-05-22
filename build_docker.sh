#!/bin/bash

: '
################################################################
#  Compiler-assisted Code Randomization - Build Script         #
#   (In the 39th IEEE Symposium on Security & Privacy 2018)    #
#                                                              #
#  Author: Hyungjoon Koo <hykoo@cs.stonybrook.edu>             #
#          Computer Science@Stony Brook University             #
#                                                              #
#  This file can be distributed under the MIT License.         #
#  See the LICENSE.TXT for details.                            #
################################################################
'

# Define source directories to compile
TOOLCHAIN_ROOT=`pwd`
RANDOMIZER_DIR="$TOOLCHAIN_ROOT/randomizer"
PROTODEF_DIR="$TOOLCHAIN_ROOT/protobuf_def"
PROTOBUF_DIR="$TOOLCHAIN_ROOT/protobuf-3.1.0"
BINUTILS_DIR="$TOOLCHAIN_ROOT/binutils-2.27"
NEWGOLD_DIR="$BINUTILS_DIR/gold"
LLVM_DIR="$TOOLCHAIN_ROOT/llvm-3.9.0"
CCR="/usr/local/bin/ccr"
CCR_PLUS="/usr/local/bin/ccr++"

function directory_check {
   if [ -d $2 ]
   then
      echo "$1 Directory: $2"
   else
      echo "Cannot find the directory: $2 (Terminating...)"
      exit 1
   fi
}

echo
echo =============================================
echo "A. Checking environment settings..."
echo =============================================
echo

directory_check ToolchainRoot $TOOLCHAIN_ROOT
directory_check Randomizer $RANDOMIZER_DIR
directory_check ProtoDef $PROTODEF_DIR
directory_check Protobuf $PROTOBUF_DIR
directory_check Binutils $BINUTILS_DIR
directory_check Gold $NEWGOLD_DIR
directory_check LLVM $LLVM_DIR

# Check the number of CPUs
NO_CPUS=$(expr `cat /proc/cpuinfo | awk '/^processor/{print $3}' | tail -1` + 1)
echo "Number of CPUs:" $NO_CPUS
 
# Check the python version
echo -ne "Default Python: "
$(which python) --version 

# Check the default system linker
echo -ne "Default Linker: "
if [ -h $(which ld) ]
then
   LDLN=$(which ld)
   LD=$(readlink -e $LDLN)
   echo $LD
fi

# Change the bfd linker to gold as default
if [[ $LD =~ .*bfd.* ]]
then
   GOLD=$(echo $LD | sed -e 's/bfd/gold/g')
   if [ -f $GOLD ]
   then
      mv $LDLN $LDLN.bfd
      ln -s $GOLD $LDLN
      echo "Changed Linker:" $GOLD
   else
      echo "Cannot find a gold linker (Terminating...)"
      exit 1
   fi
fi

function compile_protobuf {
   cd $1
   ./configure
   #make clean
   make -j$2
   make install
   ldconfig

   PROTOC=`which protoc`
   if [ -f $PROTOC ]
   then
      echo "Installed protobuf: " $PROTOC
   else
      echo "Cannot find a protobuf compiler (Terminating...)"
      exit 1
   fi
}

function compile_binutils {
   cd $1
   ./configure 
   # make clean
   make -j$2
}

function compile_gold {
   cd $1
   ./configure --enable-gold --enable-plugins=yes
   #make clean
   make -j$2
} 

echo
echo =============================================
echo "B. Compiling Google's Protocol Buffers..."
echo =============================================
echo
compile_protobuf $PROTOBUF_DIR $NO_CPUS

echo
echo =============================================
echo "C. Generating the shuffleInfo.so..."
echo =============================================
echo

PROTO="shuffleInfo.proto"
SHUFFLEINFO="shuffleInfo.so"
CC_HDR="shuffleInfo.pb.h"
PROTO_C="shuffleInfo.pb.cc"
PROTO_PY="shuffleInfo_pb2.py"

LIB1="/usr/lib"
LIB2="/usr/local/lib"

cd $PROTODEF_DIR
protoc --proto_path=$PROTODEF_DIR --cpp_out=. $PROTODEF_DIR/$PROTO
protoc --proto_path=$PROTODEF_DIR --python_out=. $PROTODEF_DIR/$PROTO
c++ -fPIC -shared $PROTODEF_DIR/$PROTO_C -o $PROTODEF_DIR/$SHUFFLEINFO `pkg-config --cflags --libs protobuf`

USER=`whoami`
chmod 755 $PROTODEF_DIR/$SHUFFLEINFO
chown $USER:$USER $PROTODEF_DIR/$SHUFFLEINFO $PROTODEF_DIR/$PROTO_C $PROTODEF_DIR/$PROTO_PY

# Deploy the shared object
cp $PROTODEF_DIR/$SHUFFLEINFO $LIB1/$SHUFFLEINFO
cp $PROTODEF_DIR/$SHUFFLEINFO $LIB2/$SHUFFLEINFO
cp $PROTODEF_DIR/$SHUFFLEINFO $LIB2/lib$SHUFFLEINFO

echo
echo =============================================
echo "D. Compiling the binutils and gold linker..."
echo =============================================
echo
compile_binutils $BINUTILS_DIR $NO_CPUS

# Deploy the shared object for gold
cp $PROTODEF_DIR/$CC_HDR $NEWGOLD_DIR/$CC_HDR
cp $PROTODEF_DIR/$SHUFFLEINFO $NEWGOLD_DIR/lib$SHUFFLEINFO

compile_gold $NEWGOLD_DIR $NO_CPUS

echo
echo =============================================
echo "E. Compiling LLVM 3.9.0..."
echo =============================================
echo

cd $LLVM_DIR
mkdir $LLVM_DIR/build
cd $LLVM_DIR/build
cmake -DCMAKE_EXE_LINKER_FLAGS_DEBUG="-I/usr/local/include -L/usr/local/lib -lprotobuf -lpthread" -DLLVM_ENABLE_RTTI=ON -DLLVM_BINUTILS_INCDIR=$BINUTILS_DIR/include ..

MODIFIED_LINK1="$LLVM_DIR/build/lib/MC/CMakeFiles/LLVMMC.dir/link.txt"
MODIFIED_LINK2="$LLVM_DIR/build/tools/lto/CMakeFiles/LTO.dir/link.txt"
MODIFIED_LINK3="$LLVM_DIR/build/tools/clang/tools/libclang/CMakeFiles/libclang.dir/link.txt"
MODIFIED_LINK4="$LLVM_DIR/build/tools/clang/tools/c-index-test/CMakeFiles/c-index-test.dir/link.txt"

# Adding /usr/lib/shuffleInfo.so
sed -i '/LLVMMC.dir/s/$/\ \/usr\/lib\/shuffleInfo\.so/' $MODIFIED_LINK1

# Adding -I/usr/local/include -L/usr/local/lib -lprotobuf
sed -i 's/$/\-I\/usr\/local\/include\ \-L\/usr\/local\/lib\ \-lprotobuf/' $MODIFIED_LINK2 
sed -i 's/$/\-I\/usr\/local\/include\ \-L\/usr\/local\/lib\ \-lprotobuf/' $MODIFIED_LINK3 
sed -i 's/$/\-I\/usr\/local\/include\ \-L\/usr\/local\/lib\ \-lprotobuf/' $MODIFIED_LINK4 

# Deploy the protobuf for LLVM 
cp $PROTODEF_DIR/$CC_HDR $LLVM_DIR/include/llvm/Support/$CC_HDR
make -j$NO_CPUS
cp $LLVM_DIR/build/lib/LLVMgold.so /usr/lib/

echo
echo =============================================
echo "F. Configuring the Randomizer..."
echo =============================================
echo

# Install protobuf and pyelftools for the randomizer 
cp $PROTODEF_DIR/$PROTO_PY $RANDOMIZER_DIR/$PROTO_PY

echo
echo =============================================
echo "G. Finalizing the CCR Toolchain..."
echo =============================================
echo

# Generate the links to support toolchains for randomization framework in the system
CCR_COMPILER="$LLVM_DIR/build/bin/clang"
CCR_PLUS_COMPILER="$LLVM_DIR/build/bin/clang++"
CCR_LINKER="$NEWGOLD_DIR/ld-new"

ldconfig

if [ -f $CCR_COMPILER ]; then
   ln -s $CCR_COMPILER $CCR
   ln -s $CCR_COMPILER $CCR_PLUS
   echo "CCR C Compiler   : $CCR"
   echo "CCR C++ Compiler : $CCR_PLUS"
else
   echo "$CCR_COMPILER has been failed to be built!"
fi


if [ -f $CCR_LINKER ]; then
   mv /usr/bin/ld /usr/bin/ld.gold
   ln -s $CCR_LINKER /usr/bin/ld
   echo "CCR Gold Linker  : $CCR_LINKER"
else
   echo "$CCR_LINKER has been failed to be built!"
fi

echo "CCR Randomizer   : $RANDOMIZER_DIR/prander.py"
echo "Done...!"
echo