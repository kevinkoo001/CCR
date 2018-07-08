################################################################
#  Compiler-assisted Code Randomization: Practical Randomizer  #
#   (In the 39th IEEE Symposium on Security & Privacy 2018)    #
#                                                              #
#  Author: Hyungjoon Koo <hykoo@cs.stonybrook.edu>             #
#          Computer Science@Stony Brook University             #
#                                                              #
#  This file can be distributed under the MIT License.         #
#  See the LICENSE.TXT for details.                            #
################################################################

import os, sys
import logging
import util
import struct
import unit
import constants as C
from util import hexPrint as HP
from elfParser import ELFParser

'''
Brief overview of classes
    BinaryInfo  : the location of the object for reordering
    Objects     : object sizes and function counts in each object
    Functions   : function sizes and basic block counts in each function
    BasicBlocks : basic block sizes and fixup counts in each basic block
    Fixups      : fixup offsets from each function, sizes for de-referencing and kinds
'''

class BinaryInfo():
    def __init__(self, BinInfo):
        '''
        Holds the given binary information including:
            Base address
            Entry point
            [Required] the location of the object for reordering
        :param BinInfo:
        '''

        self.elfParser = ELFParser(BinInfo['bin_path'])
        self.entryPoint = self.elfParser.elf.header['e_entry']
        self.base = self.elfParser.elf.get_segment(2)['p_vaddr']

        self.reorderObjStartFromText = BinInfo['reorderObjStartFromText']
        self.mainAddrOffsetFromText = BinInfo['mainAddrOffsetFromText']
        self.reorderedObjSize = BinInfo['reorderedObjSize']

        # Whether or not pic/pie, executable should have an entry point
        if self.entryPoint > 0:
            self.baseOffsetFromFile = self._getTextSecVA() - self.base
        # Only shared object does not have one
        else:
            self.baseOffsetFromFile = self._getTextSecVA()
            self.base = 0x0

        self.Objects = []   # Objects that consist of the binary
        self.fixupCnt = 0

    def _getTextSecVA(self):
        for s in range(1, self.elfParser.elf.num_sections()):
            if self.elfParser.elf.get_section(s).name == C.SEC_TEXT:
                return self.elfParser.elf.get_section(s)['sh_addr']

    def getBinary(self):
        return self

    def getElfParser(self):
        return self.elfParser

    def getReorderObjOff(self):
        return self.reorderObjStartFromText

    def isInReorderRange(self, addr):
        s = self._getTextSecVA() + self.reorderObjStartFromText
        return s <= addr < s + self.reorderedObjSize

    def __repr__(self):
        return '<Binary>' \
                 '\n\t [Parsed] Base Address  : 0x%08x' \
                 '\n\t [Parsed] Entry Point   : 0x%08x' \
                 '\n\t [Linker] Main Offset   : 0x%08x' \
                 '\n\t [Linker] Reorder Start : 0x%08x' \
                 '\n\t OffsetFromBase   : 0x%08x' \
               % (self.base, self.entryPoint, self.mainAddrOffsetFromText,
                  self.reorderObjStartFromText, self.baseOffsetFromFile)

