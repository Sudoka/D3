//
//  BufferedVertexData.hpp
//  D3
//
//  Created by Srđan Rašić on 10/5/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_BufferedVertexData_hpp
#define D3_BufferedVertexData_hpp

namespace d3 {
    /*! VertexData implementation using Vertex Buffer Object.
     *  Memory is managed by GPU.
     */
    class BufferedVertexData : public VertexData {        
    public:
        //! Creates new BufferedVertexData object
        BufferedVertexData(unsigned size,       //!> Size of buffer in bytes
                           unsigned stride,     //!> Stride for interleaved parts
                           unsigned usage_mode, //!> Usage mode: GL_STATIC_DRAW, GL_STREAM_DRAW...
                           unsigned target,     //!> Target: GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER
                           unsigned char * ptr);//!> Pointer to data to copy to buffer or nullptr
        
        //! Destructor
        virtual ~BufferedVertexData();
        
        //! VertexData:: Binds array/buffer to device
        virtual void _bind();
        
        //! VertexData:: Maps array to system memory (unmapData() must follow later!)
        virtual void * mapData(int access_mode = GL_WRITE_ONLY);
        
        //! VertexData:: Unmaps data from system memory
        virtual void unmapData();
        
    protected:
        unsigned object_id;
        unsigned usage_mode;
        unsigned target;
    };
}

#endif
