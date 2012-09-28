//
//  GLProgram.hpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GLProgram__
#define ____GLProgram__

namespace d3 {
    class GLProgram {
    protected:
        String name;
        GLuint program_id_;
        
        shared_ptr<GLShader> vertex_shader_;
        shared_ptr<GLShader> fragment_shader_;
        
        std::unordered_map<String, int> parameters_;
    public:
        GLProgram(String name, shared_ptr<GLShader> vertex_shader, shared_ptr<GLShader> fragment_shader, bool compile_and_link = NO);
                
        void setVertexShader(shared_ptr<GLShader> vertex_shader);
        
        shared_ptr<GLShader> & getVertexShaderRef();
        
        void setFragmentShader(shared_ptr<GLShader> fragment_shader);
        
        shared_ptr<GLShader> & getFragmentShaderRef();
        
        int getLocation(String name);
        
        void setParamMat4(String name, const Mat4 & mat);
        void setParamMat3(String name, const Mat3 & mat);
        void setParamVec4(String name, const Vec4 & vec);
        void setParamVec3(String name, const Vec3 & vec);
        void setParamBool(String name, bool value);
        void setParamInt(String name, int value);
        void setParamFloat(String name, float value);
        void disableArrayPtr(String name);
        void enableFloatArrayPtr(String, int size, GLsizei stride, const float * ptr);
        
        //! Compile, link and validate
        void compileAndLink();
        
        void compile();
        
        void link();
        
        void validate();
        
        void bind();
        
        void printInfoLog();
        
        GLuint getProgramID() const;
        
        void printParams();
        
        String getName() const;
    };
}

#endif 
