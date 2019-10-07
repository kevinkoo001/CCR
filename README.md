# Compiler-assisted Code Randomization (CCR)
## Update News
09/23/19 CCR handles IFUNC cases (R_X86_64_IRELATIVE) in a rela.plt section

04/27/19 CCR supports LLVM 6

04/25/19 CCR supports handwritten (standalone) assembly files. Because LLVM does not
generate any internal MBB/MF structure, we silently skip fixup updates. Technically,
it is difficult to obtain basic block boundaries from the compiler thus CCR excludes
randomization for an object file generated from standalone assembly. Note that LTO also
ignores optimization for such object files.

10/08/18 A randomizer (`prander`) partially supports updates for a `.debug_info` section. 
It is just experimental. A `.debug_line` section has to be updated as well.

07/08/18 CCR internally checks if an object file is compiled from the source code 
that includes assembly (none/inline/standalone). This information will help
randomization at the function level in case of standalone assembly later.

## Overview
**CCR** is a hybrid method for enabling practical and generic code randomization 
based on compiler-rewriter cooperation. CCR currently supports 
rapid cliend-side fine-grained code randomization (at both function level and 
basic block level) at installation time. The main concept behind CCR 
is to augment final executables with *a minimal (pre-defined) set of 
transformation-assisting metadata*. The following table briefly shows the essential 
information that is collected/adjusted at compilation/linking time.

| Metadata | Collected Information | Collection time |
| --- | --- | --- |
| Layout | Section offset to first object | Linking |
|   | Section offset to `main()` function if any | Linking |
|   | Total code size for randomization | Linking |
| Basic Block (BBL) |  BBL size (in bytes) | Linking |
|   | BBL boundary type (BBL, FUN, OBJ) | Compilation |
|   | Fall-through or not | Compilation |
|   | Section name that BBL belongs to | Compilation |
| Fixup | Offset from section base | Linking |
|   | Dereference size | Compilation |
|   | Absolute or relative | Compilation |
|   | Type (`c2c`, `c2d`, `d2c`, `d2d`) | Linking |
|   | Section name that fixup belongs to | Compilation |
| Jump Table | Size of each jump table entry | Compilation |
|   | Number of jump table entries | Compilation |

