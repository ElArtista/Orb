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
#ifndef _ANM_H_
#define _ANM_H_

#include "types.h"

/* Animation change components */
#define ANM_COMP_UNKN (1 << 0)
#define ANM_COMP_POSX (1 << 1)
#define ANM_COMP_POSY (1 << 2)
#define ANM_COMP_POSZ (1 << 3)
#define ANM_COMP_ROTX (1 << 4)
#define ANM_COMP_ROTY (1 << 5)
#define ANM_COMP_ROTZ (1 << 6)
#define ANM_COMP_ROTW (1 << 7)
#define ANM_COMP_SCLX (1 << 8)
#define ANM_COMP_SCLY (1 << 9)
#define ANM_COMP_SCLZ (1 << 10)

/* Animation File */
struct anm_file {
    /* Header */
    struct anm_header {
        /* File identifier {0x41, 0x4E, 0x4D, 0x00} */
        byte id[4];
        /* Version {0x00, 0x01} */
        struct {
            u16 maj;
            u16 min;
        } ver;
        /* Frame rate */
        f32 frame_rate;
        /* Number of joints */
        u16 num_joints;
        /* Number of joints */
        u16 num_frames;
        /* Number of changes */
        u32 num_changes;
        /* Data chunk of joints */
        data_chunk joints;
        /* Data chunk of frame infos */
        data_chunk frame_infos;
        /* Data chunk of changes */
        data_chunk changes;
    } header;

    /* Array of joints (base frame)
     *  - Transforms are absolute, not relative to parent */
    struct anm_joint {
        /* Parent index */
        u32 par_idx;
        /* Position */
        f32 position[3];
        /* Rotation (quaternion) */
        f32 rotation[4];
        /* Scaling */
        f32 scaling[3];
    }* joints;

    /* Array of frame infos */
    struct anm_frame_info {
        /* Number of changes belonging to this frame */
        u16 num_changes;
    }* frame_infos;

    /* Array of animation changes */
    struct anm_change {
        /* Joint index */
        u16 joint_idx;
        /* Components filled in */
        u16 components;
        /* Position */
        f32 pos[3];
        /* Rotation */
        f32 rot[4];
        /* Scale */
        f32 scl[3];
    }* changes;
};

void anm_parse_from_buf(struct anm_file* a, byte* buf, u32 buf_sz);

#endif /* ! _ANM_H_ */
