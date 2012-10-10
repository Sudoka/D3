//
//  VertexData.cpp
//  D3
//
//  Created by Srđan Rašić on 10/10/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "VertexData.hpp"

namespace d3 {
    VertexData::AttribProps::AttribProps(unsigned offset, unsigned size, unsigned type, unsigned normalize)
    : offset(offset), size(size), type(type), normalize(normalize) {}
    
    //! Creates new VertexData object
    VertexData::VertexData(unsigned int size,     //!> Size of array in bytes
                           unsigned stride,       //!> Stride of individual atrributes in bytes
                           unsigned char * ptr)   //!> pointer to data, or nullptr to allocate new
    {
        this->size = size;
        this->stride = stride;
        
        if (ptr == nullptr)
            this->array_ptr = new unsigned char[size];
        else
            this->array_ptr = ptr;
    }
    
    //! Creates new VertexData object with one attribute
    VertexData::VertexData(unsigned int size,       //!> Size of array in bytes
                           unsigned stride,         //!> Stride of individual atrributes in bytes
                           String attrib_name,      //!> Name of attribute
                           AttribProps props,       //!> Attribute's properties
                           unsigned char * ptr)     //!> Pointer to data (not copied but deleted in destructor)
    {
        this->size = size;
        this->stride = stride;
        this->array_ptr = ptr;
        setAttribute(attrib_name, props);
    }
    
    //! Destructor
    VertexData::~VertexData()
    {
        if (array_ptr != nullptr)
            delete array_ptr;
    }
    
    //! Resets size of array
    void VertexData::resetSize(unsigned size)
    {
        this->size = size;
    }
    
    //! Adds new attribute description
    void VertexData::setAttribute(String name, AttribProps props)
    {
        attrib_map[name] = props;
    }
    
    //! Binds array/buffer to device
    void VertexData::_bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    //! @return Reference to attributes map
    VertexData::AttribMap & VertexData::getAttribMapRef()
    {
        return attrib_map;
    }
    
    //! @return pointer/offset to/of array
    unsigned char * VertexData::getArrayPointer()
    {
        return array_ptr;
    }
    
    //! @return Stride of attributes on bytes
    unsigned VertexData::getStride() const
    {
        return stride;
    }
    
    //! Maps array to system memory (unmapData() must follow later!)
    void * VertexData::mapData(int access_mode)
    {
        return this->array_ptr;
    }
    
    //! Unmaps data from system memory
    void VertexData::unmapData() {}
}