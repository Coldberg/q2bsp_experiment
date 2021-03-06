//
//  bsp_common.cpp
//  Bsp_Take0
//
//  Created by Aleksandras Sevcenko on 3/17/16.
//  Copyright © 2016 Aleksandr Ševčenko. All rights reserved.
//

#ifndef __XTK_BSP_COMMON_HPP__
#define __XTK_BSP_COMMON_HPP__

#include <glm/glm.hpp>
#include <cstddef>
#include <cstdint>
#include <array>

#pragma pack(push, 1)

namespace xtk {

    typedef glm::tvec3<std::int16_t>    bsp_point3s;
    typedef glm::tvec3<float>           bsp_point3f;
    typedef glm::tvec2<std::int16_t>    bsp_point2s;
    typedef glm::tvec2<float>           bsp_point2f;
    typedef std::array<std::int16_t, 2> bsp_edge2s;
    
    static_assert (sizeof (bsp_point3s) == 6, "Wrong size");
    static_assert (sizeof (bsp_point3f) == 12, "Wrong size");
    static_assert (sizeof (bsp_point2s) == 4, "Wrong size");
    static_assert (sizeof (bsp_point2f) == 8, "Wrong size");
    
    enum bsp_version {
        bsp_version_quake2 = 0x26
    };
    
    struct bsp_lump {
        std::uint32_t offset;
        std::uint32_t length;
    };
    
    struct bsp_header {
        std::uint32_t signature;
        std::uint32_t version;
        union {
            struct {
                bsp_lump entities;           // 0
                bsp_lump planes;             // 1
                bsp_lump vertices;           // 2
                bsp_lump visibility;         // 3
                bsp_lump nodes;              // 4
                bsp_lump texinfo;            // 5
                bsp_lump faces;              // 6
                bsp_lump lightmaps;          // 7
                bsp_lump leaves;             // 8
                bsp_lump leaf_face_list;     // 9
                bsp_lump leaf_brush_list;    // 10
                bsp_lump edges;              // 11
                bsp_lump face_edge_list;     // 12
                bsp_lump models;             // 13
                bsp_lump brushes;            // 14
                bsp_lump brush_sides;        // 15
                bsp_lump pop;                // 16
                bsp_lump areas;              // 17
                bsp_lump area_portals;       // 18
            };
            bsp_lump all_lumps [19u];
        };
    };
    
    struct bsp_face {
        std::uint16_t   plane;             // index of the plane the face is parallel to
        std::uint16_t   plane_side;        // set if the normal is parallel to the plane normal

        std::uint32_t   first_edge;        // index of the first edge (in the face edge array)
        std::uint16_t   num_edges;         // number of consecutive edges (in the face edge array)
        
        std::uint16_t   texture_info;      // index of the texture info structure
       
        std::uint8_t    lightmap_syles[4]; // styles (bit flags) for the lightmaps
        std::uint32_t   lightmap_offset;   // offset of the lightmap (in bytes) in the lightmap lump
    };
    
    struct bsp_plane {
        bsp_point3f     normal;
        float           distance;
        std::uint32_t   type;
    };
    
    struct bsp_node {
        std::uint32_t   plane;             // index of the splitting plane (in the plane array)
    
        std::int32_t    front_child;       // index of the front child node or leaf
        std::int32_t    back_child;        // index of the back child node or leaf
   
        bsp_point3s     bbox_min;          // minimum x, y and z of the bounding box
        bsp_point3s     bbox_max;          // maximum x, y and z of the bounding box
	
        std::uint16_t   first_face;        // index of the first face (in the face array)
        std::uint16_t   num_faces;         // number of consecutive edges (in the face array)
    };
    
    
    struct bsp_leaf {
   
        std::uint32_t   brush_or;          // ?
	
        std::uint16_t   cluster;           // -1 for cluster indicates no visibility information
        std::uint16_t   area;              // ?

        bsp_point3s     bbox_min;          // bounding box minimums
        bsp_point3s     bbox_max;          // bounding box maximums

        std::uint16_t   first_leaf_face;   // index of the first face (in the face leaf array)
        std::uint16_t   num_leaf_faces;    // number of consecutive edges (in the face leaf array)

        std::uint16_t   first_leaf_brush;  // ?
        std::uint16_t   num_leaf_brushes;  // ?

    };
    
    struct bsp_texinfo {

        bsp_point3f     u_axis;
        float           u_offset;
   
        bsp_point3f     v_axis;
        float           v_offset;

        std::uint32_t   flags;
        std::uint32_t   value;

        char            texture_name[32];

        std::uint32_t   next_texinfo;
    };
    
    struct bsp_vis_offset {

        std::uint32_t   pvs;   // offset (in bytes) from the beginning of the visibility lump
        std::uint32_t   phs;   // ?

    };
    
    struct wal_header {

        char            name[32];        // name of the texture
 
        std::uint32_t   width;           // width (in pixels) of the largest mipmap level
        std::uint32_t   height;          // height (in pixels) of the largest mipmap level
 
        std::int32_t    offset[4];       // byte offset of the start of each of the 4 mipmap levels

        char            next_name[32];   // name of the next texture in the animation

        std::uint32_t   flags;           // ?
        std::uint32_t   contents;        // ?
        std::uint32_t   value;           // ?

    };

}

#pragma pack(pop)

#endif