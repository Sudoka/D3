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
        struct AttribProps {
            unsigned offset;    //!> Starting offset in array in bytes
            unsigned size;      //!> Number of components [1..4]
            unsigned type;      //!> Type: GL_FLOAT, GL_UNSIGNED_INT, etc...
            unsigned normalize; //!> Normalize?
            
            AttribProps() {}
            AttribProps(unsigned offset, unsigned size, unsigned type, unsigned normalize = GL_FALSE);
        };
        
        typedef std::unordered_map<String, AttribProps> AttribMap;
        
    public:
        //! Creates new VertexData object
        VertexData(unsigned int size,               //!> Size of array in bytes
                   unsigned stride,                 //!> Stride of individual atrributes in bytes
                   unsigned char * ptr = nullptr);  //!> pointer to data, or nullptr to allocate new
        
        //! Creates new VertexData object with one attribute
        VertexData(unsigned int size,       //!> Size of array in bytes
                   unsigned stride,         //!> Stride of individual atrributes in bytes
                   String attrib_name,      //!> Name of attribute
                   AttribProps props,       //!> Attribute's properties
                   unsigned char * ptr);    //!> Pointer to data (not copied but deleted in destructor)
        
        //! Destructor
        virtual ~VertexData();
        
        //! Resets size of array
        virtual void resetSize(unsigned size);
        
        //! Adds new attribute description
        virtual void setAttribute(String name, AttribProps props);
        
        //! Binds array/buffer to device
        virtual void _bind();
        
        //! @return Reference to attributes map
        virtual AttribMap & getAttribMapRef();
        
        //! @return pointer/offset to/of array
        virtual unsigned char * getArrayPointer();
        
        //! @return Stride of attributes on bytes
        virtual unsigned getStride() const;
        
        //! Maps array to system memory (unmapData() must follow later!)
        virtual void * mapData(int access_mode = GL_WRITE_ONLY);    //!> GL_WRITE_ONLY, GL_READ_ONLY...
        
        //! Unmaps data from system memory
        virtual void unmapData();
        
    protected:
        VertexData() {}
        
    protected:
        AttribMap attrib_map;
        unsigned char * array_ptr;
        unsigned size;
        unsigned stride;
    };
}

#endif