class Objects(BinaryInfo):
    """
    The Objects class inherits BinaryInfo class
    """
    def __init__(self, bar, BinInfo, ObjInfo):
        BinaryInfo.__init__(self, BinInfo)
        self.objectLayout = []
        self.lookupByVA = dict()

        # Unpack the object information
        self.objSize, self.objFuncCnt, self.srcKind = ObjInfo
        self.numObjects = len(self.objSize)
        self.numFuncs = sum(self.objFuncCnt)
        #if len(self.srcKind) > 0:
        #    assert (self.numObjects == len(self.srcKind))

        self.objOffset = util.getOffset(self.objSize)
        self.objOffsetFromSection = util.computeRelaOffset(self.objOffset, self.reorderObjStartFromText)
        self.objOffsetFromBase = util.computeRelaOffset(self.objOffsetFromSection, self.baseOffsetFromFile)
        self.objVA = util.computeRelaOffset(self.objOffsetFromBase, self.base)

        self.generateObjectList(bar)
        
    def generateObjectList(self, bar):
        prevObj = None
        for idx in range(self.numObjects):
            OBJ = unit.Object()
            OBJ.idx = idx
            OBJ.size = self.objSize[idx]
            OBJ.VA = self.objVA[idx]
            #if len(self.srcKind) > 0:
            #    OBJ.srcKind = self.srcKind[idx]

            if prevObj:
                prevObj.next = OBJ
                OBJ.prev = prevObj

            # Assign the parent of the object and add it to the root binary
            OBJ.parent = self.getBinary()
            OBJ.parent.Objects.append(OBJ)

            OBJ.offsetFromSection = self.objOffsetFromSection[idx]
            OBJ.offsetFromBase = self.objOffsetFromBase[idx]

            self.objectLayout.append(OBJ)
            self.lookupByVA[OBJ.VA] = OBJ
            prevObj = OBJ
            bar += 1

    def getObjects(self):
        return self.objectLayout

    def getObject(self, idx):
        return self.objectLayout[idx]

    def getObjByVA(self, va):
        return self.lookupByVA[va]

    def __repr__(self):
        BinInfo = BinaryInfo.__repr__(self)
        return BinInfo + '\n<%d Objects>' \
                       '\n\t [Compiler] Sizes         : %s' \
                       '\n\t [Compiler] Funcs per obj : %s' \
                       '\n\t offsetFromSection        : %s' \
                       '\n\t offsetFromBase           : %s' \
                       '\n\t VirtualAddress           : %s' \
                       % (self.numObjects, self.objSize, self.objFuncCnt, HP(self.objOffsetFromSection),
                          HP(self.objOffsetFromSection), HP(self.objVA))
    
class Functions(Objects):
    """
    The Functions class inherits Objects class
    """
    def __init__(self, bar, BinInfo, ObjInfo, FuncInfo):
        Objects.__init__(self, bar, BinInfo, ObjInfo)
        self.FunctionLayout = []
        self.lookupByVA = dict()
    
        # Unpack the function information
        self.funcSize, self.funcBBCnt = FuncInfo
        self.numBBs = sum(self.funcBBCnt)
        self.numFunctions = len(self.funcSize)

        # Func X belongs to Obj Y; dict(X:Y)
        self.func2Obj = util.buildLookupTbl(self.objFuncCnt)

        self.funcOffset = util.getOffset(self.funcSize)
        self.funcOffsetFromObj = util.getOffsetFrom(self.objFuncCnt, self.funcSize)
        self.funcOffsetFromSection = util.computeRelaOffset(self.funcOffset, self.reorderObjStartFromText)
        self.BBOffsetFromBase = util.computeRelaOffset(self.funcOffsetFromSection, self.baseOffsetFromFile)
        self.funcVA = util.computeRelaOffset(self.BBOffsetFromBase, self.base)

        self.generateFunctionList(bar)

    def generateFunctionList(self, bar):
        prevFun = None
        for idx in range(self.numFunctions):
            F = unit.Function()
            F.idx = idx
            F.size = self.funcSize[idx]
            F.VA = self.funcVA[idx]

            if prevFun:
                prevFun.next = F
                F.prev = prevFun

            # Assign the parent of the Function and add it to the list
            F.parent = self.getObject(self.func2Obj[idx])
            F.parent.Functions.append(F)

            F.offsetFromObj = self.funcOffsetFromObj[idx]
            F.offsetFromSection = self.funcOffsetFromSection[idx]
            F.offsetFromBase = self.BBOffsetFromBase[idx]

            self.FunctionLayout.append(F)
            self.lookupByVA[F.VA] = F
            prevFun = F
            bar += 1

    def getFunctions(self):
        return self.FunctionLayout

    def getFunction(self, idx):
        return self.FunctionLayout[idx]

    def getFunByVA(self, va):
        return self.lookupByVA[va]

    def __repr__(self):
        objInfo = Objects.__repr__(self)
        return objInfo + '\n<%d Functions>' \
                         '\n\t [Compiler] Sizes        : %s' \
                         '\n\t [Compiler] BBs per func : %s' \
                         '\n\t offsetFromObj           : %s' \
                         '\n\t offsetFromSection       : %s ' \
                         '\n\t offsetFromBase          : %s ' \
                         '\n\t VirtualAddress          : %s' \
                         % (self.numFuncs, self.funcBBCnt, HP(self.funcSize),
                            HP(self.funcOffsetFromObj), HP(self.funcOffsetFromSection),
                            HP(self.funcOffsetFromSection), HP(self.funcVA))

