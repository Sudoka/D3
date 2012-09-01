//
//  d3Geometry.cpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Geometry.hpp"

namespace d3 {
    d3Geometry::d3Geometry()
    :
    vertex_array_(nullptr),
    normal_array_(nullptr),
    tex_coord_array_(nullptr),
    color_array_(nullptr),
    indices_(nullptr)
    {
    }
    
    void d3Geometry::setGeometryType(unsigned int geometry_type)
    {
        geometry_type_ = geometry_type;
    }
    
    unsigned int d3Geometry::getGeometryType()
    {
        return geometry_type_;
    }
    
    void d3Geometry::setVertexArray(d3ArrayDescriptor<float> * vertex_array)
    {
        vertex_array_ = vertex_array;
    }
    
    d3ArrayDescriptor<float> * d3Geometry::getVertexArray() const
    {
        return vertex_array_;
    }
    
    void d3Geometry::setIndices(d3ArrayDescriptor<unsigned int> * indices)
    {
        indices_ = indices;
    }
    
    d3ArrayDescriptor<unsigned int> * d3Geometry::getIndices() const
    {
        return indices_;
    }
    
    void d3Geometry::setNormalArray(d3ArrayDescriptor<float> * normal_array)
    {
        normal_array_ = normal_array;
    }
    
    d3ArrayDescriptor<float> * d3Geometry::getNormalArray() const
    {
        return normal_array_;
    }
    
    void d3Geometry::setTexCoordArray(d3ArrayDescriptor<float> * tex_coord_array)
    {
        tex_coord_array_ = tex_coord_array;
    }
    
    d3ArrayDescriptor<float> * d3Geometry::getTexCoordArray() const
    {
        return tex_coord_array_;
    }
    
    void d3Geometry::setColorArray(d3ArrayDescriptor<float> * color_array)
    {
        color_array_ = color_array;
    }
    
    d3ArrayDescriptor<float> * d3Geometry::getColorArray() const
    {
        return color_array_;
    }

}