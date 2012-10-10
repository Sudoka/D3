//
//  BufferedVertexData.cpp
//  D3
//
//  Created by Srđan Rašić on 10/10/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "BufferedVertexData.hpp"

namespace d3 {
    BufferedVertexData::BufferedVertexData(unsigned size,       //!> Size of buffer in bytes
                                           unsigned stride,     //!> Stride for interleaved parts
                                           unsigned usage_mode, //!> Usage mode: GL_STATIC_DRAW, GL_STREAM_DRAW...
                                           unsigned target,     //!> Target: GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER
                                           unsigned char * ptr) //!> Pointer to data to copy to buffer or nullptr
    {
        this->size = size;
        this->stride = stride;
        this->array_ptr = NULL;
        this->usage_mode = usage_mode;
        this->target = target;
        
        glGenBuffers(1, &object_id);
        glBindBuffer(target, object_id);
        glBufferData(target, size, ptr, usage_mode);
    }
    
    //! Destructor
    BufferedVertexData::~BufferedVertexData()
    {
        glDeleteBuffers(1, &object_id);
    }
    
    //! VertexData:: Binds array/buffer to device
    void BufferedVertexData::_bind()
    {
        glBindBuffer(target, object_id);
    }
    
    //! VertexData:: Maps array to system memory (unmapData() must follow later!)
    void * BufferedVertexData::mapData(int access_mode)
    {
        glBindBuffer(target, object_id);
        if (access_mode == GL_WRITE_ONLY)
            glBufferData(target, size, NULL, usage_mode); // if only write
        return glMapBuffer(target, access_mode);
    }
    
    //! VertexData:: Unmaps data from system memory
    void BufferedVertexData::unmapData()
    {
        glUnmapBuffer(target);
    }
}