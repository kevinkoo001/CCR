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
import struct
import hashlib
import unit
import util
import constants as C
from constants import Formats as FMT
from constants import Sizes as SZ

class BinaryBuilder():
    """
    Class for Successful Binary Instrumentation
    """
    def __init__(self, reorderEngine, hasRandSection=False):
        """
        Initialize useful variables for binary transformation
        :param reorderEngine:
        :param hasRandSection:
        """
        self.RE = reorderEngine
        self.EI = self.RE.getReorderInfo()
        self.EP = self.RE.getELFParser()
        self.randomizedBBContainer = self.RE.getRandBBs()
        self.fixupsSpecial = self.RE.getFixupsSpecial()
        self.fixupsOrphan = self.RE.getFixupsOrphan()
        self.fixupsRodata = self.RE.getFixupsRodata()
        self.fixupsData = self.RE.getFixupsData()
        self.fixupsDataRel = self.RE.getFixupsDataRel()
        self.fixupsInitArray = self.RE.getFixupsInitArray()
        self.hasRandSection = hasRandSection

        self.fmt = {FMT.CHAR: "<b", FMT.UCHAR: "<B",
                    FMT.SHORT: "<h", FMT.USHORT: "H",
                    FMT.INT: "<i", FMT.UINT: "<I",
                    FMT.LONG: "<q", FMT.ULONG: "<Q"}
        self.updatedSections = list()

        self.origBin = self.EP.bin  # Original Binary Dump
        self.instBin = ''           # Instrumented Binary

        # Define a simple function for packing/unpacking
        self.PK  = lambda f, val: struct.pack(self.fmt[f], val)
        self.UPK = lambda f, val: struct.unpack(self.fmt[f], val)[0]

        # Collect fruitful information during building process
        self.memo = self.RE.getReport()

    def getFormat(self, sz):
        """ Return formats for fixup reference size only """
        if sz == 1: return self.fmt[FMT.CHAR]
        if sz == 2: return self.fmt[FMT.SHORT]
        if sz == 4: return self.fmt[FMT.INT]
        if sz == 8: return self.fmt[FMT.LONG]

    def checkOrigLayout(self):
        """
        Analyze the section layout of the given binary
        :return:
        """
        ELF = self.EP.elf
        elfInfo = ELF._parse_elf_header()

        sections = []
        totalSec = ELF.num_sections()

        for i in range(1, totalSec):
            sec = ELF.get_section(i)
            s = unit.Section()
            s.idx = i
            s.name = sec.name

            # The following sections only exist in the process memory space
            if s.name == C.SEC_TM_CLONE or s.name == C.SEC_BSS:
                continue

            s.sz = sec['sh_size']
            s.va = sec['sh_addr']
            s.sectionStart = sec['sh_offset']
            s.sectionEnd = s.sectionStart + s.sz

            sections.append(s)

        # The file layout of the section might not match the memory layout
        self.updatedSections = sorted(sections, key=lambda s: s.sectionStart)
        self.updatedSections[-1].fileOffsetEnd = elfInfo['e_shoff']

        for i in range(len(self.updatedSections)-1):
            self.updatedSections[i].next = self.updatedSections[i+1]
            if self.updatedSections[i].sectionEnd < self.updatedSections[i+1].sectionStart:
                self.updatedSections[i].fileOffsetEnd = self.updatedSections[i+1].sectionStart
            else:
                self.updatedSections[i].fileOffsetEnd = self.updatedSections[i].sectionEnd

    def patchCodeSection(self, sectionChunk):
        """
        Patches all collected fixups in .text section
        :param sectionChunk:
        :return:
        """
        textBar = util.ProgressBar(len(self.randomizedBBContainer))

        # Fixme: Would be better if fixup could be updated at updateFixupRefs() of reorderEngine
        def updateRemainingFixups(FI, kind):
            if FI.refBB:
                self.instBin += textSection[pos:FI.offset]
                if not FI.isRela:  # Absolute value
                    FI.newRefVal = FI.newRefTo = FI.refBB.newVA
                else:  # Relative value
                    FI.newRefTo = FI.refBB.newVA
                    FI.newRefVal = FI.newRefTo - FI.VA - FI.derefSz
                self.instBin += struct.pack(self.getFormat(FI.derefSz), FI.newRefVal)
                logging.debug("[%s Fixup] 0x%x->0x%x@0x%x (BBVA: 0x%x->0x%x)" %
                             (kind, FI.derefVal, FI.newRefVal, FI.VA, FI.refBB.VA, FI.refBB.newVA))

            else:
                self.instBin += textSection[pos:FI.offset + FI.derefSz]
                logging.debug("[%s Fixup] Not updated: 0x%x (%s)" % (kind, FI.derefVal, FI.target))

        # Tricky - elf data() might be missing padding bytes; so use code section chuck instead of it
        # textSection = self.EP.elf.get_section_by_name('.text').data()
        textSection = sectionChunk
        MAINOFFSZ = SZ[FMT.INT]
        mainOffset = self.EI.mainAddrOffsetFromText

        # No-PIC case: update special fixups and main() address
        if mainOffset > 0:
            # Step 1-1) Copy everything before the pointer of the main function at _start() in crti.o object
            # The following procedure handles the fixups in a special section names if any, including
            #     {".text.unlikely", ".text.exit", ".text.startup", ".text.hot"} for compatibility reason
            #     Mostly class initialization routine resides in these sections in c++ applications
            if self.fixupsSpecial:
                pos = 0
                # Update all fixups that refer to the BBL within the randomization range
                for FI in self.fixupsSpecial:
                    updateRemainingFixups(FI, 'Special')
                    pos = FI.offset + FI.derefSz

                # Copy all bytes until we meet mainOffset to be updated
                self.instBin += textSection[pos:mainOffset]

            # Otherwise just copy all bytes to update mainOffset
            else:
                self.instBin += textSection[:mainOffset]

            # Step 2-1) Update the location pointing to the main() after reordering if any
            mainAddr = self.UPK(FMT.INT, textSection[mainOffset: mainOffset + MAINOFFSZ])
            self.memo.origMainAddr = mainAddr

            if self.EI.base > 0: # Absolute address (w/o PIC/PIE option)
                mainBBL = self.EI.getBBlByVA(mainAddr)
                self.instBin += self.PK(FMT.INT, mainBBL.newVA)
                self.memo.instMainAddr = mainBBL.newVA
            else:                # Relative address (w/ PIC/PIE option)
                mainBBL = self.EI.getBBlByVA(self.EI._getTextSecVA() + mainAddr + self.EI.mainAddrOffsetFromText + MAINOFFSZ)
                mainNewOffset = mainBBL.newVA - (self.EI.mainAddrOffsetFromText + MAINOFFSZ + self.EI._getTextSecVA())
                self.instBin += self.PK(FMT.INT, mainNewOffset)
                self.memo.instMainAddr = mainNewOffset

            # Step 3-1) Copy the bytes right before the first object to be reordered
            self.instBin += textSection[mainOffset + MAINOFFSZ:self.EI.reorderObjStartFromText]

        # When there is no main function (i.e, shared object w/ [-fPIC -pie] option),
        # just copy all until the first object for randomization
        else:
            self.memo.isMain = False

            # Step 1-2) Do the same update as above iff there is any fixup in a special section
            if self.fixupsSpecial:
                pos = 0
                for FI in self.fixupsSpecial:
                    # Here needs to care only if the fixup has a referenced BBL within the randomization range
                    updateRemainingFixups(FI, 'Special')
                    pos = FI.offset + FI.derefSz

                # Copy all bytes until we meet mainOffset to be updated
                self.instBin += textSection[pos:mainOffset]

            # Step 2-2) Otherwise just copy all bytes to update mainOffset
            else:
                self.instBin += textSection[:self.EI.reorderObjStartFromText]

        # Step 4) Patch the references accordingly
        #         Append the reordered basic blocks in order
        textPos = self.EI.reorderObjStartFromText
        for BBL in self.randomizedBBContainer:
            secOff = BBL.offsetFromSection
            BBLcode = textSection[secOff:secOff + BBL.size]
            fixupBBLOffs = dict()

            # Obtain patching locations (distance from each BBL) for all fixups
            for FI in BBL.Fixups:
                fixupBBLOffs[FI.VA - BBL.VA] = (FI.derefSz, FI.newRefVal)

            # Copy the patched code in a randomized order
            pos = 0
            for off in sorted(fixupBBLOffs.keys()):
                # Code part to preserve
                self.instBin += BBLcode[pos:off]
                # Fixup reference to be updated (already from performTransformation())
                refSz, refVal = fixupBBLOffs[off]
                try:
                    self.instBin += struct.pack(self.getFormat(refSz), refVal)
                except struct.error:
                    logging.critical("BBL#%d [BBLOff:%d] %s" % (BBL.idx, off, BBL))
                    logging.critical("\tStruct error during patching references in .text! " \
                                     "(Deref Size: %dB, Val:0x%04x)" % (refSz, refVal))
                    sys.exit(1)
                pos = off + refSz

            self.instBin += BBLcode[pos:]  # Remaining code in the BBL if any
            textPos += BBL.size
            textBar += 1

        textBar.finish()

        # Step 5) (Optional) This is only when there are orphan fixups
        #          only when for -cfi-icall option has been enabled (implementation-specific)
        #          Other CFI options for LLVM do not contain any orphan fixup observed yet.
        '''
            1) cfi_icall:          CFI for indirect calls
            2) cfi_vcall:          CFI for virtual function calls
            3) cfi_nvcall:         CFI for calling non-virtual member functions
            4) cfi_unrelated_cast: CFI for the casts between objects of unrelated types
            5) cfi_derived_cast:   CFI for the casts between a base and a derived class
            6) cfi_cast_strict:    specific instance where 5) would not catch an illegal cast
        '''
        if self.fixupsOrphan:
            for FI in self.fixupsOrphan:
                # Assume orphan fixups for CFI always should have a refBB with a relative value
                try:
                    trampoline = '\xE9'     # unconditional jump instruction
                    FI.newRefTo = FI.refBB.newVA
                    FI.newRefVal = FI.newRefTo - FI.VA - FI.derefSz
                    # 8 byte aligned with three 0xCCs at all times
                    trampoline += struct.pack(self.getFormat(FI.derefSz), FI.newRefVal) + '\xCC'*3
                    self.instBin += trampoline
                    logging.info("[Orphan Fixup] 0x%x->0x%x@0x%x (BBVA: 0x%x->0x%x)" %
                             (FI.derefVal, FI.newRefVal, FI.VA, FI.refBB.VA, FI.refBB.newVA))
                except:
                    logging.critical("[Orphan Fixup] Could not find a reference BB!: %s" % (FI))
            textPos += 8 * len(self.fixupsOrphan)

        # Step 5) Remaining code in the text section (that has not been reordered)
        self.instBin += textSection[textPos:]

    def patchDataSection(self, sectionChunk, fixups):
        """
        Patches all collected fixups in .rodata/.data/.data.rel.ro section
        :param sectionChunk:
        :param fixups:
        :return:
        """

        # Step 1) Check if any fixupData exists
        if fixups:
            dataBar = util.ProgressBar(len(fixups))
            fixups = sorted(fixups, key=lambda F: F.offset)

        # Step 2) Initialize the first fixup offset in the section
        pos = fixups[0].offset if fixups else 0

        # Step 3) Copy all data until the first fixup appears if any
        self.instBin += sectionChunk[:pos]

        # Step 4) The fixups to be patched might not be continuous
        #         Hence take care of non-fixup data during updates
        if fixups:
            for i, FI in enumerate(fixups):
                # newRefVals are already computed from performReorder()
                refSz, newRefVal = FI.derefSz, FI.newRefVal
                self.instBin += struct.pack(self.getFormat(refSz), newRefVal)
                pos += refSz
                if i < len(fixups) - 1 and fixups[i + 1].offset > pos:
                    nextFixupOffset = fixups[i + 1].offset
                    self.instBin += sectionChunk[pos:nextFixupOffset]
                    pos = nextFixupOffset
                dataBar += 1
            dataBar.finish()

        # Step 5) The last remaining data to maintain intact if any
        self.instBin += sectionChunk[pos:]

    def patchRelocationSection(self, secName, sectionChunk):
        """ Patches all relocation entries for .rela.dyn section """
        patchCtr = 0
        if self.EI.base == 0:
            relocDyn = self.EP.elf.get_section_by_name('.rela.dyn')
            assert(len(sectionChunk) % relocDyn.num_relocations() == 0)

            """
            # For now, any Addend (R_X86_64_RELATIVE) within the range of reordering would be updated
            # Below is the example (* represents the randomized locations, which has been adjusted)
            Relocation section '.rela.dyn' at offset 0x408 contains 10 entries:
              Offset          Info           Type           Sym. Value    Sym. Name + Addend
            000000001dd0  000000000008 R_X86_64_RELATIVE                    660
            000000001dd8  000000000008 R_X86_64_RELATIVE                    6a0
            000000002028  000000000008 R_X86_64_RELATIVE                    2028
            000000002030  000000000008 R_X86_64_RELATIVE                    6d0*
            000000002038  000000000008 R_X86_64_RELATIVE                    6f0*
            000000001fd8  000100000006 R_X86_64_GLOB_DAT 0000000000000000 __cxa_finalize@GLIBC_2.2.5 + 0
            000000001fc0  000300000006 R_X86_64_GLOB_DAT 0000000000000000 __gmon_start__ + 0
            000000001fc8  000400000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_deregisterTMClone + 0
            000000001fd0  000500000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_registerTMCloneTa + 0
            000000001fe0  000600000006 R_X86_64_GLOB_DAT 0000000000000000 _Jv_RegisterClasses + 0
            """
            #TODO - Is there any other type to update other than R_X86_64_RELATIVE?
            for rel in relocDyn.iter_relocations():
                offset, addend = rel['r_offset'], rel['r_addend']
                type, sym = rel['r_info_type'], rel['r_info_sym']
                self.instBin += self.PK(FMT.LONG, offset)
                self.instBin += self.PK(FMT.INT, type)
                self.instBin += self.PK(FMT.INT, sym)
                if self.EI.isInReorderRange(addend):
                    newAddend = self.EI.getBBlByVA(addend).newVA
                    self.instBin += self.PK(FMT.LONG, newAddend)
                    patchCtr += 1
                    logging.debug("   [%s] Original: 0x%x -> Updated: 0x%x" % (secName, addend, newAddend))
                else:
                    self.instBin += self.PK(FMT.LONG, addend)

        # In case of non-pic, proceed it as normal
        else:
            self.instBin += sectionChunk

        self.memo.numRelocPatch += patchCtr

    def patchSymbolTable(self, secName, sectionChunk):
        """ Patches all symbol values after randomization for '.dynsym' and '.symtab' section """
        symbolTable = self.EP.elf.get_section_by_name(secName)
        assert(len(sectionChunk) % symbolTable.num_symbols() == 0)
        symbolBar = util.ProgressBar(symbolTable.num_symbols())

        patchCtr = 0
        symOffset = 0
        randRangeBottom = self.EI._getTextSecVA() + self.EI.reorderObjStartFromText
        randRangeTop = randRangeBottom + self.EI.reorderedObjSize

        # [FIXME] Define a temporary bag to contain symval and symsize
        #         Ugly hack - it arises from the discrepancy of the function (symbol) size
        #                     that lacks alignment size; maybe we could do better
        sym_temp_lookup = {}
        for symbol in symbolTable.iter_symbols():
            symVal, symSz = symbol['st_value'], symbol['st_size']
            if randRangeBottom <= symVal < randRangeTop:
                sym_temp_lookup[symVal] = symSz

        for symbol in symbolTable.iter_symbols():
            """
            # The first 8 bytes have to be always identical - combined to symProperty
            type, bind = symbol['st_info']['type'], symbol['st_info']['bind']
            sym_other, sym_shndx = symbol['st_other']['visibility'], symbol['st_shndx']
            """
            symProperty = sectionChunk[symOffset:symOffset + 8]
            symVal, symSz = symbol['st_value'], symbol['st_size']
            self.instBin += symProperty

            # We only need to update the symbol value/size (either absolute or relative VA) here
            if randRangeBottom <= symVal < randRangeTop:
                try:
                    sym_fn = self.EI.getBBlByVA(symVal)
                    newSymVal = sym_fn.newVA
                    self.instBin += self.PK(FMT.LONG, newSymVal)
                    self.instBin += self.PK(FMT.LONG, sym_temp_lookup[symVal])

                    patchCtr += 1
                    logging.debug(" [%s] Original: 0x%x -> Updated: 0x%x" % (secName, symVal, newSymVal))

                    # [NEW] Let's save the symbol name for each function defined as a symbol
                    sym_fn.parent.name = symbol.name

                except AttributeError:
                    self.instBin += self.PK(FMT.LONG, symVal)
                    logging.warning(" [%s] Failed to update the symbol: 0x%x " % (secName, symVal))
            else:
                self.instBin += self.PK(FMT.LONG, symVal)
                self.instBin += self.PK(FMT.LONG, symSz)

            # Each entry for a symbol is 24B in size; Move on the next entry
            symOffset += 24
            symbolBar += 1

        symbolBar.finish()
        self.memo.numSymPatch += patchCtr

    def patchInitArray(self, secName, sectionChunk, fixups):
        """ Patches '.init_array' section """
        if fixups:
            initBar = util.ProgressBar(len(fixups))
            fixups = sorted(fixups, key=lambda F: F.offset)

        pos = fixups[0].offset if fixups else 0
        self.instBin += sectionChunk[:pos]
        patchCtr = 0

        # TODO: Check if init_array has relavant values in PIC/PIE
        if fixups:
            for i, FI in enumerate(fixups):
                if self.EI.isInReorderRange(FI.refTo):
                    newRefTo = self.EI.getBBlByVA(FI.refTo).newVA
                    self.instBin += struct.pack(self.getFormat(FI.derefSz), newRefTo)
                    patchCtr += 1
                    logging.debug("   [%s] Original: 0x%x -> Updated: 0x%x" %
                                 (secName, FI.refTo, newRefTo))
                else:
                    self.instBin += struct.pack(self.getFormat(FI.derefSz), FI.refTo)
                pos += FI.derefSz
                initBar += 1
            initBar.finish()

        self.instBin += sectionChunk[pos:]
        self.memo.numInitArrayPatch += patchCtr

    def patchEhframe(self, secName, sectionChunk):
        """
        Here patches a .eh_frame section, which contains the information to unwind the stack
            - Has the same structure with .debug_frame, which follows DWARF format
            - Overall structure
              : Represents a table that describes how to set registers to restore the previous call frame
              : Each row shows how the given text location could return to the previous frame
              : Consists of two forms: CIE and FDE
            - DWARF designers allow one to have flexible mechanism for unwinding with expressions
              : Constant values, Arithmetic, Memory dereference, Register contents, Control flow
            - CIE (Common Information Entry) attributes
              : length, CIE_id, version, augmentation, addr_sz, seg_sz,
              : code_align_factor, data_align_factor, ret_addr_reg, initial_instns, padding
            - FDE (Frame Description Entry) attributes
              : length, CIE_ptr, initial_location, addr_range, LSDA_ptr, instns, padding
            - What we care to update
              : initial_location, the relative addr of the first instruction (the function entry) in every FDE
              : If CIE that FDE belongs to contains 'L' in augmentation, follow LSDA pointer in FDE.
                 .gcc_except_table is a collection of LSDA (Language Specific Data Areas)
            - Reference
              : DWARF Debugging Information Format p.174-6: http://dwarfstd.org/doc/DWARF5.pdf
              : http://refspecs.linuxfoundation.org/LSB_3.0.0/LSB-Core-generic/LSB-Core-generic/ehframechpt.html
              : http://www.hexblog.com/wp-content/uploads/2012/06/Recon-2012-Skochinsky-Compiler-Internals.pdf

        Example of a break-down CIE
            Len=0x14 (4B), CIE_id=0 (4B), version=1 (compiler-dependent?)
            -------------------------
            00000000 0000000000000014 00000000 CIE
            Version:               1
            Augmentation:          "zR"
            Code alignment factor: 1
            Data alignment factor: -8
            Return address column: 16
            Augmentation data:     1b
            DW_CFA_def_cfa: r7 (rsp) ofs 8
            DW_CFA_offset: r16 (rip) at cfa-8
            DW_CFA_nop
            DW_CFA_nop

        Example of a break-down FDE
            Len=0x1c (4B), CIE_ptr=0x1c (4B),
            initial_loc = 0xfffffb08 (4B) => 0x400600, addr_range=0x35 (4B)
            -------------------------
            00000018 000000000000001c 0000001c FDE cie=00000000 pc=0000000000400600..0000000000400635
            00 41 0E 10 86 02 43
              DW_CFA_advance_loc: 1 to 0000000000400601 (0x40 + 0x1 = 0x41)
              DW_CFA_def_cfa_offset: 16 (0xe 0x10)
              DW_CFA_offset: r6 (rbp) at cfa-16 (0x80 + 0x6 = 0x86)
              DW_CFA_advance_loc: 3 to 0000000000400604 (0x40 + 3 = 0x43)
              DW_CFA_def_cfa_register: r6 (rbp) (0x0d 0x06)
              DW_CFA_nop (0x0)
              DW_CFA_nop (0x0)
              DW_CFA_nop (0x0)
              DW_CFA_nop (0x0)
              DW_CFA_nop (0x0)
              DW_CFA_nop (0x0)
              DW_CFA_nop (0x0)

        :param sectionChunk:
        :return:
        """
        pos, frameLen = 0, 0
        cie, fde = 0, 0
        patchCtr = 0

        LEN_SZ = SZ[FMT.INT]
        ehframe = [x for x in self.updatedSections if x.name == secName][0]

        # Walk all section to read either:
        #   CIE(Common Information Entry) or FDE(Frame Description Entry)
        while pos < len(sectionChunk):
            frameLen = self.UPK(FMT.INT, sectionChunk[pos:pos + LEN_SZ])
            entry = sectionChunk[pos:pos + frameLen + LEN_SZ]
            if frameLen == 0:
                break

            # We check the version info of each entry, the binary from LLVM is 1 iff CIE
            ver = self.UPK(FMT.UCHAR, entry[8])
            if ver == 1 or ver == 3:
                self.instBin += entry
                cie += 1
            else:
                relLoc = self.UPK(FMT.INT, entry[8:8 + LEN_SZ])
                pc = ehframe.va + (pos + 8) + relLoc
                range = self.UPK(FMT.INT, entry[12:12 + LEN_SZ])

                if self.EI.isInReorderRange(pc):
                    newPc = self.EI.getBBlByVA(pc).newVA
                    newRelLoc = newPc - ehframe.va - (pos + 8)
                    self.instBin += entry[:8]
                    self.instBin += self.PK(FMT.INT, newRelLoc)
                    self.instBin += entry[12:]
                    patchCtr += 1
                    logging.debug("   [%s] FDE PC range [0x%x:0x%x] -> [0x%x:0x%x]" %
                                 (secName, pc, pc + range, newPc, newPc + range))
                else:
                    self.instBin += entry
                fde += 1

            pos += (frameLen + LEN_SZ)

        # Here adds the last alignment if any
        self.instBin += sectionChunk[pos:]
        self.memo.ehframeCIE, self.memo.ehframeFDE = cie, fde
        self.memo.numEhframePatch = patchCtr

    def patchEhframeHdr(self, secName, sectionChunk):
        """
        .eh_frame_hdr
            Contains a table of pairs(initial location, ptr to the FDE in .eh_frame)
            Sorted entries allow for quick binary search of O(log n)
        Attributes in order
            version, eh_frame_ptr_enc, fde_count_enc, table_enc (uint8)
            eh_frame_ptr, fde_count (4B)
            pairs of (initial_loc[n] and fde_ptr[n]) (4B per each pair)
        References
            https://refspecs.linuxfoundation.org/LSB_1.3.0/gLSB/gLSB/ehframehdr.html
        :param sectionChunk:
        :return:
        """
        def readEncodingType(e):
            '''
            DWARF Exception Header value format (lower 4 bits)
                DW_EH_PE_omit	 0xff	No value is present.
                DW_EH_PE_uleb128 0x01	Unsigned value is encoded using LEB128
                DW_EH_PE_udata2	 0x02	A 2 bytes unsigned value.
                DW_EH_PE_udata4	 0x03	A 4 bytes unsigned value.
                DW_EH_PE_udata8	 0x04	An 8 bytes unsigned value.
                DW_EH_PE_sleb128 0x09	Signed value is encoded using LEB128
                DW_EH_PE_sdata2	 0x0A	A 2 bytes signed value.
                DW_EH_PE_sdata4	 0x0B	A 4 bytes signed value.
                DW_EH_PE_sdata8	 0x0C	An 8 bytes signed value.
            DWARF Exception Header Encoding (upper 4 bits)
                DW_EH_PE_absptr	 0x00	Value is used with no modification.
                DW_EH_PE_pcrel	 0x10	Value is reletive to the current program counter.
                DW_EH_PE_datarel 0x30	Value is reletive to the beginning of the .eh_frame_hdr section.
                DW_EH_PE_omit	 0xff	No value is present.
            :param e:
            :return:
            '''
            if e == 0xff:
                return FMT.INVALID, FMT.INVALID

            upperMask, lowerMask = 0xf0, 0x0f
            val, ty = e&lowerMask, e&upperMask

            return getFormat(val), ty

        def getFormat(v):
            if v == 0x2: return FMT.USHORT
            elif v == 0x3: return FMT.UINT
            elif v == 0x4: return FMT.ULONG
            elif v == 0xA: return FMT.SHORT
            elif v == 0xB: return FMT.INT
            elif v == 0xC: return FMT.LONG
            elif v == 0x2 or v == 0x9:
                raise NotImplementedError("LEB128 encoding has not been implemented!")

        def evalTarget(app, loc, ehframeSecBegin, pos, sz):
            if app == 0x00: # Absolute address
                return loc
            elif app == 0x10: # Relative to the pc
                pc = ehframeSecBegin + pos + sz
                return loc + pc
            elif app == 0x30: # Relative to the .eh_frame_hdr section
                return loc + ehframeSecBegin

        def computeNewRelLoc(app, newLoc, ehframeSecBegin, pos, sz):
            if app == 0x00:
                return newLoc
            elif app == 0x10:
                pc = ehframeSecBegin + pos + sz
                return newLoc - pc
            elif app == 0x30:
                return newLoc - ehframeSecBegin

        ehframeHdr = [x for x in self.updatedSections if x.name == secName][0]
        patchCtr = 0

        # Get version, fde_count_enc and table_enc
        # We do not care about eh_frame_ptr_enc because eh_frame is out of randomization range
        ver = self.UPK(FMT.UCHAR, sectionChunk[0])
        fdeVal, fdeTy = readEncodingType(self.UPK(FMT.UCHAR, sectionChunk[2]))
        tblVal, tblTy = readEncodingType(self.UPK(FMT.UCHAR, sectionChunk[3]))

        if ver != 1:
            logging.critical("   [%s] Wrong version." % secName)
        if fdeVal == FMT.INVALID or tblVal == FMT.INVALID:
            logging.critical("   [%s] Invalid value." % secName)

        # Safely assume that the number of the entries can be used as it is (no modification)
        numEntries = self.UPK(fdeVal, sectionChunk[8:8 + SZ[fdeVal]])
        self.instBin += sectionChunk[:12]

        # Obtain each entry pair (initial_loc[n] and fde_ptr[n]) from the table, and
        #    compute new relative locations for every initial_loc[n]
        pos = 12
        newFdePtrs = []
        for _ in range(numEntries):
            initialLoc = self.UPK(tblVal, sectionChunk[pos:pos + SZ[tblVal]])
            targetFunc = evalTarget(tblTy, initialLoc, ehframeHdr.va, pos, SZ[tblVal])
            pos += 4

            fdePtr = self.UPK(tblVal, sectionChunk[pos:pos + SZ[tblVal]])
            targetFDE = evalTarget(tblTy, fdePtr, ehframeHdr.va, pos, SZ[tblVal])
            pos += 4

            if self.EI.isInReorderRange(targetFunc):
                newVA = self.EI.getBBlByVA(targetFunc).newVA
                newFdePtrs.append((newVA, targetFDE))
                patchCtr += 1
            else:
                newFdePtrs.append((targetFunc, targetFDE))

            logging.debug("   [%s] Corresponding Func: 0x%x (%d), FDE: 0x%x (%d)" %
                         (secName, targetFunc, initialLoc, targetFDE, fdePtr))

        # Now all pairs should be rewritten in a way which initial_locs are ordered for binary search
        # Note that newRelLoc and newFdePtr are relative values whereas
        #           funcAddr(=newVA or targetFunc) and fdeAddr(=targetFDE) are absolute ones
        pos = 12
        newFdePtrs = sorted(newFdePtrs, key=lambda x: x[0])
        for funcAddr, fdeAddr in newFdePtrs:
            newRelLoc = computeNewRelLoc(tblTy, funcAddr, ehframeHdr.va, pos, SZ[tblVal])
            self.instBin += self.PK(FMT.INT, newRelLoc)
            pos += 4
            newFdePtr = computeNewRelLoc(tblTy, fdeAddr, ehframeHdr.va, pos, SZ[tblVal])
            self.instBin += self.PK(FMT.INT, newFdePtr)
            pos += 4

            logging.debug("   [%s] New Corresponding Func: 0x%x (%d), FDE: 0x%x (%d)" %
                         (secName, funcAddr, newRelLoc, fdeAddr, newFdePtr))

        self.instBin += sectionChunk[pos:]
        self.memo.numEhframeHdrPatch = patchCtr

    def patchDebugInfo(self, secName, sectionChunk):
        """
        .debug_info section update
            The following code is based on a dwarf example of an elftools library
            From an official DWARF documenation (http://dwarfstd.org/doc/DWARF4.pdf)
                a) DW_AT_low_pc and DW_AT_high_pc pair or a DW_AT_ranges attribute
                   encode the contiguous or non-contiguous address ranges, respectively,
                   of the machine instructions generated for the compilation unit
                b) DW_AT_name attribute
                   a null-terminated string containing the path name of the primary source
                c) DW_AT_stmt_list attribute
                   a section offset to the line number information for compilation unit
                d) DW_AT_macro_info attribute
                   a section offset to the macro information for compilation unit
        :param secName:
        :param sectionChunk:
        :return:
        """
        def _decode_funcname(dwarfinfo, address):
            # Go over all DIEs in the DWARF information, looking for a subprogram
            # entry with an address range that includes the given address. Note that
            # this simplifies things by disregarding subprograms that may have
            # split address ranges.
            for CU in dwarfinfo.iter_CUs():
                for DIE in CU.iter_DIEs():
                    try:
                        if DIE.tag == 'DW_TAG_subprogram':
                            lowpc = DIE.attributes['DW_AT_low_pc'].value

                            # DWARF v4 in section 2.17 describes how to interpret the
                            # DW_AT_high_pc attribute based on the class of its form.
                            # For class 'address' it's taken as an absolute address
                            # (similarly to DW_AT_low_pc); for class 'constant', it's
                            # an offset from DW_AT_low_pc.
                            highpc_attr = DIE.attributes['DW_AT_high_pc']
                            highpc_attr_class = describe_form_class(highpc_attr.form)
                            if highpc_attr_class == 'address':
                                highpc = highpc_attr.value
                            elif highpc_attr_class == 'constant':
                                highpc = lowpc + highpc_attr.value
                            else:
                                print('Error: invalid DW_AT_high_pc class:',
                                      highpc_attr_class)
                                continue

                            if lowpc <= address <= highpc:
                                return DIE.attributes['DW_AT_name'].value
                    except KeyError:
                        continue
            return None

        def _decode_file_line(dwarfinfo, address):
            '''
            Go over all the line programs in the DWARF information, looking for
            one that describes the given address.
            '''
            for CU in dwarfinfo.iter_CUs():
                # First, look at line programs to find the file/line for the address
                lineprog = dwarfinfo.line_program_for_CU(CU)
                prevstate = None
                for entry in lineprog.get_entries():
                    # We're interested in those entries where a new state is assigned
                    if entry.state is None or entry.state.end_sequence:
                        continue
                    # Looking for a range of addresses in two consecutive states that
                    # contain the required address.
                    if prevstate and prevstate.address <= address < entry.state.address:
                        filename = lineprog['file_entry'][prevstate.file - 1].name
                        line = prevstate.line
                        return filename, line
                    prevstate = entry.state
            return None, None

        def _decode_addr(address):
            funcname = _decode_funcname(dwarfinfo, address)
            file, line = _decode_file_line(dwarfinfo, address)

            logging.debug('\tFunction: %s' % bytes2str(funcname))
            logging.debug('\tFile: %s' % bytes2str(file))
            logging.debug('\tLine: %s' % line)

        dwarfinfo = self.EP.elf.get_dwarf_info()

        # Experimental: reading statement advances
        # CUs = [x for x in dwarfinfo.iter_CUs()]
        # debug_line = dwarfinfo.line_program_for_CU(CUs[0])
        # debug_line_entries = debug_line.get_entries()
        # stmts = [hex(x.state.address) for x in debug_line_entries if x.state is not None]

        from elftools.common.py3compat import itervalues, bytes2str
        from elftools.dwarf.descriptions import describe_form_class

        update_pos_vals = {}
        for CU in dwarfinfo.iter_CUs():
            # DWARFInfo allows to iterate over the compile units contained in
            # the .debug_info section. CU is a CompileUnit object, with some
            # computed attributes (such as its offset in the section) and
            # a header which conforms to the DWARF standard. The access to
            # header elements is, as usual, via item-lookup.
            logging.debug('  Found a compile unit at offset %s, length %s' %
                          (CU.cu_offset, CU['unit_length']))

            # A CU provides a simple API to iterate over all the DIEs in it.
            for DIE in CU.iter_DIEs():
                # Go over all attributes of the DIE. Each attribute is an
                # AttributeValue object (from elftools.dwarf.die)
                # Here we only care the addresses for the subprograms
                # TODO: check it out for DW_TAG_inlined_subroutine (DWARF4)!
                for attr in itervalues(DIE.attributes):
                    if attr.name == 'DW_AT_low_pc' and DIE.tag == 'DW_TAG_subprogram':
                        logging.debug('   DIE %s. attr %s. Off: 0x%x, Addr:0x%x' %
                                        (DIE.tag, attr.name, attr.offset, attr.value))

                        #_decode_addr(attr.value)
                        update_pos_vals[attr.offset] = attr.value

        pos = 0
        for off in sorted(update_pos_vals.keys()):
            self.instBin += sectionChunk[pos:off]
            va = update_pos_vals[off]
            if self.EI.base > 0:
                updated_va = self.EI.getBBlByVA(va).newVA
                self.instBin += self.PK(FMT.ULONG, updated_va)
                logging.debug('[%s] 0x%08x -> 0x%08x' % (secName, va, updated_va))
                pos = off + 8

        self.instBin += sectionChunk[pos:]

    def instrumentBin(self, origBin, emittedBin, isSymbolUpdate):
        """
        The addr of main is stored in rdi register. Should be received from linker
        This might vary depending on libc version and system architecture. For example,
          In a _start()
            .text:004004AF 49 C7 C0 F0 06 40 00    mov   r8, offset __libc_csu_fini ; fini
            .text:004004B6 48 C7 C1 80 06 40 00    mov   rcx, offset __libc_csu_init ; init
            .text:004004BD 48 C7 C7 00 06 40 00    mov   rdi, offset main ; main
            .text:004004C4 E8 A7 FF FF FF          call  ___libc_start_main
        :return:
        """

        elfInfo = self.EP.elf._parse_elf_header()
        ehSz = elfInfo['e_ehsize']
        phOff = elfInfo['e_phoff']
        phSz = elfInfo['e_phnum'] * elfInfo['e_phentsize']
        shOff = elfInfo['e_shoff']
        shSz = elfInfo['e_shnum'] * elfInfo['e_shentsize']

        logging.debug("[0x%04x:0x%04x] Sz:%5dB InstBinSz:%5dB (ELF Hdr)" % (0, ehSz, ehSz, ehSz))
        logging.debug("[0x%04x:0x%04x] Sz:%5dB InstBinSz:%5dB (Program Hdr)" \
                      % (phOff, phOff + phSz, phSz, ehSz + phSz))

        # (1) Build ELF/Program Header
        self.instBin += self.origBin[0:ehSz + phSz]

        # (2) Instrument the sections in order
        #     Caution: note that get_section_by_name() does not include alignment, thus
        #     it might eventually fail to maintain the exact size of the instrumented binary.
        #     Thus here we deal with sectionChunk instead of

        secUpdated = [
            C.SEC_TEXT, C.SEC_RODATA, C.SEC_DATA, C.SEC_DATA_REL, C.SEC_DYNSYM,
            C.SEC_INIT_ARR, C.SEC_EH_FRAME, C.SEC_EH_FR_HDR, C.SEC_REL_DYN,
        ]

        if isSymbolUpdate:
            secUpdated += [C.SEC_SYMTAB]

        for sec in self.updatedSections:
            layoutName = sec.name
            start, end = sec.sectionStart, sec.fileOffsetEnd
            sectionChunk = self.origBin[start:end]

            if layoutName in secUpdated:
                logging.info("\tProcessing section [%s]" % (layoutName))

            # Patch all fixups (including the ones resolved by compiler)
            if layoutName == C.SEC_REL_DYN:
                self.patchRelocationSection(layoutName, sectionChunk)

            elif layoutName == C.SEC_TEXT:
                self.patchCodeSection(sectionChunk)

            # Patch the fixups in a .rodata section
            elif layoutName == C.SEC_RODATA:
                # rodataSection = self.EP.elf.get_section_by_name(layoutName).data()
                self.patchDataSection(sectionChunk, self.fixupsRodata)

            # Patch the fixups in a .data section
            elif layoutName == C.SEC_DATA:
                # dataSection = self.EP.elf.get_section_by_name(layoutName).data()
                self.patchDataSection(sectionChunk, self.fixupsData)

            # Patch the fixups in a .data.rel.ro section (for pic/pie executable only)
            elif layoutName == C.SEC_DATA_REL:
                # dataRelSection = self.EP.elf.get_section_by_name(layoutName).data()
                self.patchDataSection(sectionChunk, self.fixupsDataRel)

            elif layoutName == C.SEC_DYNSYM:
                self.patchSymbolTable(layoutName, sectionChunk)

            elif layoutName == C.SEC_SYMTAB and isSymbolUpdate:
                self.patchSymbolTable(layoutName, sectionChunk)

            elif layoutName == C.SEC_INIT_ARR:
                # initArraySection = self.EP.elf.get_section_by_name(layoutName)
                self.patchInitArray(layoutName, sectionChunk, self.fixupsInitArray)

            elif layoutName == C.SEC_EH_FRAME:
                # ehframeSection = self.EP.elf.get_section_by_name(layoutName)
                self.patchEhframe(layoutName, sectionChunk)

            elif layoutName == C.SEC_DEBUG_INFO:
                self.patchDebugInfo(layoutName, sectionChunk)

            elif layoutName == C.SEC_EH_FR_HDR:
                # ehframeSection = self.EP.elf.get_section_by_name(layoutName)
                self.patchEhframeHdr(layoutName, sectionChunk)

            else:
                self.instBin += self.origBin[start:end]

            logging.debug("[0x%04x:0x%04x] Sz:%5dB InstBinSz:%5dB (%s)" % \
                          (start, end, end - start, len(self.instBin), layoutName))

            assert (end == len(self.instBin)), \
                "Size Mismatch (%s): Orig[0x%04x:0x%04x] SecSz:%5dB InstBinSz: %5dB" % \
                (layoutName, start, end, end - start, len(self.instBin))

        logging.debug("[0x%04x:0x%04x] Sz:%5dB InstBinSz:%5dB (Section Hdr)" \
                      % (shOff, shOff + shSz, shSz, shOff + shSz))

        # (3) Build the section headers at the end
        self.instBin += self.origBin[shOff:shOff + shSz]

        # (4) Emit the instrumented binary into the file
        self.writeBin(origBin, emittedBin)

    def writeBin(self, oldBin, newBin):
        """
        Write the instrumented binary
        :param newBin:
        :return:
        """
        # Check if the final binary is sane in size
        assert (len(self.origBin) == len(self.instBin)), \
            "Mismatch the instrumented binary in size!\n Orig: 0x%04x, Inst: 0x%04x" \
            % (len(self.origBin), len(self.instBin))

        # Emit the final binary to be transformed
        with open(newBin, 'wb') as f:
            f.write(self.instBin)

        self.memo.instBinName = newBin

        # Change the permission to be executable
        os.chmod(newBin, 0755)

        '''
        # Compress the metadata (~80% compression rate empirically)
        # The following was just for measuring size increase before combining .rand section with the final binary
        if not self.hasRandSection:
            with gzip.open(GZIPPED_META, 'wb') as f:
                gzippedMetaBin = open(oldBin + METADATA_POSTFIX, 'rb').read()
                f.write(gzippedMetaBin)

            # Combine the gzipped metadata to the new binary with objcopy command
            randSection = RAND + '=' + GZIPPED_META
            combineSecCmd = ' '.join(['objcopy', '--add-section', randSection, newBin, '2> /dev/null'])
            os.system(combineSecCmd)
        '''

        if self.hasRandSection:
            removeSecCmd = ' '.join([C.OBJCOPY, C.OBJCOPY_RMSEC, C.RAND_SECTION, newBin, C.NULL])
            os.system(removeSecCmd)

        metaSz = os.path.getsize(C.METADATA_PATH)
        os.remove(C.METADATA_PATH)

        self.memo.origBinSz = os.path.getsize(oldBin)
        self.memo.instBinSz = os.path.getsize(newBin)
        self.memo.incRate = metaSz / float(self.memo.origBinSz - metaSz) * 100.0

        finalBin = open(newBin, 'rb').read()
        self.memo.origBinHash = hashlib.md5(self.origBin).hexdigest()
        self.memo.instBinHash = hashlib.md5(finalBin).hexdigest()
        self.memo.shuffledSz = self.EI.reorderedObjSize
        self.memo.metadataSz = metaSz
        self.memo.finalBinSz = len(finalBin)