//
//  VertexData.hpp
//  D3
//
//  Created by Srđan Rašić on 10/5/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_VertexData_hpp
#define D3_VertexData_hpp

namespace d3 {
    /*! Encapsulates all per-vertex attributes like
     *  position, colour, texcoords, etc.
     */
    class VertexData {
    public:
        typedef std::unordered_map<String, unsigned> AttribMap;
        
    protected:
        AttribMap attrib_map;
        unsigned char * array_ptr;
        unsigned size;
        unsigned stride;
        
    public:
        VertexData(unsigned int size, unsigned stride, unsigned char * ptr = nullptr) {
            this->size = size;
            this->stride = stride;
            
            if (ptr == nullptr)
                this->array_ptr = new unsigned char[size];
            else
                this->array_ptr = ptr;
        }
        
        virtual ~VertexData() {
            if (array_ptr != nullptr)
                delete array_ptr;
        }
        
        virtual void setAttribute(String name, unsigned offset) {
            attrib_map[name] = offset;
        }
        
        virtual void bindToProgram(Program * program) {
            program->setVertexData(this);
        }
        
        virtual void unbindFromProgram(Program * program) {
            for (auto iter : attrib_map) {
                program->disableArrayPtr(iter.first);
            }
        }
        
        virtual AttribMap & getAttribMapRef() {
            return attrib_map;
        }
        
        virtual void * getArrayPointer() {
            return array_ptr;
        }
        
        virtual void * mapData() {
            return this->array_ptr;
        }
    };
}

#endif
