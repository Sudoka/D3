//
//  d3Geometry.hpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Geometry_hpp
#define D3_d3Geometry_hpp

namespace d3 {
    class d3Geometry {
    protected:
        d3ArrayDescriptor<unsigned int> * indices_;
        d3ArrayDescriptor<float> * vertex_array_;
        d3ArrayDescriptor<float> * normal_array_;
        d3ArrayDescriptor<float> * tex_coord_array_;
        d3ArrayDescriptor<float> * color_array_;
        
        unsigned int geometry_type_;
        
    public:
        d3Geometry() :  vertex_array_(nullptr), normal_array_(nullptr), tex_coord_array_(nullptr),
                        color_array_(nullptr), indices_(nullptr) {}
        
        SETGET(unsigned int, geometry_type_, GeometryType)
        SETGET(d3ArrayDescriptor<unsigned int> *, indices_, Indices)
        SETGET(d3ArrayDescriptor<float> *, vertex_array_, VertexArray)
        SETGET(d3ArrayDescriptor<float> *, normal_array_, NormalArray)
        SETGET(d3ArrayDescriptor<float> *, tex_coord_array_, TexCoordArray)
        SETGET(d3ArrayDescriptor<float> *, color_array_, ColorArray)
    };
}

#endif
