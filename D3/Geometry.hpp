//
//  Geometry.hpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Geometry_hpp
#define _Geometry_hpp

namespace d3 {
    class Geometry {
    protected:
        ArrayDescriptor<unsigned int> * indices_;
        ArrayDescriptor<float> * vertex_array_;
        ArrayDescriptor<float> * normal_array_;
        ArrayDescriptor<float> * tex_coord_array_;
        ArrayDescriptor<float> * color_array_;
        
        unsigned int geometry_type_;
        
    public:
        Geometry() :  vertex_array_(nullptr), normal_array_(nullptr), tex_coord_array_(nullptr),
                        color_array_(nullptr), indices_(nullptr) {}
        
        SETGET(unsigned int, geometry_type_, GeometryType)
        SETGET(ArrayDescriptor<unsigned int> *, indices_, Indices)
        SETGET(ArrayDescriptor<float> *, vertex_array_, VertexArray)
        SETGET(ArrayDescriptor<float> *, normal_array_, NormalArray)
        SETGET(ArrayDescriptor<float> *, tex_coord_array_, TexCoordArray)
        SETGET(ArrayDescriptor<float> *, color_array_, ColorArray)
    };
}

#endif
