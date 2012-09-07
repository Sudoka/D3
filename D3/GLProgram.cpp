//
//  GLProgram.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLProgram.hpp"

namespace d3 {
    GLProgram::GLProgram(shared_ptr<GLShader> vertex_shader,
                             shared_ptr<GLShader> fragment_shader) : vertex_shader_(vertex_shader), fragment_shader_(fragment_shader)
    {
        program_id_ = glCreateProgram();
    }
    
    void GLProgram::setVertexShader(shared_ptr<GLShader> vertex_shader)
    {
        vertex_shader_ = vertex_shader;
        glAttachShader(program_id_, vertex_shader_->getShaderID());
    }
    
    void GLProgram::setFragmentShader(shared_ptr<GLShader> fragment_shader)
    {
        fragment_shader_ = fragment_shader;
        glAttachShader(program_id_, fragment_shader_->getShaderID());
    }
    
    void GLProgram::compile()
    {
        if (vertex_shader_) {
            vertex_shader_->compile();
            assert(vertex_shader_->isCompiled());
        }
        
        if (fragment_shader_) {
            fragment_shader_->compile();
            assert(fragment_shader_->isCompiled());
        }
    }
    
    void GLProgram::link()
    {
        glLinkProgram(program_id_);
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