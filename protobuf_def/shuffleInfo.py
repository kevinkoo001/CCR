import shuffleInfo_pb2
import os, sys
from util import hexPrint as HP

sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), os.pardir))

def deserializeInfo(reorder_info):
    print "Key: ", hex(reorder_info.secret_key)

    bin_info = reorder_info.binInfo
    obj_info = reorder_info.objInfo
    fun_info = reorder_info.funInfo
    bbk_info = reorder_info.bbkInfo
    ref_info = reorder_info.refInfo
    ref_info_ro = reorder_info.refInfoRO

    obj_size, obj_func_cnt = [], []
    fun_size, fun_bb_cnt   = [], []
    bbk_size, bbk_fixup_cnt  = [], []
    fixup_deref_size, fixup_offset, fixup_is_rela = [], [], []
    fixup_deref_size_ro, fixup_offset_ro, fixup_is_rela_ro = [], [], []

    print "Main Addr Offset     : 0x%08x" % bin_info.main_addr_offset_from_text
    print "Reorder Object Offset: 0x%08x" % bin_info.reorder_obj_start_from_text
    print "Number of Objects    : %d" % bin_info.num_objs_for_bin

    for i in range(len(obj_info)):
        obj_size.append(obj_info[i].obj_size)
        obj_func_cnt.append(obj_info[i].num_funcs_per_obj)

    for j in range(len(fun_info)):
        fun_size.append(fun_info[j].fun_size)
        fun_bb_cnt.append(fun_info[j].num_bbks_per_func)

    for k in range(len(bbk_info)):
        bbk_size.append(bbk_info[k].bbk_size)
        bbk_fixup_cnt.append(bbk_info[k].num_refs_per_bbk)

    for l in range(len(ref_info)):
        fixup_offset.append(ref_info[l].ref_offset_from_func)
        fixup_deref_size.append(ref_info[l].deref_size)
        fixup_is_rela.append(ref_info[l].is_relative)

    for m in range(len(ref_info_ro)):
        fixup_offset_ro.append(ref_info_ro[m].ref_offset_from_func_ro)
        fixup_deref_size_ro.append(ref_info_ro[m].deref_size_ro)
        fixup_is_rela_ro.append(ref_info_ro[m].is_relative_ro)

    print "obj_size", obj_size
    print "obj_func_cnt", obj_func_cnt

    print "fun_size", fun_size
    print "fun_bb_cnt", fun_bb_cnt

    print "bbk_size", bbk_size
    print "bbk_fixup_cnt", bbk_fixup_cnt

    print "fixup_deref_size", fixup_deref_size
    print "fixup_offset", fixup_offset
    print "fixup_is_rela", fixup_is_rela

    print "fixup_deref_size_ro", fixup_deref_size_ro
    print "fixup_offset_ro", fixup_offset_ro
    print "fixup_is_rela_ro", fixup_is_rela_ro

if __name__ == '__main__':

    if len(sys.argv) != 2:
      print "Usage:", sys.argv[0], "INFO_FILE"
      sys.exit(-1)

    reorder_info = shuffleInfo_pb2.ReorderInfo()

    # Read the existing address book.
    f = open(sys.argv[1], "rb")
    reorder_info.ParseFromString(f.read())
    f.close()

    deserializeInfo(reorder_info)