class BasicBlocks(Functions):
    """
    The BasicBlocks class inherits Functions class
    """
    def __init__(self, bar, BinInfo, ObjInfo, FuncInfo, BBInfo):
        Functions.__init__(self, bar, BinInfo, ObjInfo, FuncInfo)
        self.BasicBlockLayout = []
        self.lookupByVA = dict()

        # Unpack the basic block information
        self.BBSize, self.BBFixupCnt, self.BBFallThrough = BBInfo
        self.numFixups = sum(self.BBFixupCnt)
        self.numBasicBlocks = len(self.BBSize)

        # BB X belongs to Func Y; dict(X:Y)
        self.BB2Func = util.buildLookupTbl(self.funcBBCnt)

        self.BBOffset = util.getOffset(self.BBSize)
        self.BBOffsetFromFunc = util.getOffsetFrom(self.funcBBCnt, self.BBSize)
        self.BBOffsetFromObj = util.getOffsetFrom(self._getObjBBCnt(), self.BBSize)
        self.BBOffsetFromSection = util.computeRelaOffset(self.BBOffset, self.reorderObjStartFromText)
        self.BBOffsetFromBase = util.computeRelaOffset(self.BBOffsetFromSection, self.baseOffsetFromFile)
        self.BBVA = util.computeRelaOffset(self.BBOffsetFromBase, self.base)

        self.generateBasicBlockList(bar)

    def generateBasicBlockList(self, bar):
        prevBBL = None
        for idx in range(self.numBasicBlocks):
            BBL = unit.BasicBlock()
            BBL.idx = idx
            BBL.size = self.BBSize[idx]
            BBL.hasFallThrough = self.BBFallThrough[idx]
            BBL.VA = self.BBVA[idx]

            if prevBBL:
                prevBBL.next = BBL
                BBL.prev = prevBBL

            # Assign the parent of the BB and add it to the list
            BBL.parent = self.getFunction(self.BB2Func[idx])
            BBL.parent.BasicBlocks.append(BBL)

            BBL.offsetFromFunc = self.BBOffsetFromFunc[idx]
            BBL.offsetFromSection = self.BBOffsetFromSection[idx]
            BBL.offsetFromBase = self.BBOffsetFromBase[idx]

            # As fixup might not be in BBL, all ctrs have to be taken care of here
            BBL.fixupCnt = self.BBFixupCnt[idx]
            BBL.parent.fixupCnt += BBL.fixupCnt               # Update function ctr
            BBL.parent.parent.fixupCnt += BBL.fixupCnt        # Update object ctr
            BBL.parent.parent.parent.fixupCnt += BBL.fixupCnt # Update binary ctr

            self.BasicBlockLayout.append(BBL)
            self.lookupByVA[BBL.VA] = BBL
            prevBBL = BBL
            bar += 1

    def getBasicBlocks(self):
        return self.BasicBlockLayout

    def getBasicBlock(self, idx):
        return self.BasicBlockLayout[idx]

    def getBBlByVA(self, va):
        if va in self.lookupByVA:
            return self.lookupByVA[va]

    def show(self, level=1):
        for bbl in self.BasicBlockLayout:
            print bbl
            if level > 1:
                for fixup in bbl.Fixups:
                    print '\t', fixup

    def _getObjBBCnt(self):
        ''' Compute how many BBs in a single object to move forward '''
        objBBCnt = list()
        funcIdx = 0
        for funcCnt in self.objFuncCnt:
            BBCnt = 0
            for _ in range(funcCnt):
                BBCnt += self.funcBBCnt[funcIdx]
                funcIdx += 1
            objBBCnt.append(BBCnt)
        return objBBCnt

    def __repr__(self):
        funcInfo = Functions.__repr__(self)
        return funcInfo + '\n<%d BasicBlocks>' \
                          '\n\t [Compiler] Sizes         : %s' \
                          '\n\t [Compiler] Fixups per BB : %s' \
                          '\n\t offsetFromFunc           : %s ' \
                          '\n\t offsetFromObj            : %s ' \
                          '\n\t offsetFromSection        : %s ' \
                          '\n\t offsetFromBase           : %s ' \
                          '\n\t VirtualAddress           : %s' \
                          % (self.numBBs, self.BBFixupCnt, HP(self.BBSize), HP(self.BBOffsetFromFunc),
                             HP(self.BBOffsetFromObj), HP(self.BBOffsetFromSection),
                             HP(self.BBOffsetFromBase), HP(self.BBVA))

