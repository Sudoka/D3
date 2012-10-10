//
//  Program.hpp
//  D3
//
//  Created by Srđan Rašić on 10/5/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Program_hpp
#define D3_Program_hpp

namespace d3 {
    class VertexData;
    
    /*! Vertex / Pixel program.
     */
    class Program {
    public:
        //! Default constructor
        Program(String name);
        
        //! Virtual destructor
        virtual ~Program() {}
        
        //! @return program name
        String getName() const;
        
        /* Parameters configurators */        
        virtual void setParamMat4(String name, const Mat4 & mat) {}
        virtual void setParamMat3(String name, const Mat3 & mat) {}
        virtual void setParamVec4(String name, const Vec4 & vec) {}
        virtual void setParamVec3(String name, const Vec3 & vec) {}
        virtual void setParamBool(String name, bool value) {}
        virtual void setParamInt(String name, int value) {}
        virtual void setParamFloat(String name, float value) {}
        virtual void setVertexData(VertexData * vertex_data, unsigned global_offset = 0) {}
        virtual void disableArrayPtr(String name) {}
    
    protected:
        String name;
    };
}

#endif
