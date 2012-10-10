//
//  GLSLProgram.hpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GLSLProgram__
#define ____GLSLProgram__

namespace d3 {
    class GLSLProgram : public Program {
    public:
        GLSLProgram(String name, String path, bool compile_and_link = NO);
        
        virtual void setParamMat4(String name, const Mat4 & mat);
        virtual void setParamMat3(String name, const Mat3 & mat);
        virtual void setParamVec4(String name, const Vec4 & vec);
        virtual void setParamVec3(String name, const Vec3 & vec);
        virtual void setParamBool(String name, bool value);
        virtual void setParamInt(String name, int value);
        virtual void setParamFloat(String name, float value);
        virtual void setVertexData(VertexData * vertex_data, unsigned global_offset = 0);
        virtual void disableArrayPtr(String name);
        virtual void enableFloatArrayPtr(String, int size, GLsizei stride, const float * ptr);
        
        //! Compile, link and validate
        void compileAndLink();
        
        void compile();
        void link();
        void bind();
        
    protected:
        void printShaderInfoLog(GLuint id);
        void printProgramInfoLog();
        GLuint getProgramID() const;
        
        int getLocation(String name);
        
    protected:
        GLuint program_id;
        GLuint vertex_shader_id;
        GLuint fragment_shader_id;
        
        String source;
        
        std::unordered_map<String, int> parameters;
    };
}

#endif 