class Fixups():
    """
    The Fixups class that contains a variety of fixups
    """
    def __init__(self, FixupData, constructInfo, sectionName, bar):
        self.FixupData = FixupData
        self.FixupsLayout = []
        # The following layout is only defined when special section has been found in .text
        self.FixupsLayoutSpecial = []
        # The following layout is only defined in CFI-enabled binary with LLVM (-cfi-icall)
        self.FixupsLayoutOrphan = []

        self.CI = constructInfo
        self.elfParser = self.CI.getElfParser()
        self.sectionName = sectionName
        self.secOff = self.elfParser.getSectionVA(self.sectionName)

        if sectionName == C.SEC_TEXT:
            self.Fixup2BB = util.buildLookupTbl(self.CI.BBFixupCnt)

        self._generateFixupList(bar)
        self.numFixups = len(self.FixupsLayout)
        self.numFixupsSpecial = len(self.FixupsLayoutSpecial)
        self._processRefs()

    def hasSpecialSection(self):
        """  Check if the section contains any fixup in a spectial section """
        return self.sectionName == C.SEC_TEXT and len(self.FixupsLayoutSpecial) > 0

    def hasOrphanFixups(self):
        """  Check if the section contains any orphan fixup """
        return self.sectionName == C.SEC_TEXT and len(self.FixupsLayoutOrphan) > 0

    def _generateFixupList(self, bar):
        """ Initialize the fixup information from metadata """
        # The following is counting non-special fixups, excluding the type 5
        textIdx, specialIdx, orphanIdx = 0, 0, 0
        for idx in range(len(self.FixupData)):
            FI = unit.Fixup()

            # Only .text section could have a jump table.
            if self.sectionName == C.SEC_TEXT:
                FI.offset, FI.derefSz, FI.isRela, FI.type, FI.numJTEntries, FI.jtEntrySz = self.FixupData[idx]
            else:
                FI.offset, FI.derefSz, FI.isRela, FI.type = self.FixupData[idx]

            FI.VA = FI.offset + self.secOff

            # Assign the parent of the BB and add it to the list iff .text section
            if self.sectionName == C.SEC_TEXT and FI.type < 4:
                try:
                    FI.parent = self.CI.getBasicBlock(self.Fixup2BB[textIdx])
                    FI.parent.Fixups.append(FI)
                except:
                    FI.isOrphan = True

            if FI.type == C.FT_Special:
                FI.idx = specialIdx
                self.FixupsLayoutSpecial.append(FI)
                specialIdx += 1
            elif FI.isOrphan:
                FI.idx = orphanIdx
                FI.isRela = True    # Should be done manually (metadata does not have it)
                self.FixupsLayoutOrphan.append(FI)
                orphanIdx += 1
            else:
                FI.idx = textIdx
                self.FixupsLayout.append(FI)
                textIdx += 1
            bar += 1

    def _processRefs(self):
        """ Compute fixup derefVals and refTos from the given section """
        def findFixupTarget(FI):
            FI.derefVal = struct.unpack(fmt[FI.derefSz],
                                        sectionData[FI.offset:FI.offset + FI.derefSz])[0]
            FI.refTo = FI.VA + FI.derefSz + util.toSigned32(FI.derefVal) if FI.isRela else FI.derefVal
            FI.refBB = self.CI.getBBlByVA(FI.refTo)
            if FI.refBB:
                FI.target = "BB#%3s" % str(FI.refBB.idx)
            else:
                FI.target = self.elfParser.getSectionByVA(FI.refTo)

        sectionData = self.elfParser.elf.get_section_by_name(self.sectionName).data()
        fmt = {1: "<b", 2: "<h", 4: "<i", 8: "<q"}
        for FI in self.FixupsLayout:
            FI.derefVal = struct.unpack(fmt[FI.derefSz],
                                        sectionData[FI.offset:FI.offset + FI.derefSz])[0]

            # In the small/medium ABI model, it is safe to assume that
            # all FixupRefValues are the signed 32-bit integers
            # FIXME : Handle the large model (64-bit offset) in need - we do not care for now
            FI.refTo = FI.VA + FI.derefSz + util.toSigned32(FI.derefVal) if FI.isRela else FI.derefVal
            FI.refBB = self.CI.getBBlByVA(FI.refTo)
            if FI.refBB:
                FI.target = "BB#%3s" % str(FI.refBB.idx)
                if FI.parent:
                    FI.parent.refFroms.append(FI.refBB)

                    '''
                    # [NEW] We only trace CFG of the function (i.e., cross reference)
                    #       iff a fixup points to the region within .text section
                    if self.sectionName == C.SEC_TEXT and FI.type == C.FT_C2C:
                        fixupFunc, refBBFunc = FI.parent.parent, FI.refBB.parent

                        if fixupFunc.idx != refBBFunc.idx:
                            # For direct references (either by calls or jump families)
                            # For indirect references using JT, see updateFixupRefs1() in reorderEngine
                            fixupFunc.refTos.add(refBBFunc)
                            refBBFunc.refFroms.add(fixupFunc)
                    '''

            else:
                FI.target = self.elfParser.getSectionByVA(FI.refTo)
                nopBytes = util.countRefToNops(sectionData, FI)
                if FI.target == C.SEC_TEXT and nopBytes > 0:
                    FI.refBB = self.CI.getBBlByVA(FI.refTo + nopBytes)
                    logging.warning("\tFound the Fixup that points to a NOP block: refBBL adjusted to the next BBL")
                    if FI.refBB:
                        FI.target = "BB#%3s" % str(FI.refBB.idx)

        # Since we do not have BBL information for special sections,
        #       a) Find the corresponding BBL here
        #       b) Patching fixup should be done in patchCodeSection() in a binaryBuilder class
        if self.hasSpecialSection():
            for FI in self.FixupsLayoutSpecial:
                findFixupTarget(FI)

        if self.hasOrphanFixups():
            for FI in self.FixupsLayoutOrphan:
                findFixupTarget(FI)
                logging.info("Orphan Fixup (maybe -cfi-icall?): %s" % (FI))

    def verifyFixups(self):
        """ Processes fixup verification not to screw up further randomization """
        sn = self.sectionName
        saneFlag = True

        if len(set([FI.offset for FI in self.FixupsLayout])) < self.numFixups:
            logging.warning('\t[%s] There are redundant fixups!' % (sn))
            saneFlag = False

        if sn == C.SEC_TEXT:
            for FI in self.FixupsLayout:
                if FI.type not in C.FIXUP_TYPE:
                    logging.warning('\t[%s] Has unknown type (Fixup#%d): %s' % (sn, FI.idx, C.FIXUP_TYPE[FI.type]))
                    saneFlag = False
                if FI.type == C.FT_D2C or FI.type == C.FT_D2D:
                    logging.warning('\t[%s] Has wrong type (Fixup#%d): %s' % (sn, FI.idx, C.FIXUP_TYPE[FI.type]))
                    saneFlag = False
                if FI.type == C.FT_C2C and not FI.refBB:
                    if FI.parent.parent.parent.srcKind == C.SRC_TYPE_ASSEMBLY:
                        logging.warning("\t[%s] Fixup %d comes from standalone assembly (Obj#%d)!" %
                                        (sn, FI.idx, FI.parent.parent.parent.idx))
                    else:
                        logging.warning('\t[%s] Fails to discover the reference BBL (Fixup#%d)' % (sn, FI.idx))
                        saneFlag = False
                if FI.VA < FI.parent.VA:
                    logging.warning('\t[%s] Has wrong Fixup VA: VA(Parent BBL)=0x%04x VS VA(Fixup)=0x%04x'
                                   % (sn, FI.parent.VA, FI.VA))
                    saneFlag = False
                if FI.type != C.FT_C2D and FI.numJTEntries > 0:
                    logging.warning('\t[%s] Refers a jump table from non-C2D type (Fixup#%d)' % (sn, FI.idx))
                    saneFlag = False

        if sn == C.SEC_RODATA or sn == C.SEC_DATA or sn == C.SEC_DATA_REL:
            for FI in self.FixupsLayout:
                if FI.type not in C.FIXUP_TYPE:
                    logging.warning('\t[%s] Has unknown type (Fixup#%d): %s' % (sn, FI.idx, C.FIXUP_TYPE[FI.type]))
                    saneFlag = False
                if FI.type == C.FT_C2C or FI.type == C.FT_C2D:
                    logging.warning('\t[%s] Has wrong type (Fixup#%d): %s' % (sn, FI.idx, C.FIXUP_TYPE[FI.type]))
                    saneFlag = False
                if FI.type == C.FT_D2C and not FI.isRela and not FI.refBB:
                    logging.warning('\t[%s] No legitimate RefBBL (Fixup#%d)' % (sn, FI.idx))
                    saneFlag = False

        return saneFlag

    def getFixups(self):
        """ Return the list of fixup(s) in a layout order """
        return self.FixupsLayout

    def getSpecialFixups(self):
        """ Return the list of special fixup(s) """
        return self.FixupsLayoutSpecial

    def getOrphanFixups(self):
        """ Return the list of special fixup(s) """
        return self.FixupsLayoutOrphan

    def show(self):
        """ Show the fixup layout in detail """
        logging.info("\tFixups in %s section: %d" % (self.sectionName, self.numFixups))
        for fixup in self.FixupsLayout:
            logging.info(fixup)

