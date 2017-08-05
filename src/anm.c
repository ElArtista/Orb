#include <orb/anm.h>
#include <string.h>

void anm_parse_from_buf(struct anm_file* a, byte* buf, u32 buf_sz)
{
    (void) buf_sz;
    memcpy(&a->header, buf, sizeof(a->header));
    a->joints      = (void*)(buf + a->header.joints.offset);
    a->frame_infos = (void*)(buf + a->header.frame_infos.offset);
    a->changes     = (void*)(buf + a->header.changes.offset);
}
