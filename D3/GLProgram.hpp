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
        GLuint program_id_;
        
        shared_ptr<GLShader> vertex_shader_;
        shared_ptr<GLShader> fragment_shader_;
        
        std::unordered_map<String, int> parameters_;
    public:
        GLProgram(shared_ptr<GLShader> vertex_shader, shared_ptr<GLShader> fragment_shader);
        
        GLProgram(String vertex_shader_path, String fragment_shader_path, bool compile_and_link = NO);
        
        void setVertexShader(shared_ptr<GLShader> vertex_shader);
        
        shared_ptr<GLShader> & getVertexShaderRef();
        
        void setFragmentShader(shared_ptr<GLShader> fragment_shader);
        
        shared_ptr<GLShader> & getFragmentShaderRef();
        
        int getLocation(String name);
        
        //! Compile, link and validate
        void compileAndLink();
        
        void compile();
        
        void link();
        
        void validate();
        
        void bind();
        
        void printInfoLog();
    };
}

#endif 
