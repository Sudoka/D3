//
//  d3GLProgram.cpp
//  D3
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3GLProgram.hpp"

namespace d3 {
    d3GLProgram::d3GLProgram(shared_ptr<d3GLShader> vertex_shader,
                             shared_ptr<d3GLShader> fragment_shader) : vertex_shader_(vertex_shader), fragment_shader_(fragment_shader)
    {
        program_id_ = glCreateProgram();
    }
    
    void d3GLProgram::setVertexShader(shared_ptr<d3GLShader> vertex_shader)
    {
        vertex_shader_ = vertex_shader;
        glAttachShader(program_id_, vertex_shader_->getShaderID());
    }
    
    void d3GLProgram::setFragmentShader(shared_ptr<d3GLShader> fragment_shader)
    {
        fragment_shader_ = fragment_shader;
        glAttachShader(program_id_, fragment_shader_->getShaderID());
    }
    
    void d3GLProgram::compile()
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
    
    void d3GLProgram::link()
    {
        glLinkProgram(program_id_);
    }
    
    void d3GLProgram::bind()
    {
        glUseProgram(program_id_);
    }
    
    void d3GLProgram::printInfoLog()
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