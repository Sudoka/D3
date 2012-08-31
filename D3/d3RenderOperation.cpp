//
//  d3RenderOperation.cpp
//  D3
//
//  Created by Srđan Rašić on 8/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3RenderOperation.hpp"

namespace d3 {
    d3RenderOperation::d3RenderOperation()
    
    :
    vertex_array_(nullptr),
    normal_array_(nullptr),
    tex_coord_array_(nullptr),
    color_array_(nullptr),
    indices_(nullptr),
    material_(nullptr),
    texture_(nullptr)
    {
    }
    
    void d3RenderOperation::render()
    {
        if (getVertexArray() != nullptr) {
            if (getMaterial() != nullptr) {
                glMateriali(GL_FRONT, GL_SHININESS, getMaterial()->getShininess());
                glMaterialfv(GL_FRONT, GL_AMBIENT, getMaterial()->getAmbientColor());
                glMaterialfv(GL_FRONT, GL_DIFFUSE, getMaterial()->getDiffuseColor());
                glMaterialfv(GL_FRONT, GL_SPECULAR, getMaterial()->getSpecularColor());
                
            }
            
            if (getColorArray()) {
                glEnable(GL_COLOR_MATERIAL);
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(3, GL_FLOAT, getColorArray()->getStride(), getColorArray()->getPointer());    //FIX size
            }
            
            if (getNormalArray()) {
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(GL_FLOAT, getNormalArray()->getStride(), getNormalArray()->getPointer());
            }
            
            if (getTexture() != nullptr && getTexCoordArray()) {
                glEnable(GL_TEXTURE_2D);
                getTexture()->bind();
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(2, GL_FLOAT, getTexCoordArray()->getStride(), getTexCoordArray()->getPointer());
            }
            
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, getVertexArray()->getStride(), getVertexArray()->getPointer());
            
            if (getIndices()) {
                glDrawElements(getGeometryType(),
                               getIndices()->getSize(),
                               GL_UNSIGNED_INT,
                               getIndices()->getPointer());
            } else {
                glDrawArrays(getGeometryType(), 0, getVertexArray()->getSize());
            }
            
            // undo
            if (getColorArray()) {
                glDisableClientState(GL_COLOR_ARRAY);
                glDisable(GL_COLOR_MATERIAL);
            }
            
            if (getNormalArray()) {
                glDisableClientState(GL_NORMAL_ARRAY);
            }
            
            if (getTexture() != nullptr && getTexCoordArray()) {
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glDisable(GL_TEXTURE_2D);
            }
        }
    }
    
    void d3RenderOperation::setGeometryType(unsigned int geometry_type)
    {
        geometry_type_ = geometry_type;
    }
    
    unsigned int d3RenderOperation::getGeometryType()
    {
        return geometry_type_;
    }
    
    void d3RenderOperation::setVertexArray(d3ArrayDescriptor<float> * vertex_array)
    {
        vertex_array_ = vertex_array;
    }
    
    d3ArrayDescriptor<float> * d3RenderOperation::getVertexArray() const
    {
        return vertex_array_;
    }
    
    void d3RenderOperation::setIndices(d3ArrayDescriptor<unsigned int> * indices)
    {
        indices_ = indices;
    }
    
    d3ArrayDescriptor<unsigned int> * d3RenderOperation::getIndices() const
    {
        return indices_;
    }
    
    void d3RenderOperation::setNormalArray(d3ArrayDescriptor<float> * normal_array)
    {
        normal_array_ = normal_array;
    }
    
    d3ArrayDescriptor<float> * d3RenderOperation::getNormalArray() const
    {
        return normal_array_;
    }
    
    void d3RenderOperation::setTexCoordArray(d3ArrayDescriptor<float> * tex_coord_array)
    {
        tex_coord_array_ = tex_coord_array;
    }
    
    d3ArrayDescriptor<float> * d3RenderOperation::getTexCoordArray() const
    {
        return tex_coord_array_;
    }
    
    void d3RenderOperation::setColorArray(d3ArrayDescriptor<float> * color_array)
    {
        color_array_ = color_array;
    }
    
    d3ArrayDescriptor<float> * d3RenderOperation::getColorArray() const
    {
        return color_array_;
    }
    
    void d3RenderOperation::setMaterial(d3Material * material)
    {
        material_ = material;
    }
    
    d3Material * d3RenderOperation::getMaterial() const
    {
        return material_;
    }
    
    void d3RenderOperation::setTexture(d3Texture * texture)
    {
        texture_ = texture;
    }
    
    d3Texture * d3RenderOperation::getTexture() const
    {
        return texture_;
    }
}