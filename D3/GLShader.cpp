//
//  GLShader.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLShader.hpp"

namespace d3 {
    GLShader::GLShader(ShaderType program_type, String path) : program_type_(program_type)
    {
        assert(path.size() > 1);
        String source = FileIO::loadString(path);
        assert(source.size() > 1);
        setSource(source);
        
        if (program_type_ == D3_VERTEX_PROGRAM)
            shader_id_ = glCreateShader(GL_VERTEX_SHADER);
        else if (program_type_ == D3_FRAGMENT_PROGRAM)
            shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
        
        is_compiled_ = false;
    }
    
    void GLShader::compile()
    {
#ifdef _IOS_
        const char *sources[2] = { "precision mediump float;\n", source_.c_str() };
#else
        const char *sources[2] = { "#version 120\n", source_.c_str() };
#endif
        
        glShaderSource(shader_id_, 2, sources, NULL);
        glCompileShader(shader_id_);
        
        GLint status;
        glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &status);
        
        is_compiled_ = (status == GL_TRUE) ? true : false;
    }
    
    void GLShader::printInfoLog()
    {
        int infologLength = 0;
        int charsWritten  = 0;
        char *infoLog;
        
        glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH,&infologLength);
        
        if (infologLength > 0)
        {
            infoLog = (char *)malloc(infologLength);
            glGetShaderInfoLog(shader_id_, infologLength, &charsWritten, infoLog);
            printf("%s\n",infoLog);
            free(infoLog);
        }
    }
}