For more details, plese refer to our  IEEE S&P 2018 
[paper](http://www3.cs.stonybrook.edu/~mikepo/papers/ccr.sp18.pdf).

## How to build CCR
We provide a handy build script (`build.sh`) to automate the entire toolchain installation, which includes:
* modified `LLVM 3.9.0` and `clang` compiler compilation
* `binutils 2.27` and modified gold linker (`ld-new`) compilation
* Google's `protocol buffers 3.1.0` compiler (`protoc`) compilation for metadata serialization/deserialization
* shared object (`shuffleInfo.so`) generation with the [shuffleInfo.proto](./protobuf_def/shuffleInfo.proto) definition
* required packages installation
* python packages (`protobuf` and `pyelftools`) installation
* symbolic link creation to the modified compiler (dubbed as `ccr` and `ccr++`), the gold linker and the randomizer

Once the build script runs successfully, check out the following components.
* CCR C Compiler  : `/usr/local/bin/ccr` symbolically links to `./llvm-3.9.0/build/bin/clang`
* CCR C++ Compiler: `/usr/local/bin/ccr++` symbolically links to `./llvm-3.9.0/build/bin/clang++`
* CCR Gold Linker : `/usr/bin/ld` symbolically links to `./binutils-2.27/gold/ld-new` by default
* Randomizer      : `./randomizer/prander.py` (`prander` is dubbed as a practical randomizer)

Finally, make sure that CCR can properly load `shuffleInfo.so`, located in both `/usr/lib` 
and `/usr/local/lib`. If not, `sudo ldconfig` may help.
```
$ ldd $(readlink -e `which ccr`) | grep shuffleInfo
        shuffleInfo.so => /usr/lib/shuffleInfo.so (0x00007f42b4db9000)
$ ldd $(readlink -e `which ld`) | grep shuffleInfo
        libshuffleInfo.so => /usr/local/lib/libshuffleInfo.so (0x00007f3185af9000)
```

### Notes for CCR build
The build script:
* Requires at least 8GB memory and 30GB HDD space
* Installs `protoc`, `shuffleInfo.so`, and other necessary packages on your system
* Does not install the compiler and linker, but creates symbolic links instead
* Changes the default linker to `ld.gold` at build time, and to `ld-new` at the end

> Note that the script has been tested on Ubuntu 16.04 only (using the default gcc 5.4 and gold 1.11). 
If you have failed to build everything at the first attempt, you may want to change 
the default linker to the system's gold linker before runing the build script again.

### Build with Docker
A Docker script is available for easily testing CCR within a Docker container. 
The following commands show how to install Docker and how to generate the CCR container.
```
$ curl -fsSL https://get.docker.com/ | sudo sh
$ sudo usermod -aG docker [user_id]

$ docker run ubuntu:16.04
Unable to find image 'ubuntu:16.04' locally
16.04: Pulling from library/ubuntu
Digest: sha256:e348fbbea0e0a0e73ab0370de151e7800684445c509d46195aef73e090a49bd6
Status: Downloaded newer image for ubuntu:16.04

$ docker build -t ccr .
... (omitted)
CCR C Compiler   : /usr/local/bin/ccr
CCR C++ Compiler : /usr/local/bin/ccr++
CCR Gold Linker  : /CCR/binutils-2.27/gold/ld-new
CCR Randomizer   : /CCR/randomizer/prander.py

$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ccr                 latest              687322eff8f3        29 minutes ago      30.5GB
ubuntu              16.04               f975c5035748        10 days ago         112MB
```

Once the build has been successful, lunch the Docker image 
to test out CCR.
```
$ docker run --rm -it ccr:latest /bin/bash
root@c1aa9c064785:/CCR# 
```

Or you can just download the images that everything is ready to use.
```
$ docker pull kevinkoo001/ccr:0.8
$ docker run --rm -it kevinkoo001/ccr:0.8 /bin/bash
```

For more information about Docker, visit [here](https://docs.docker.com/)

## Binary Instrumentation with the CCR Toolchain
Once CCR has been successfully deployed, you can test it using the included examples. 
By simply compiling the source code as shown below, you will obtain a 
`ShuffleInfo` (=metadata) message from the linker with the section `.rand`, meaning
the metadata has been updated/generated within the final executable from all object files.

```
$ ccr -o ./examples/funcptr ./examples/funcptr.c
Successfully wrote the ShuffleInfo to the .rand section!
```

If you want to inspect the metadata (layout, jump table, and fixups) in detail, 
use the `-mllvm -debug-only=ccr-metadata` option.
```
$ ccr -o ./examples/funcptr -mllvm -debug-only=ccr-metadata ./examples/funcptr.c
<MF/MBB Layout Summary>
----------------------------------------------------------------------------------
 Layout MF_MBB_ID       MBBSize Align   Fixups  Offset          MFSize  Section
----------------------------------------------------------------------------------
 2      [DF 0_0]        64B     11B     3       0x00000040      64B     (.text)
----------------------------------------------------------------------------------
 4      [DF 1_0]        64B     11B     3       0x00000080      64B     (.text)
----------------------------------------------------------------------------------
 6      [DF 2_0]        64B     11B     3       0x000000c0      64B     (.text)
----------------------------------------------------------------------------------
 8      [DF 3_0]        64B     11B     3       0x00000100      64B     (.text)
----------------------------------------------------------------------------------
 10     [DF 4_0]        48B     14B     2       0x00000130      48B     (.text)
----------------------------------------------------------------------------------
 12     [DF 5_0]        48B     14B     2       0x00000160      48B     (.text)
----------------------------------------------------------------------------------
 14     [DF 6_0]        48B     14B     2       0x00000190      48B     (.text)
----------------------------------------------------------------------------------
 16     [DF 7_0]*       32B     0B      1       0x000001b0      32B     (.text)
 16     [DF 7_1]*       10B     0B      1       0x000001ba      42B     (.text)
 16     [DF 7_2]        39B     0B      3       0x000001e1      81B     (.text)
 16     [DF 7_3]*       28B     0B      2       0x000001fd      109B    (.text)
 16     [DF 7_4]*       10B     0B      1       0x00000207      119B    (.text)
 16     [DF 7_5]        22B     0B      2       0x0000021d      141B    (.text)
 16     [DF 7_6]*       10B     0B      1       0x00000227      151B    (.text)
 16     [DF 7_7]        13B     0B      2       0x00000234      164B    (.text)
 16     [DF 7_8]        32B     0B      3       0x00000254      196B    (.text)
 16     [DF 7_9]*       5B      0B      1       0x00000259      201B    (.text)
 16     [DF 7_10]*      7B      0B      0       0x00000260      208B    (.text)
 16     [DF 7_11]       16B     7B      0       0x00000270      224B    (.text)
----------------------------------------------------------------------------------
 18     [DF 8_0]*       31B     0B      1       0x0000028f      31B     (.text)
 18     [DF 8_12]       14B     0B      1       0x0000029d      45B     (.text)
 18     [DF 8_1]        10B     0B      2       0x000002a7      55B     (.text)
 18     [DF 8_2]        10B     0B      2       0x000002b1      65B     (.text)
 18     [DF 8_3]        10B     0B      2       0x000002bb      75B     (.text)
 18     [DF 8_4]        10B     0B      2       0x000002c5      85B     (.text)
 18     [DF 8_5]        10B     0B      2       0x000002cf      95B     (.text)
 18     [DF 8_6]        10B     0B      2       0x000002d9      105B    (.text)
 18     [DF 8_7]        10B     0B      2       0x000002e3      115B    (.text)
 18     [DF 8_8]        10B     0B      2       0x000002ed      125B    (.text)
 18     [DF 8_9]        10B     0B      2       0x000002f7      135B    (.text)
 18     [DF 8_10]*      5B      0B      1       0x000002fc      140B    (.text)
 18     [DF 8_11]       6B      0B      0       0x00000302      146B    (.text)
----------------------------------------------------------------------------------
Code(B) NOPs(B) MFs     MBBs    Fixups
770     93      9       33      56
        Legend
        (*) FallThrough MBB

<Jump Tables Summary>
[JT@Function#8_0] (Kind: 0, 18 Entries of 8B each)
        [8_1]   0x0000029d
        [8_2]   0x000002a7
        [8_10]  0x000002f7
        [8_10]  0x000002f7
        [8_3]   0x000002b1
        [8_10]  0x000002f7
        [8_4]   0x000002bb
        [8_10]  0x000002f7
        [8_10]  0x000002f7
        [8_5]   0x000002c5
        [8_6]   0x000002cf
        [8_7]   0x000002d9
        [8_10]  0x000002f7
        [8_10]  0x000002f7
        [8_10]  0x000002f7
        [8_10]  0x000002f7
        [8_8]   0x000002e3
        [8_9]   0x000002ed
#JTs    #Entries
1       18

<Fixups Summary>
 - Fixups Info (.text): 56
 - Fixups Info (.rodata): 18
 - Fixups Info (.data): 4
```

> Note that the metadata for the final executable is gzipped to save space 
in the `.rand` section. The metadata can be separately extracted with `objcopy`. 
You can read the metadata with the reader script `shuffleInfoReader.py`, 
which by default extracts the metadata into a `[name].meta.txt` file. 
The script also can reads the metadata from the binary itself if the `.rand` section 
is found.
```
$ readelf -SW ./examples/funcptr | grep rand
  [28] .rand             PROGBITS        0000000000000000 0010d0 000185 00      0   0  1
$ objcopy --dump-section .rand=./examples/funcptr.shuffle.bin.gz ./examples/funcptr
$ gzip -d ./examples/funcptr.shuffle.bin.gz
$ python ./randomizer/shuffleInfoReader.py ./examples/funcptr.shuffle.bin
Found the metadata at ./examples/funcptr.shuffle.bin
        Main Addr Offset   : 0x0020
        Rand Object Offset : 0x0100
        Rand Object Size   : 0x0310
        Total BBLs in .text: 32
Wrote the metadata to ./examples/funcptr.shuffle.bin.meta.txt...
```

The following command generates a program variant with the randomizer, 
`prander.py`, which takes the binary to be transformed as its only argument.
The default option (`-f`) creates a transformed binary at the function level
(Use the `-b` option for basic block level randomization). The name of the variant is 
`[filename]_shuffled` by default. The `-s` option updates all symbols in 
the symbol table (`.symtab`) if the binary has not been stripped. 
For additional options, try the `-h` option for help. In this example, 
the `main()` function has been displaced from 0x400790 to 0x400600.
```
$ python ./randomizer/prander.py -s -b ./examples/funcptr
    ___   ___   __         ___                     _
   / __\ / __\ /__\       / _ \_ __ __ _ _ __   __| | ___ _ __
  / /   / /   / \//_____ / /_)/ '__/ _` | '_ \ / _` |/ _ \ '__|
 / /___/ /___/ _  \_____/ ___/| | | (_| | | | | (_| |  __/ |
 \____/\____/\/ \_/     \/    |_|  \__,_|_| |_|\__,_|\___|_/

 Compiler-assisted Code Randomization: Practical Randomizer
 (In the 39th IEEE Symposium on Security & Privacy 2018)

 [INFO   ] Reading the metadata from the .rand section... (shuffleInfoReader.py:139)
 [INFO   ]       Offset to the object  : 0x100 (shuffleInfoReader.py:140)
 [INFO   ]       Offset to the main()  : 0x20 (shuffleInfoReader.py:141)
 [INFO   ]       Total Emitted Bytes   : 0x0310 (shuffleInfoReader.py:142)
 [INFO   ]       Number of Objects     : 1 (shuffleInfoReader.py:143)
 [INFO   ]       Number of Functions   : 9 (shuffleInfoReader.py:144)
 [INFO   ]       Number of Basic Blocks: 32 (shuffleInfoReader.py:145)
 [INFO   ]       Fixups in .text : 56  (shuffleInfoReader.py:56)
 [INFO   ]       Fixups in .rodata       : 18  (shuffleInfoReader.py:56)
 [INFO   ]       Fixups in .data : 4  (shuffleInfoReader.py:56)
 [INFO   ]       Number of Jump Tables : 1 (shuffleInfoReader.py:173)
 [INFO   ] Building up the layout... (prander.py:43)
                 100% [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]
 [INFO   ] Sanity check for ./examples/funcptr...  (reorderInfo.py:580)
 [INFO   ]       All sanity checks have been PASSED!! (reorderInfo.py:605)
 [INFO   ] Performing reordering (@FUN)... (prander.py:48)
 [INFO   ]       # of Function Constraints: 0 (reorderEngine.py:216)
 [INFO   ] Instrumenting the binary... (prander.py:66)
 [INFO   ]       Processing section [.dynsym] (binaryBuilder.py:694)
                 100% [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]
 [INFO   ]       Processing section [.rela.dyn] (binaryBuilder.py:694)
 [INFO   ]       Processing section [.text] (binaryBuilder.py:694)
                 100% [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]
 [INFO   ]       Processing section [.rodata] (binaryBuilder.py:694)
                 100% [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]
 [INFO   ]       Processing section [.eh_frame] (binaryBuilder.py:694)
 [INFO   ]       Processing section [.eh_frame_hdr] (binaryBuilder.py:694)
 [INFO   ]       Processing section [.init_array] (binaryBuilder.py:694)
 [INFO   ]       Processing section [.data] (binaryBuilder.py:694)
                 100% [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]
 [INFO   ]       Processing section [.symtab] (binaryBuilder.py:694)
                 100% [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]
 [INFO   ] Summary of Binary Instrumentation (report.py:81)
 [INFO   ]       Binary Name       : ./examples/funcptr_shuffled (report.py:82)
 [INFO   ]       Main() Addr       : 0x400790 -> 0x400600 (report.py:85)
 [INFO   ]       Symbol Patches    : 9 (.dynsym|.symtab) (report.py:92)
 [INFO   ]       InitArray Patches : 0 (.init_array) (report.py:93)
 [INFO   ]       CIE / FDE         : 2 / 13 (.eh_frame) (report.py:94)
 [INFO   ]       FDE Patches       : 9 (.eh_frame) (report.py:95)
 [INFO   ]       Pair Patches      : 9 (.eh_frame_hdr) (report.py:96)
 [INFO   ]       Original MD5      : 59f6375f21e9c4884a63a827eac5c301 (report.py:98)
 [INFO   ]       Shuffled MD5      : 320f8f59364c3bd26fabe9f0e43829ee (report.py:99)
 [INFO   ]       Shuffled Size     : 0x000310 (report.py:100)
 [INFO   ]       Metadata size     : 0x000185 (report.py:101)
 [INFO   ]       Total Size        : 0x0024e0 (report.py:102)
 [INFO   ]       File Inc Rate     : 4.298% (report.py:103)
 [INFO   ]       Entropy [LB, UB]  : [10^5.56, 10^15.24] possible versions (report.py:77)
 [INFO   ] Total elapsed time: 0.07 sec(s) (prander.py:77)
 [INFO   ] Success!! The log has been saved to ./examples/funcptr.log (prander.py:162)
```

To verify how functions have been relocated, compare the symbols of the original binary with 
those of the variant. For example, the function `switchcase()` has been relocated 
(`0x400870`->`0x400720`). Note that the intact functions are from CRT (C Run-Time) libraries, 
which are excluded from randomization.
```
$ readelf --syms ./examples/funcptr | grep switchcase
    73: 0000000000400870   146 FUNC    GLOBAL DEFAULT   12 switchcase
    
$ readelf --syms ./examples/funcptr_shuffled | grep switchcase
    73: 0000000000400720   146 FUNC    GLOBAL DEFAULT   12 switchcase
```

The following shows the disassembly of the `switchcase()` function using [radare2](https://rada.re/r/). 
The operand of every jump/call instruction has been updated accordingly so that 
the original semantics of the program are preserved.
```
[0x00400870 22% 335 funcptr]> pd $r @ sym.switchcase
/ (fcn) sym.switchcase 45
|   sym.switchcase ();
|           ; var int local_14h @ rbp-0x14
|           ; var int local_10h @ rbp-0x10
|           ; var int local_4h @ rbp-0x4
|              ; CALL XREF from 0x0040082a (main)
|           0x00400870      55             push rbp
|           0x00400871      4889e5         mov rbp, rsp
|           0x00400874      4883ec20       sub rsp, 0x20
|           0x00400878      897dfc         mov dword [local_4h], edi
|           0x0040087b      ffcf           dec edi
|           0x0040087d      89f8           mov eax, edi
|           0x0040087f      83ef11         sub edi, 0x11
|           0x00400882      488945f0       mov qword [local_10h], rax
|           0x00400886      897dec         mov dword [local_14h], edi
|       ,=< 0x00400889      0f8768000000   ja 0x4008f7                 ;[1]
|       |   0x0040088f      488b45f0       mov rax, qword [local_10h]
|       |   0x00400893      488b0cc59809.  mov rcx, qword [rax*8 + 0x400998]    ; [0x400998:8]=0x40089d
\       |   0x0040089b      ffe1           jmp rcx
        |   0x0040089d      e85efeffff     call sym.f1                 ;[2]
       ,==< 0x004008a2      e955000000     jmp 0x4008fc                ;[3]
       ||   0x004008a7      e884feffff     call sym.f2                 ;[4]
      ,===< 0x004008ac      e94b000000     jmp 0x4008fc                ;[3]
      |||   0x004008b1      e84afeffff     call sym.f1                 ;[2]
     ,====< 0x004008b6      e941000000     jmp 0x4008fc                ;[3]
     ||||   0x004008bb      e870feffff     call sym.f2                 ;[4]
    ,=====< 0x004008c0      e937000000     jmp 0x4008fc                ;[3]
    |||||   0x004008c5      e836feffff     call sym.f1                 ;[2]
   ,======< 0x004008ca      e92d000000     jmp 0x4008fc                ;[3]
   ||||||   0x004008cf      e85cfeffff     call sym.f2                 ;[4]
  ,=======< 0x004008d4      e923000000     jmp 0x4008fc                ;[3]
  |||||||   0x004008d9      e852feffff     call sym.f2                 ;[4]
  ========< 0x004008de      e919000000     jmp 0x4008fc                ;[3]
  |||||||   0x004008e3      e818feffff     call sym.f1                 ;[2]
  ========< 0x004008e8      e90f000000     jmp 0x4008fc                ;[3]
  |||||||   0x004008ed      e80efeffff     call sym.f1                 ;[2]
  ========< 0x004008f2      e905000000     jmp 0x4008fc                ;[3]
  |||||||      ; JMP XREF from 0x00400889 (sym.switchcase)
  ||||||`-> 0x004008f7      e864feffff     call sym.f3                 ;[5]
  ||||||       ; XREFS: JMP 0x004008a2  JMP 0x004008ac  JMP 0x004008b6  JMP 0x004008c0  JMP 0x004008ca
  ||||||       ; XREFS: JMP 0x004008d4  JMP 0x004008de  JMP 0x004008e8  JMP 0x004008f2
  ``````--> 0x004008fc      4883c420       add rsp, 0x20
            0x00400900      5d             pop rbp
            0x00400901      c3             ret
            0x00400902      66666666662e.  nop word cs:[rax + rax]
            
[0x00400720 19% 396 funcptr_shuffled]> pd $r @ sym.switchcase
/ (fcn) sym.switchcase 45
|   sym.switchcase ();
|           ; var int local_14h @ rbp-0x14
|           ; var int local_10h @ rbp-0x10
|           ; var int local_4h @ rbp-0x4
|              ; CALL XREF from 0x004006da (main)
|           0x00400720      55             push rbp
|           0x00400721      4889e5         mov rbp, rsp
|           0x00400724      4883ec20       sub rsp, 0x20
|           0x00400728      897dfc         mov dword [local_4h], edi
|           0x0040072b      ffcf           dec edi
|           0x0040072d      89f8           mov eax, edi
|           0x0040072f      83ef11         sub edi, 0x11
|           0x00400732      488945f0       mov qword [local_10h], rax
|           0x00400736      897dec         mov dword [local_14h], edi
|       ,=< 0x00400739      0f8768000000   ja 0x4007a7                 ;[1]
|       |   0x0040073f      488b45f0       mov rax, qword [local_10h]
|       |   0x00400743      488b0cc59809.  mov rcx, qword [rax*8 + 0x400998]    ; [0x400998:8]=0x40074d
\       |   0x0040074b      ffe1           jmp rcx
        |   0x0040074d      e84e010000     call sym.f1                 ;[2]
       ,==< 0x00400752      e955000000     jmp 0x4007ac                ;[3]
       ||   0x00400757      e8a4000000     call sym.f2                 ;[4]
      ,===< 0x0040075c      e94b000000     jmp 0x4007ac                ;[3]
      |||   0x00400761      e83a010000     call sym.f1                 ;[2]
     ,====< 0x00400766      e941000000     jmp 0x4007ac                ;[3]
     ||||   0x0040076b      e890000000     call sym.f2                 ;[4]
    ,=====< 0x00400770      e937000000     jmp 0x4007ac                ;[3]
    |||||   0x00400775      e826010000     call sym.f1                 ;[2]
   ,======< 0x0040077a      e92d000000     jmp 0x4007ac                ;[3]
   ||||||   0x0040077f      e87c000000     call sym.f2                 ;[4]
  ,=======< 0x00400784      e923000000     jmp 0x4007ac                ;[3]
  |||||||   0x00400789      e872000000     call sym.f2                 ;[4]
  ========< 0x0040078e      e919000000     jmp 0x4007ac                ;[3]
  |||||||   0x00400793      e808010000     call sym.f1                 ;[2]
  ========< 0x00400798      e90f000000     jmp 0x4007ac                ;[3]
  |||||||   0x0040079d      e8fe000000     call sym.f1                 ;[2]
  ========< 0x004007a2      e905000000     jmp 0x4007ac                ;[3]
  |||||||      ; JMP XREF from 0x00400739 (sym.switchcase)
  ||||||`-> 0x004007a7      e884000000     call sym.f3                 ;[5]
  ||||||       ; XREFS: JMP 0x00400752  JMP 0x0040075c  JMP 0x00400766  JMP 0x00400770  JMP 0x0040077a
  ||||||       ; XREFS: JMP 0x00400784  JMP 0x0040078e  JMP 0x00400798  JMP 0x004007a2
  ``````--> 0x004007ac      4883c420       add rsp, 0x20
            0x004007b0      5d             pop rbp
            0x004007b1      c3             ret
            0x004007b2      66666666662e.  nop word cs:[rax + rax]
```

In general, you may want to set the default compilers as `ccr` and `ccr++` when running the `configure` script  to generate the `Makefile`. The CCR prototype supports most existing binary features when generating hardened variants, including (but not limited to) position independent code (PIC), shared objects, exception handling, lazy binding, link time optimization (LTO), and control flow integrity (CFI).

## Debian Packages using the CCR Toolchain
To demonstrate how the master executable can be transparently transformed at installation time,
we have modified the debian package source directory to trigger the randomizer.
Either of the `apt-get install` or `dpkg -i` commands trigger code randomization as part of the installation process.
For more details, see [here](./examples-dpkg/README.md).

## Pitfalls
* The current prototype only supports  ELF binaries on the x86_64 platform.
* Too many basic blocks and fixups (100,000 or more) may impact the rewriting time.
* Symbol updates are experimental and may be slow, so we do not recommend using the `-s` option for large binaries.
* Technically the latest `protobuf` should work, but different versions may result in unforeseen collisions.

## Known Limitations
The current CCR prototype has the following limitations.
* No support for self-modifying code.
* No support for debugging-relevant sections (i.e., .debug_*).
* No support for basic block reordering at the presence of custom exception handling (`.eh_frame` and `.eh_frame_hdr`) (See the appendix of the paper).
* No support for one of the six CFI protection mechanisms of LLVM, which is `cfi-icall` (See the appendix of the paper).
* Although there is support for inline assembly (i.e., `__asm` directive) and full assembly source code (`*.s` files), it works only for function level randomization. More engineering effort is required for basic block randomization due to the various styles of writing assembly files. Randomization at the basic block level is still feasible by excluding non-compatible object files (written in assembly).

## Citation
If your research employs our CCR prototype, please cite the following paper:
```
@INPROCEEDINGS{ccr,
  author = {Hyungjoon Koo and Yaohui Chen and Long Lu and Vasileios~P. Kemerlis and Michalis Polychronakis},
  title = {Compiler-assisted Code Randomization},
  booktitle = {Proceedings of the 39th IEEE Symposium on Security \& Privacy (S\&P)},
  pages = {472--488},
  month = {May},
  year = {2018},
  location = {San Francisco, CA}
}
```
