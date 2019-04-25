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

import logging
import random
import constants as C
from reorderInfo import EssentialInfo

class ReorderCore(EssentialInfo):
    def __init__(self, ReorderInfo, report):
        '''
        Generate all essential information for further reordering.
        Note that the size information have included the alignment already.
        :param ReorderInfo:
        '''

        # First construct all essential information for randomization
        EssentialInfo.__init__(self, ReorderInfo)
        self.EI = self.getInfo()
        self.EP = self.EI.getElfParser()
        self.randomizedBBContainer = list()
        self.randLayout = list()
        self.R = report
        self.__recordSummary()

        # Test purpose
        #random.seed(1)

    # Wrapper getters to obtain essential objects
    def getBinary(self):      return self.EI.getBinary()
    def getObjects(self):     return self.EI.getObjects()
    def getFunctions(self):   return self.EI.getFunctions()
    def getBasicBlocks(self): return self.EI.getBasicBlocks()
    def getRandLayout(self):  return self.randLayout
    def getReorderInfo(self): return self.EI
    def getELFParser(self):   return self.EP
    def getRandBBs(self):     return self.randomizedBBContainer
    def getReport(self):      return self.R

    def __recordSummary(self):
        """ Bookkeeping the data of our interest """
        self.R.numObjs = self.EI.numObjects
        self.R.numFuns = self.EI.numFunctions
        self.R.numBBLs = self.EI.numBBs
        self.R.numFixupsText, self.R.numFixupsSpecial = self.getNumFixups(C.SEC_TEXT)
        self.R.numFixupsRodata = self.getNumFixups(C.SEC_RODATA)
        self.R.numFixupsData = self.getNumFixups(C.SEC_DATA)
        self.R.numFixupsRel = self.getNumFixups(C.SEC_DATA_REL)
        self.R.numFixupsInitArray = self.getNumFixups(C.SEC_INIT_ARR)

    def simulateShuffleBBLs(self, BBLs):
        """
        In case of basic block randomization, finding a possible reordering
          that meets BBL constraints (10 trials by default) as described in the paper
        :param BBLs:
        :return:
        """
        firstBBL = self.EI.getBasicBlock(BBLs[0][0])

        # Exclude BBL shuffling for a hand-written assembly case
        if firstBBL.parent.parent.srcKind == C.SRC_TYPE_ASSEMBLY:
            logging.debug("[Case 0] (F#%2d) Standalone Assembly: %s" \
                          % (firstBBL.parent.idx, BBLs))
            return BBLs

        # If there is a single BBL, no need to shuffle the bucket
        if len(BBLs) == 1:
            logging.debug("[Case 1] (F#%2d) Single BBL: %s" \
                          % (firstBBL.parent.idx, BBLs))
            return BBLs

        # If the size of this function is smaller than 128B, go shuffle it
        if firstBBL.parent.size < 128:
            logging.debug("[Case 2] (F#%2d) %dB < 128B" \
                      % (firstBBL.parent.idx, firstBBL.parent.size))
            random.shuffle(BBLs)
            logging.debug("\t\t%s (Success)", BBLs)
            self.R.entropyBBL.append(len(BBLs))
            return BBLs

        chkFixups = list()
        chkFixupsShortDist = list()
        for idx in sum(BBLs, []):
            BBL = self.EI.getBasicBlock(idx)
            for FI in BBL.Fixups:
                if FI.isRela and FI.derefSz < 4:
                    chkFixupsShortDist.append(FI)
                chkFixups.append(FI)

        # If there is no constraint in the BBL set, go shuffle it
        if len(chkFixupsShortDist) == 0:
            logging.debug("[Case 3] (F#%2d) No short distance fixups (<4B): %s" \
                    % (self.EI.getBasicBlock(BBLs[0][0]).parent.idx, BBLs))
            random.shuffle(BBLs)
            self.R.entropyBBL.append(len(BBLs))
            logging.debug("\t\t%s (Success)", BBLs)
            return BBLs

        import copy
        tryCnt = 0
        originalBBLs = copy.deepcopy(BBLs)
        originalList = sum(originalBBLs, [])

        logging.debug("[Case 4] (F#%2d) Simulation" \
                      % (self.EI.getBasicBlock(BBLs[0][0]).parent.idx))

        while True:
            random.shuffle(BBLs)
            tryCnt += 1

            simulateList = sum(BBLs, [])

            firstRandBBL = self.EI.getBasicBlock(simulateList[0])
            firstRandBBL.testVA = self.EI.getBasicBlock(originalList[0]).VA

            # Compute the VAs when BBLs have been relocated in simulateList
            for idx, bbi in enumerate(simulateList):
                if idx > 0:
                    prevBBL = self.EI.getBasicBlock(simulateList[idx-1])
                    curBBL = self.EI.getBasicBlock(simulateList[idx])
                    curBBL.testVA = prevBBL.testVA + prevBBL.size

            # Compute the refVal of the fixup accordingly
            anyFalseFixupRef = False
            for FI in chkFixupsShortDist:
                bblOffset = FI.VA - FI.parent.VA
                FI.testVA = FI.parent.testVA + bblOffset
                testRefVal = FI.refBB.testVA - (FI.testVA + FI.derefSz)
                if testRefVal <= -128 or testRefVal >= 128:
                    anyFalseFixupRef = True

            if not anyFalseFixupRef:
                logging.debug("\t\t%s (Success after %d attempts)" % (BBLs, tryCnt))
                self.R.entropyBBL.append(len(BBLs))
                return BBLs

            if tryCnt > 10:
                BBLs = copy.deepcopy(originalBBLs)
                logging.debug("\t\t%s (Failed after %d attempts)" % (BBLs, tryCnt))
                return BBLs

    def _generateRandTable(self, granularity=1):
        """
        This process has to resolve all constraints to meet
            a) intra-function BB-level randomization
            b) function-level randomization
            c) fallThrough blocks have to move around together
            d) maximum distances between BBLs due to derefSz in the fixup
            e) functions from hand-written assembly
        :return:
        """

        funcLayout = []

        # The following process discovers any reference pointing to the function outside
        # Such case will be viewed as a single function to satisfy the constraint (d)
        curFunc = self.getFunctions()[0]
        constCtr = 0
        prevMFSet = None

        while curFunc:
            mergedFuncs = set()
            chkBBLs = curFunc.BasicBlocks

            # In case of standalone assembly (e)
            # [Note] Assume that all fixups in the object refer to BBLs within
            if curFunc.parent.srcKind == C.SRC_TYPE_ASSEMBLY:
                while curFunc and curFunc.parent.srcKind == C.SRC_TYPE_ASSEMBLY:
                    mergedFuncs.add(curFunc.idx)
                    curFunc = curFunc.next

            else:
                for curBBL in chkBBLs:
                    if len(curBBL.Fixups) == 0:
                        mergedFuncs.add(curBBL.parent.idx)
                        continue
                    for fixup in curBBL.Fixups:
                        if fixup.type == 0 and fixup.derefSz < 4 and fixup.refBB:
                            funcFixupParent = fixup.parent.parent
                            funcFixupRefParent = fixup.refBB.parent
                            mergedFuncs.add(funcFixupParent.idx)

                            # The reference is pointing to the outside of this function
                            if funcFixupParent.idx != funcFixupRefParent.idx:
                                mergedFuncs.add(funcFixupRefParent.idx)
                                chkBBLs += funcFixupRefParent.BasicBlocks
                                curFunc = self.EI.getFunction(funcFixupRefParent.idx)
                        else:
                            mergedFuncs.add(curBBL.parent.idx)

            MF = sorted(mergedFuncs)

            if len(MF) > 1:
                MF = range(MF[0], MF[-1] + 1)

                # Handling the special case when the current function set has the intersection
                #  of the previous set - should be combined together before further proceeding
                if prevMFSet:
                    overlapped = len(set(MF).intersection(set(prevMFSet)))
                    if overlapped > 0:
                        MF = range(min(min(MF), min(prevMFSet)), max(max(MF), max(prevMFSet)) + 1)
                        funcLayout = [x for x in funcLayout if len(set(MF).intersection(x)) == 0]
                        funcLayout.append(MF)
                    else:
                        funcLayout.append(MF)
                else:
                    funcLayout.append(MF)

                prevMFSet = MF

                if len(set([MF[x + 1] - MF[x] for x in range(len(MF) - 1)])) > 1:
                    logging.critical("\tThe merged function set contains non-consecutive functions")

                #assert (len(set([MF[x + 1] - MF[x] for x in range(len(MF) - 1)])) == 1), \
                #    "The merged function set contains non-consecutive functions"
                constCtr += 1

            else:
                funcLayout.append(MF)
                prevMFSet = MF

            # [Note] Assume that compiler would generate functions close enough to refer from
            #        such BBLs that have short distance references (i.e., -128 <= d < 127)
            #        Otherwise this assumption could be problematic because of a skip-over function
            curFunc = self.EI.getFunction(funcLayout[-1][-1]).next

        logging.debug("\tFunction Layout with Constraints: %s", funcLayout)
        logging.info("\t# of Function Constraints: %d", constCtr)
        if len(sum(funcLayout, [])) != self.EI.numFunctions:
            logging.critical("\t# of Functions: %d VS # of elements in funcLayout: %d " \
                             % (self.EI.numFunctions, len(sum(funcLayout,[]))))

        #assert(len(sum(funcLayout, [])) == self.EI.numFunctions), \
        #    "# of Functions: %d VS # of elements in funcLayout: %d " % \
        #    (self.EI.numFunctions, len(sum(funcLayout,[])))

        '''
        Now reorder the Basic Blocks within each Function Layout
        Similarly canFallThrough BBL constraint (c) can be dealt with (d)
        '''
        if granularity > 0:
            logging.debug("Shuffling at the BBL granularity...")

        for F in funcLayout:
            BBLs = []

            # If there are multiple functions satisfying (d), merge those BBLs
            # This case can be considered as a bulk of intact BBLs (quite rare though)
            if len(F) > 1:
                mergedBBL = set()
                for f in F:
                    for bbl in self.EI.getFunction(f).BasicBlocks:
                        mergedBBL.add(bbl.idx)
                BBLs.append(sorted(mergedBBL))

            else:
                f = self.EI.getFunction(F[0])
                curBBL = f.BasicBlocks[0]

                # Combine the hasFallThrough BBL with the next one (c)
                while curBBL and f.BasicBlocks[0].idx <= curBBL.idx <= f.BasicBlocks[-1].idx:
                    if not curBBL.hasFallThrough:
                        BBLs.append([curBBL.idx])
                        curBBL = curBBL.next
                    else:
                        tmpBBL = curBBL
                        combined = [curBBL.idx]
                        while tmpBBL.hasFallThrough:
                            tmpBBL = tmpBBL.next
                            combined.append(tmpBBL.idx)
                        BBLs.append(combined)
                        curBBL = tmpBBL.next

            # Simulate transformation that references fit into a single byte distance each other
            if granularity > 0:
                BBLs = self.simulateShuffleBBLs(BBLs)

            self.randLayout.append(BBLs)

        # Reorder the Functions - it is safe because the compartmentalized bulks meet all constraints
        random.shuffle(self.randLayout)
        funEntropy = len(self.randLayout)
        self.R.entropyFun = funEntropy

        logging.debug("Shuffling at the FUN granularity...")
        logging.debug("Final Function Layout with Constraints: %s", funcLayout)
        logging.debug("Final BBL Layout with Constraints: %s", self.randLayout)

        # Unnest the nested list containing BBLs
        self.randLayout = reduce(lambda x, y: x + y,
                                reduce(lambda x, y: x + y, self.randLayout, []), [])

        # Maintain BBLs in a randomized order
        self.randomizedBBContainer = [self.EI.getBasicBlock(bbi) for bbi in self.randLayout]

    def performTransformation(self, granularity=0):
        """
        Once the randomized layout is determined, references require to be recomputed accordingly
        This method contains one of the core reordering processes.
            a) Update new VAs of the randomized BBLs (or functions)
            b) Update all fixups in [.rodata|.data.rel.ro|.data] sections
                according to randomized functions and/or basic blocks in .text section
        :param DEBUG:
        :return:
        """
        # Prepare for a lookup table to contain the order of randomized BBs
        # TODO - Later, this has to be used for de-randomization
        self._generateRandTable(granularity)

        # [Step 1] Set the first basic block after randomization
        beginOffset = self.EI.getBasicBlocks()[0].offsetFromBase
        firstRandBBL = self.randomizedBBContainer[0]
        base = firstRandBBL.VA - firstRandBBL.offsetFromBase
        firstRandBBL.newOffsetFromSection = beginOffset
        firstRandBBL.newVA = base + firstRandBBL.newOffsetFromSection
        firstRandBBL.adjustedBytes = firstRandBBL.newVA - firstRandBBL.VA

        # [Step 2] Set the following basic blocks accordingly: newVA, adjustedBytes
        for idx, bbi in enumerate(self.randLayout):
            if idx > 0:
                prevBBL = self.EI.getBasicBlock(self.randLayout[idx - 1])
                BBL = self.EI.getBasicBlock(bbi)
                BBL.newOffsetFromSection = prevBBL.newOffsetFromSection + prevBBL.size
                BBL.newVA = base + BBL.newOffsetFromSection
                BBL.adjustedBytes = BBL.newVA - BBL.VA

        # [Step 3] Compute newOffset, newRefVal, newVA and newRefTo in .text section
        jumpTables = dict() # VA: (numJTEntries, jtEntrySz)
        if self.hasFixupsInText():
            for FI in self.getFixupsText():
                # For the fixups in standalone assembly, just skip them to update
                if FI.parent.parent.parent.srcKind == C.SRC_TYPE_ASSEMBLY:
                    continue

                # For fixups in .text, newVA needs to be updated
                FIOffsetBBL = FI.VA - FI.parent.VA
                FI.newVA = FI.parent.newVA + FIOffsetBBL
                FI.newOffset = FI.newVA - base

                # If the fixup contains the absolute address and C2C type,
                # update it to the reordered address (pointing to the original BBL)
                # otherwise leave it as it is. (C2D type)
                if not FI.isRela:
                    if FI.type == C.FT_C2C:
                        try:
                            FI.newRefVal = FI.refBB.newVA
                            FI.newRefTo = FI.newRefVal
                        except AttributeError:
                            # Exception when any orphan fixup exists
                            FI.newRefVal = FI.newRefTo = FI.refTo
                            logging.warning("\t(%s) [Possibly CFI/LTO] Check out Fixup [%d] RefBB: %s, newRefTo: 0x%x, Type: %d" % \
                                             (C.SEC_TEXT, FI.idx, FI.refBB, FI.newRefVal, FI.type))
                    else:
                        FI.newRefVal = FI.derefVal
                        FI.newRefTo = FI.refTo

                else:
                    # FI.VA + refVal + derefSz = RefTo
                    # newRefVal = RefTo - FI.newVA - derefSz
                    FI.newRefTo = FI.refBB.newVA if FI.refBB else FI.refTo
                    FI.newRefVal = FI.newRefTo - FI.newVA - FI.derefSz

                # The following information will be used to update entries in .rodata
                if FI.numJTEntries > 0:
                    jumpTables[FI.refTo] = (FI.parent.parent, FI.numJTEntries, FI.jtEntrySz)

        def updateFixupRefs1(fixups, secName, jumpTables):
            """ Update the fixups for .rodata and .data.rel.ro sections """
            pivot, numJTEntries, jtEntrySz = 0x0, 0, 0
            for FI in fixups:
                if FI.type == C.FT_D2D:    # Do not touch the case of D2D
                    FI.newRefVal = FI.derefVal
                    FI.newRefTo = FI.refTo
                    continue

                # If the fixup corresponds to any jump table
                if FI.VA in jumpTables:
                    pivot = FI.VA
                    fixupFunc, numJTEntries, jtEntrySz = jumpTables[pivot]

                # If the fixup contains absolute value, it is straightforward to update
                if not FI.isRela:
                    try:
                        FI.newRefVal = FI.refBB.newVA
                        FI.newRefTo = FI.newRefVal
                        logging.debug("\t(%s) Fixup [%d] RefBB: %s, RefVal: 0x%x, RefTo: 0x%x, Type: %d" % \
                                      (secName, FI.idx, FI.refBB, FI.newRefVal, FI.newRefTo, FI.type))

                        '''
                        # [NEW] For cross reference trace, use the jump table (indirect pointers)
                        if pivot <= FI.VA < pivot + (numJTEntries * jtEntrySz):
                            refFunc = self.EI.getBBlByVA(FI.derefVal).parent
                            fixupFunc.refTos.add(refFunc)
                            refFunc.refFroms.add(fixupFunc)
                        '''

                    except AttributeError:
                        # Exception when any orphan fixup exists
                        FI.newRefVal = FI.newRefTo = FI.refTo
                        logging.warning("\t(%s) [Possibly CFI/LTO] Check out Fixup [%d] RefBB: %s, newRefVal: 0x%x, Type: %d" % \
                                        (secName, FI.idx, FI.refBB, FI.newRefVal, FI.type))

                # If the fixup contains relative value [RV] (pie/pic)
                #    a) non-JT: newRV = BBL(VA + RV).newVA - VA
                #    b) JT:     newRV = BBL(pivot + RV).newVA - pivot (where pivot = JT location)
                # PIE/PIC (position independent) binary falls into this category
                else:
                    # If Fixup is the entry of this jump table, adjust the relative value accordingly
                    if pivot <= FI.VA < pivot + (numJTEntries * jtEntrySz):
                        FI.newRefTo = self.EI.getBBlByVA(pivot + FI.derefVal).newVA
                        FI.newRefVal = FI.newRefTo - pivot
                        logging.debug("\t(%s) [PIE] Fixup@0x%x: RV=0x%x, Pivot=0x%x, newRefTo=0x%x, newRefVal=0x%x"
                                     % (secName, FI.VA, FI.derefVal, pivot, FI.newRefTo, FI.newRefVal))

                        '''
                        # [NEW] For cross reference trace, use the jump table (indirect pointers)
                        refFunc = self.EI.getBBlByVA(pivot + FI.derefVal).parent
                        fixupFunc.refTos.add(refFunc)
                        refFunc.refFroms.add(fixupFunc)
                        '''

                    else:
                        FI.newRefTo = self.EI.getBBlByVA(FI.VA + FI.derefVal).newVA
                        FI.newRefVal = FI.newRefTo - FI.VA
                        logging.debug("\t(%s) [PIE] Fixup@0x%x: RV=0x%x, newRefTo=0x%x, newRefVal=0x%x"
                                     % (secName, FI.VA, FI.derefVal, FI.newRefTo, FI.newRefVal))

        # [Step 4] Compute newRefVal and newRefTo in .rodata/.data.rel.ro section
        if self.hasFixupsInRodata():
            updateFixupRefs1(self.getFixupsRodata(), C.SEC_RODATA, jumpTables)

        if self.hasFixupsInDataRel():
            updateFixupRefs1(self.getFixupsDataRel(), C.SEC_DATA_REL, jumpTables)

        # FIXME - Did not combine updateFixupRefs2 with updateFixupRefs1 for better readability
        def updateFixupRefs2(fixups, secName):
            """ Update the fixups for .data and .init_array sections """
            for FI in fixups:
                if FI.type == C.FT_D2D and secName is not C.SEC_INIT_ARR:    # Do not touch the case of D2D
                    FI.newRefVal = FI.derefVal
                    FI.newRefTo = FI.refTo
                    continue

                if not FI.isRela:
                    try:
                        FI.newRefVal = FI.refBB.newVA
                        FI.newRefTo = FI.newRefVal
                        logging.debug("\t(%s) Fixup [%d] RefBB: %s, RefVal: 0x%x, RefTo: 0x%x, Type: %d" % \
                                    (secName, FI.idx, FI.refBB, FI.newRefVal, FI.newRefTo, FI.type))
                    except AttributeError:
                        # Exception when any orphan fixup exists
                        FI.newRefVal = FI.newRefTo = FI.refTo
                        additionalMsg = ' [Possibly CFI / LTO]' if not secName == C.SEC_INIT_ARR else ''
                        logging.warning("\t(%s)%s Check out Fixup [%d] RefBB: %s, newRefTo: 0x%x, Type: %d" % \
                                        (secName, additionalMsg, FI.idx, FI.refBB, FI.newRefVal, FI.type))
                else:
                    # Have not found any case that falls into this category
                    # All fixup entries in .data seems absolute addresses even under PIE
                    logging.critical("\t(%s) Relative fixup in this section?! [NEW]" % (secName))
                    pass

        # [Step 5] Compute newRefVal and newRefTo in the following sections: .data and .init_array
        if self.hasFixupsInData():
            updateFixupRefs2(self.getFixupsData(), C.SEC_DATA)
        if self.hasFixupsInInitArray():
            updateFixupRefs2(self.getFixupsInitArray(), C.SEC_INIT_ARR)

    def showRandLayout(self):
        """ Show the randomized layout and all updated fixups accordinly """
        def showFixups(allFixups, secName):
            logging.info('Fixups in %s section' % (secName))
            for FI in allFixups:
                logging.info(FI)
                logging.info("\t==> newVal=0x%08x, newRefTo=0x%08x" % (FI.newRefVal, FI.newRefTo))

        logging.info('Code Layout in a Randomized Binary in Details')
        for idx in self.randLayout:
            BBL = self.EI.getBasicBlock(idx)
            logging.info(BBL)
            logging.info("\t==> newSecOff=0x%08x, newVA=0x%08x (Adj %3dB)" \
                         % (BBL.newOffsetFromSection, BBL.newVA, BBL.adjustedBytes))
            for FI in BBL.Fixups:
                logging.info(FI)
                logging.info("\t\t==>@0x%08x, newSecOff=0x%04x, newRefVal=0x%08x, newRefTo=0x%08x" \
                             % (FI.newVA, FI.newOffset, FI.newRefVal, FI.newRefTo))

        if self.hasFixupsInRodata():
            showFixups(self.getFixupsRodata(), C.SEC_RODATA)

        if self.hasFixupsInData():
            showFixups(self.getFixupsData(), C.SEC_DATA)

        if self.hasFixupsInDataRel():
            showFixups(self.getFixupsDataRel(), C.SEC_DATA_REL)

        if self.hasFixupsInInitArray():
            showFixups(self.getFixupsInitArray(), C.SEC_INIT_ARR)
