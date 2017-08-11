#include <orb/mdl.h>
#include <string.h>

void mdl_parse_from_buf(struct mdl_file* m, byte* buf, u32 buf_sz)
{
    (void) buf_sz;
    memcpy(&m->header, buf, sizeof(m->header));
    m->mesh_desc      = (void*)(buf + m->header.mesh_descs.offset);
    m->va_desc        = (void*)(buf + m->header.va_desc.offset);
    m->va_data        = (void*)(buf + m->header.va_data.offset);
    m->indices        = (void*)(buf + m->header.indices.offset);
    m->joints         = (void*)(buf + m->header.joints.offset);
    m->joint_name_ofs = (void*)(buf + m->header.joint_name_ofs.offset);
    m->strings        = (void*)(buf + m->header.strings.offset);
}