class EssentialInfo():
    def __init__(self, RI):
        """
        Construct the essential information based on the collected information from compiler toolchain
            a) Build the layout tree - basic blocks, functions, and objects
            b) Build the entire fixup info (.text, .rodata, .data.rel.ro, .data and .init_array section)
            c) Confirm if reconstructed data is sane before processing randomization
        :param RI:
        """

        # Pre-processing: data collection and preparation for building essential information
        binInfo = RI['bin_info']
        objInfo = (RI['obj_size'], RI['obj_func_cnt'], RI['obj_src_type'])
        funcInfo = (RI['func_size'], RI['func_bb_cnt'])
        bbInfo = (RI['bb_size'], RI['bb_fixup_cnt'], RI['bb_fall_through'])

        fixupsText      = (RI[C.DS_FIXUP_TEXT[0]], RI[C.DS_FIXUP_TEXT[1]],
                           RI[C.DS_FIXUP_TEXT[2]], RI[C.DS_FIXUP_TEXT[3]],
                           RI[C.DS_FIXUP_TEXT[4]], RI[C.DS_FIXUP_TEXT[5]])
        fixupsRodata    = (RI[C.DS_FIXUP_RODATA[0]], RI[C.DS_FIXUP_RODATA[1]],
                           RI[C.DS_FIXUP_RODATA[2]], RI[C.DS_FIXUP_RODATA[3]])
        fixupsData      = (RI[C.DS_FIXUP_DATA[0]], RI[C.DS_FIXUP_DATA[1]],
                           RI[C.DS_FIXUP_DATA[2]], RI[C.DS_FIXUP_DATA[3]])
        fixupsDataRel   = (RI[C.DS_FIXUP_DATAREL[0]], RI[C.DS_FIXUP_DATAREL[1]],
                           RI[C.DS_FIXUP_DATAREL[2]], RI[C.DS_FIXUP_DATAREL[3]])
        fixupsInitArray = (RI[C.DS_FIXUP_INIT_ARR[0]], RI[C.DS_FIXUP_INIT_ARR[1]],
                           RI[C.DS_FIXUP_INIT_ARR[2]], RI[C.DS_FIXUP_INIT_ARR[3]])

        layoutInfoCnt = len(RI['obj_size']) + len(RI['func_size']) + len(RI['bb_size'])
        self.fixupInfoCnt = len(RI[C.DS_FIXUP_TEXT[0]]) + len(RI[C.DS_FIXUP_RODATA[0]]) + \
                            len(RI[C.DS_FIXUP_DATA[0]]) + len(RI[C.DS_FIXUP_DATAREL[0]]) + \
                            len(RI[C.DS_FIXUP_INIT_ARR[0]])
        bar = util.ProgressBar(layoutInfoCnt + self.fixupInfoCnt)

        # a) Construct BasicBlocks, Functions, Objects and the binary in Bottom-Up way
        self.constructInfo = BasicBlocks(bar, binInfo, objInfo, funcInfo, bbInfo)

        # b) Construct all fixups in .text, .rodata, .data, data.rel.ro, and .init_array
        self.FixupsInText, self.FixupsInRodata = None, None
        self.FixupsInData, self.FixupsInDataRel = None, None
        self.FixupsInInitArray, self.FixupsInEhframe = None, None
        self.processFixups(bar, RI, fixupsText, fixupsRodata, fixupsData, fixupsDataRel, fixupsInitArray)
        bar.finish()

        # c) Check if the provided data is appropriate for generating a variant
        self.__sanityCheck(RI, self.constructInfo)

    def processFixups(self, bar, RI, fixupsText, fixupsRodata, fixupsData, fixupsDataRel, fixupsInitArray):
        """ If a section contains fixups, generate fixup instances """
        if len(RI[C.DS_FIXUP_TEXT[0]]) > 0:
            self.FixupsInText = Fixups(zip(*fixupsText), self.constructInfo, C.SEC_TEXT, bar)

        # ReorderOffset does not need to be adjusted other than .text
        if len(RI[C.DS_FIXUP_RODATA[0]]) > 0:
            self.FixupsInRodata = Fixups(zip(*fixupsRodata), self.constructInfo, C.SEC_RODATA, bar)

        if len(RI[C.DS_FIXUP_DATA[0]]) > 0:
            self.FixupsInData = Fixups(zip(*fixupsData), self.constructInfo, C.SEC_DATA, bar)

        if len(RI[C.DS_FIXUP_DATAREL[0]]) > 0:
            self.FixupsInDataRel = Fixups(zip(*fixupsDataRel), self.constructInfo, C.SEC_DATA_REL, bar)

        if len(RI[C.DS_FIXUP_INIT_ARR[0]]) > 0:
            self.FixupsInInitArray = Fixups(zip(*fixupsInitArray), self.constructInfo, C.SEC_INIT_ARR, bar)

    def __sanityCheck(self, RI, CI):
        """ Check if the provided data makes sense for transformation """
        binPath = RI['bin_info']['bin_path']
        logging.info("Sanity check for %s... " % binPath)

        # Assertion contains a series of significant sanity checks
        assert (os.path.isfile(binPath))
        assert (CI.numObjects > 0 and CI.numFunctions > 0 and CI.numBasicBlocks > 0)
        assert (sum(RI['obj_size']) == sum(RI['func_size']) == sum(RI['bb_size']))
        assert (CI.numObjects     == len(RI['obj_func_cnt']))
        assert (CI.numFunctions   == len(RI['func_bb_cnt']))
        assert (CI.numBasicBlocks == len(RI['bb_fixup_cnt']))
        assert (CI.numFixups == sum(RI['bb_fixup_cnt']))
        assert (len(RI['fixup_deref_size_ro']) == len(RI['fixup_offset_ro']))

        # Failing of the following checks requires further investigation
        if self.getFixupsText() and not self.FixupsInText.verifyFixups():
            logging.critical("\tVerification for Fixups in .text section has been failed!")

        if self.getFixupsRodata() and not self.FixupsInRodata.verifyFixups():
            logging.critical("\tVerification for Fixups in .rodata section has been failed!")

        if self.getFixupsData() and not self.FixupsInData.verifyFixups():
            logging.critical("\tVerification for Fixups in .data section has been failed!")

        if self.getFixupsDataRel() and not self.FixupsInDataRel.verifyFixups():
            logging.critical("\tVerification for Fixups in .data.rel section has been failed!")

        logging.info("\tAll sanity checks have been PASSED!!")

    def getInfo(self):
        """ Return the instance of this class """
        return self.constructInfo

    # Wrapper functions to obtain fixup(s) and to check if a section has any fixup
    def getFixupsText(self):
        """ Return fixup(s) in .text section if any """
        return self.FixupsInText.getFixups() if self.FixupsInText else None

    def getFixupsSpecial(self):
        """ Return special fixup(s) in .text section if any """
        if self.hasFixupsInText() and self.FixupsInText.hasSpecialSection():
            return self.FixupsInText.getSpecialFixups()

    def getFixupsOrphan(self):
        """ Return orphan fixup(s) in .text section if any """
        if self.hasFixupsInText() and self.FixupsInText.hasOrphanFixups():
            return self.FixupsInText.getOrphanFixups()

    def getFixupsRodata(self):
        """ Return fixup(s) in .rodata section if any """
        return self.FixupsInRodata.getFixups() if self.FixupsInRodata else None

    def getFixupsData(self):
        """ Return fixup(s) in .data section if any """
        return self.FixupsInData.getFixups() if self.FixupsInData else None

    def getFixupsDataRel(self):
        """ Return fixup(s) in .data.rel.ro section if any """
        return self.FixupsInDataRel.getFixups() if self.FixupsInDataRel else None

    def getFixupsInitArray(self):
        """ Return fixup(s) in .init_array section if any """
        return self.FixupsInInitArray.getFixups() if self.FixupsInInitArray else None

    def hasFixupsInText(self):
        """ Check if .text section has any fixup """
        return True if self.getFixupsText() else False

    def hasFixupsInRodata(self):
        """ Check if .rodata section has any fixup """
        return True if self.getFixupsRodata() else False

    def hasFixupsInData(self):
        """ Check if .data section has any fixup """
        return True if self.getFixupsData() else False

    def hasFixupsInDataRel(self):
        """ Check if .data.rel.ro section has any fixup """
        return True if self.getFixupsDataRel() else False

    def hasFixupsInInitArray(self):
        """ Check if .init_array section has any fixup """
        return True if self.getFixupsInitArray() else False

    def getNumFixups(self, section):
        """ Return the number of fixups for the given section """
        if section == C.SEC_TEXT:
            numFixupsText = self.FixupsInText.numFixups if self.hasFixupsInText() else 0
            numFixupsSpecial = self.FixupsInText.numFixupsSpecial \
                if self.hasFixupsInText() and self.FixupsInText.hasSpecialSection() else 0
            return (numFixupsText, numFixupsSpecial)

        if section == C.SEC_RODATA:
            return self.FixupsInRodata.numFixups if self.hasFixupsInRodata() else 0

        if section == C.SEC_DATA:
            return self.FixupsInData.numFixups if self.hasFixupsInData() else 0

        if section == C.SEC_DATA_REL:
            return self.FixupsInDataRel.numFixups if self.hasFixupsInDataRel() else 0

        if section == C.SEC_INIT_ARR:
            return self.FixupsInInitArray.numFixups if self.hasFixupsInInitArray() else 0

    def show(self, showlevel=1):
        """ Show the reconstructed layout (obj, fun, and bbl) in detail """
        logging.info('Reconstructed binary information from the metadata...')
        if showlevel > 0:
            for obj in self.constructInfo.getBinary().Objects:
                logging.info(obj)
                if showlevel > 1:
                    for fn in obj.Functions:
                        logging.info(fn)
                        if showlevel > 2:
                            for bbl in fn.BasicBlocks:
                                logging.info(bbl)
                                if showlevel > 3:
                                    for fixup in bbl.Fixups:
                                        logging.info(fixup)