//
//  Geometry.hpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Geometry_hpp
#define _Geometry_hpp

#include <iostream>

namespace d3 {
    class GLProgram;
    
    class Geometry {
    protected:
        shared_ptr<unsigned int> indices_;
        shared_ptr<float> vertex_array_;
        shared_ptr<float> normal_array_;
        shared_ptr<float> tex_coord_array_;
        shared_ptr<float> color_array_;
        
        unsigned int vertex_stride_;
        unsigned int normal_stride_;
        unsigned int tex_coord_stride_;
        unsigned int color_stride_;
        
        unsigned int geometry_type_;
        unsigned int size_;
        
    public:
        Geometry(shared_ptr<float> vertex_array, unsigned int size)
            : vertex_array_(vertex_array), size_(size) {}
        
        Geometry(shared_ptr<float> vertex_array, shared_ptr<unsigned int> indices, unsigned int size)
            : vertex_array_(vertex_array), indices_(indices), size_(size) {}
        
        ~Geometry() {}
        
        SETGET(unsigned int, geometry_type_, GeometryType)
        SETGET(unsigned int, size_, Size)
        
        SETGET(shared_ptr<unsigned int>, indices_, Indices)
        SETGET(shared_ptr<float>, vertex_array_, VertexArray)
        SETGET(shared_ptr<float>, normal_array_, NormalArray)
        SETGET(shared_ptr<float>, tex_coord_array_, TexCoordArray)
        SETGET(shared_ptr<float>, color_array_, ColorArray)
        
        SETGET(unsigned int, vertex_stride_, VertexPointerStride)
        SETGET(unsigned int, normal_stride_, NormalPointerStride)
        SETGET(unsigned int, tex_coord_stride_, TexCoordPointerStride)
        SETGET(unsigned int, color_stride_, ColorPointerStride)
    };
}

#endif
