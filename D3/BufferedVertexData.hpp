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
    /*! VertexData implementation using Vertex Buffer Object
     */
    class BufferedVertexData : public VertexData {
    protected:
        unsigned object_id;
        
    public:
        BufferedVertexData(unsigned size, unsigned stride, int type, unsigned char * ptr) : VertexData(size, stride) {
            glGenBuffers(1, &object_id);
            glBindBuffer(GL_ARRAY_BUFFER, object_id);
            glBufferData(GL_ARRAY_BUFFER, size, ptr, type);
        }
        
        virtual ~BufferedVertexData() {
            glDeleteBuffers(1, &object_id);
        }
        
        virtual void bindToProgram(Program * program) {
            glBindBuffer(GL_ARRAY_BUFFER, object_id);
            program->setVertexData(this);
        }
        
        virtual void * mapData(int access_mode = GL_WRITE_ONLY) {
            // unmap 0?
            glBindBuffer(GL_ARRAY_BUFFER, object_id);
            if (access_mode == GL_WRITE_ONLY)
                glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW); // if only write
            return glMapBuffer(GL_ARRAY_BUFFER, access_mode);
        }
    };
}

#endif
