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
    protected:
        
    public:
        
        /* Parameters configurators */
        virtual void setParamMat4(String name, const Mat4 & mat) =0;
        virtual void setParamMat3(String name, const Mat3 & mat) =0;
        virtual void setParamVec4(String name, const Vec4 & vec) =0;
        virtual void setParamVec3(String name, const Vec3 & vec) =0;
        virtual void setParamBool(String name, bool value) =0;
        virtual void setParamInt(String name, int value) =0;
        virtual void setParamFloat(String name, float value) =0;
        
        virtual void setVertexData(VertexData * vertex_data) =0;
        
        virtual void disableArrayPtr(String name) =0;
        virtual void enableFloatArrayPtr(String, int size, GLsizei stride, const float * ptr) =0;
    };
}

#endif
