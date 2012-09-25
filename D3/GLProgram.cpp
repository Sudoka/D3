//
//  GLProgram.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLProgram.hpp"

namespace d3 {
    GLProgram::GLProgram(shared_ptr<GLShader> vertex_shader, shared_ptr<GLShader> fragment_shader)
    {
        program_id_ = glCreateProgram();
        
        setVertexShader(vertex_shader);
        setFragmentShader(fragment_shader);
    }
    
    GLProgram::GLProgram(String vertex_shader_path, String fragment_shader_path, bool compile_and_link)
    {
        program_id_ = glCreateProgram();
        setVertexShader(shared_ptr<GLShader>(new GLShader(D3_VERTEX_PROGRAM, vertex_shader_path)));
        setFragmentShader(shared_ptr<GLShader>(new GLShader(D3_FRAGMENT_PROGRAM, fragment_shader_path)));
        
        if (compile_and_link)
            compileAndLink();
    }
    
    void GLProgram::setVertexShader(shared_ptr<GLShader> vertex_shader)
    {
        vertex_shader_ = vertex_shader;
        glAttachShader(program_id_, vertex_shader_->getShaderID());
    }
    
    shared_ptr<GLShader> & GLProgram::getVertexShaderRef()
    {
        return vertex_shader_;
    }
    
    void GLProgram::setFragmentShader(shared_ptr<GLShader> fragment_shader)
    {
        fragment_shader_ = fragment_shader;
        glAttachShader(program_id_, fragment_shader_->getShaderID());
    }
    
    shared_ptr<GLShader> & GLProgram::getFragmentShaderRef()
    {
        return fragment_shader_;
    }
    
    int GLProgram::getLocation(String name)
    {
        GLint location;
        auto iter = parameters_.find(name);
        if (iter == parameters_.end()) {
            location = glGetUniformLocation(program_id_, name.c_str()); // try Uniform
            if (location == -1) location = glGetAttribLocation(program_id_, name.c_str()); // try Attribute
            assert(location != -1);
            parameters_[name] = location;
        } else {
            location = iter->second;
        }
        return location;
    }
    
    void GLProgram::compileAndLink() {
        compile();
        link();
        validate();
    }
    
    void GLProgram::compile()
    {
        if (vertex_shader_) {
            vertex_shader_->compile();
            vertex_shader_->printInfoLog();
            assert(vertex_shader_->isCompiled());
        }
        
        if (fragment_shader_) {
            fragment_shader_->compile();
            fragment_shader_->printInfoLog();
            assert(fragment_shader_->isCompiled());
        }
        
        printInfoLog();
    }
    
    void GLProgram::link()
    {
        glLinkProgram(program_id_);
    }
    
    void GLProgram::validate()
    {
        GLint status;
        glValidateProgram(program_id_);
        glGetProgramiv(program_id_, GL_VALIDATE_STATUS, &status);
        
        if (status != GL_TRUE)
            printInfoLog();
    }
    
    void GLProgram::bind()
    {
        glUseProgram(program_id_);
    }
    
    void GLProgram::printInfoLog()
    {
        int infologLength = 0;
        int charsWritten  = 0;
        char *infoLog;
        
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH,&infologLength);
        
        if (infologLength > 0)
        {
            infoLog = (char *)malloc(infologLength);
            glGetProgramInfoLog(program_id_, infologLength, &charsWritten, infoLog);
            printf("%s\n",infoLog);
            free(infoLog);
        }
    }
}