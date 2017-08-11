/*********************************************************************************************************************/
/*                                                  /===-_---~~~~~~~~~------____                                     */
/*                                                 |===-~___                _,-'                                     */
/*                  -==\\                         `//~\\   ~~~~`---.___.-~~                                          */
/*              ______-==|                         | |  \\           _-~`                                            */
/*        __--~~~  ,-/-==\\                        | |   `\        ,'                                                */
/*     _-~       /'    |  \\                      / /      \      /                                                  */
/*   .'        /       |   \\                   /' /        \   /'                                                   */
/*  /  ____  /         |    \`\.__/-~~ ~ \ _ _/'  /          \/'                                                     */
/* /-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                                                      */
/*                   \_|      /        _)   ;  ),   __--~~                                                           */
/*                     '~~--_/      _-~/-  / \   '-~ \                                                               */
/*                    {\__--_/}    / \\_>- )<__\      \                                                              */
/*                    /'   (_/  _-~  | |__>--<__|      |                                                             */
/*                   |0  0 _/) )-~     | |__>--<__|     |                                                            */
/*                   / /~ ,_/       / /__>---<__/      |                                                             */
/*                  o o _//        /-~_>---<__-~      /                                                              */
/*                  (^(~          /~_>---<__-      _-~                                                               */
/*                 ,/|           /__>--<__/     _-~                                                                  */
/*              ,//('(          |__>--<__|     /                  .----_                                             */
/*             ( ( '))          |__>--<__|    |                 /' _---_~\                                           */
/*          `-)) )) (           |__>--<__|    |               /'  /     ~\`\                                         */
/*         ,/,'//( (             \__>--<__\    \            /'  //        ||                                         */
/*       ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'                                          */
/*     `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                                                     */
/*   ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                                                       */
/*    ;'( ')/ ,)(                              ~~~~~~~~~~                                                            */
/*   ' ') '( (/                                                                                                      */
/*     '   '  `                                                                                                      */
/*********************************************************************************************************************/
#ifndef _MDL_H_
#define _MDL_H_

#include "types.h"

#define MDL_MAGIC "MDL"
#define MDL_INVALID_OFFSET 0xFFFFFFFF

/* float, 3 (default) */
#define MDL_POSITION      0
/* float, 3 (default) */
#define MDL_NORMAL        1
/* float, 3 (default) */
#define MDL_TANGENT       2
/* float, 2 (default) */
#define MDL_TEXCOORD0     3
/* float, 2 (default) */
#define MDL_TEXCOORD1     4
/* u16,   4 (default) */
#define MDL_BLEND_INDEXES 5
/* float, 4 (default) */
#define MDL_BLEND_WEIGHTS 6
/* Any value >= MDL_CUSTOM is interpreted as a custom type */
#define MDL_CUSTOM        7

/* 1 byte  */
#define MDL_BYTE   0
/* 2 bytes */
#define MDL_SHORT  1
/* 2 bytes */
#define MDL_USHORT 2
/* 4 bytes */
#define MDL_INT    3
/* 4 bytes */
#define MDL_UINT   4
/* 8 bytes */
#define MDL_LONG   5
/* 8 bytes */
#define MDL_ULONG  6
/* 4 bytes */
#define MDL_FLOAT  7
/* 8 bytes */
#define MDL_DOUBLE 8

/* Model File */
struct mdl_file {
    /* Header */
    struct mdl_header {
        /* File identifier {0x4D, 0x44, 0x4C, 0x00} */
        byte id[4];
        /* Version {0x00, 0x01} */
        struct {
            u16 maj;
            u16 min;
        } ver;
        /* Flags:
         *  Bit 0: Rigged
         *  Bit 1-31: Unused */
        struct {
            int rigged : 1;
            int unused : 31;
        } flags;
        /* Number of vertices (total) */
        u32 num_vertices;
        /* Number of indices (total) */
        u32 num_indices;
        /* Number of mesh descriptors */
        u32 num_mesh_descs;
        /* Number of vertex arrays */
        u16 num_vertex_arrays;
        /* Number of joints */
        u16 num_joints;
        /* Number of strings */
        u32 num_strings;
        /* Data chunk of mesh descriptors */
        data_chunk mesh_descs;
        /* Data chunk of vertex array descriptors */
        data_chunk va_desc;
        /* Data chunk of vertex arrays */
        data_chunk va_data;
        /* Data chunk of indices */
        data_chunk indices;
        /* Data chunk of joints */
        data_chunk joints;
        /* Data chunk of array of joint name offsets */
        data_chunk joint_name_ofs;
        /* Data chunk of strings */
        data_chunk strings;
    } header;

    /* Array of mesh descriptors */
    struct mdl_mesh_desc {
        /* Name offset in strings */
        u32 ofs_name;
        /* Number of vertices */
        u32 num_vertices;
        /* Number of indices */
        u32 num_indices;
        /* Material reference index */
        u16 mat_idx;
    }* mesh_desc;

    /* Array of vertex array descriptors */
    struct mdl_vertex_array {
        /* Type of vertex array data */
        u8 type;
        /* Format of vertex array data */
        u8 format;
        /* Number of components for each element */
        u16 num_components;
        /* Length of vertex array */
        u32 size;
        /* Offset to data (relative to vertex_array_data field) */
        u32 ofs_data;
    }* va_desc;

    /* Array of vertex data */
    byte* va_data;

    /* Array of indices */
    u32* indices;

    /* Array of joints
     *  - Transforms are absolute, not relative to parent */
    struct mdl_joint {
        /* Reference to parent (index to current array) */
        u32 ref_parent;
        /* Position */
        f32 position[3];
        /* Rotation (quaternion) */
        f32 rotation[4];
        /* Scaling */
        f32 scaling[3];
    }* joints;

    /* Array of joint name offsets */
    u32* joint_name_ofs;

    /* Strings data
     *  - Contains contatenated list of strings null terminated strings */
    const char* strings;
};

void mdl_parse_from_buf(struct mdl_file* m, byte* buf, u32 buf_sz);

#endif /* ! _MDL_H_ */
