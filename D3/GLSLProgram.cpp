//
//  GLSLProgram.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLSLProgram.hpp"

namespace d3 {
    GLSLProgram::GLSLProgram(String name, String path, bool compile_and_link) : Program(name)
    {
        this->program_id = glCreateProgram();
        this->vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        this->fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        
        this->source = FileIO::loadString(path);
        DEBUG_PRINT("Program " << name << " created with id " << this->program_id)
        
        if (compile_and_link)
            compileAndLink();
    }
    
    int GLSLProgram::getLocation(String name)
    {
        GLint location;
        auto iter = parameters.find(name);
        if (iter == parameters.end()) {
            location = glGetUniformLocation(program_id, name.c_str()); // try Uniform
            if (location == -1) location = glGetAttribLocation(program_id, name.c_str()); // try Attribute
            assert(location != -1);
            parameters[name] = location;
        } else {
            location = iter->second;
        }
        return location;
    }
    
    void GLSLProgram::setParamMat4(String name, const Mat4 & mat)
    {
        glUniformMatrix4fv(getLocation(name), 1, 0, mat);
    }
    
    void GLSLProgram::setParamMat3(String name, const Mat3 & mat)
    {
        glUniformMatrix3fv(getLocation(name), 1, 0, mat);
    }
    
    void GLSLProgram::setParamVec4(String name, const Vec4 & vec)
    {
        glUniform4fv(getLocation(name), 1, vec);
    }
    
    void GLSLProgram::setParamVec3(String name, const Vec3 & vec)
    {
        glUniform3fv(getLocation(name), 1, vec);
    }
    
    void GLSLProgram::setParamBool(String name, bool value)
    {
        glUniform1i(getLocation(name), value);
    }
    
    void GLSLProgram::setParamInt(String name, int value)
    {
        glUniform1i(getLocation(name), value);
    }
    
    void GLSLProgram::setParamFloat(String name, float value)
    {
        glUniform1f(getLocation(name), value);
    }
    
    void GLSLProgram::setVertexData(VertexData * vertex_data, unsigned global_offset)
    {
        unsigned char * ptr = vertex_data->getArrayPointer();
        unsigned stride = vertex_data->getStride();
     
        vertex_data->_bind();
        
        for(auto it : vertex_data->getAttribMapRef()) {
            const unsigned & offset = it.second.offset;
            const unsigned & size = it.second.size;
            const unsigned & type = it.second.type;
            const unsigned & normalize = it.second.normalize;
            const String & name = it.first;
            
            glEnableVertexAttribArray(getLocation(name));
            glVertexAttribPointer(getLocation(name), size, type, normalize, stride, ptr + global_offset + offset);
        }
    }
    
    void GLSLProgram::disableArrayPtr(String name)
    {
        glDisableVertexAttribArray(getLocation(name));
    }
    
    void GLSLProgram::enableFloatArrayPtr(String name, int size, GLsizei stride, const float * ptr)
    {
        glEnableVertexAttribArray(getLocation(name));
        glVertexAttribPointer(getLocation(name), size, GL_FLOAT, GL_FALSE, stride, ptr);
    }
    
    void GLSLProgram::compileAndLink() {
        compile();
        link();
    }
    
    void GLSLProgram::compile()
    {
        GLint status;
        const char * sources[3];
        const char * & platform_dependent_macro = sources[0];
        const char * & shader_type_macro = sources[1];
        const char * & source_code = sources[2];
        
        source_code = source.c_str();

        #ifdef _IOS_
        platform_dependent_macro = "#define GLSLES\n";
        #else
        platform_dependent_macro = "#version 120\n#define lowp\n#define mediump\n#define highp\n";
        #endif
        
        shader_type_macro = "#define VERTEX_SHADER\n";
        glShaderSource(vertex_shader_id, 3, sources, NULL);

        shader_type_macro = "#define FRAGMENT_SHADER\n";
        glShaderSource(fragment_shader_id, 3, sources, NULL);

        // Compile vertex shader
        glCompileShader(vertex_shader_id);
        printShaderInfoLog(vertex_shader_id);
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &status);
        assert(status == GL_TRUE);
        
        // Compile fragment shader
        glCompileShader(fragment_shader_id);
        printShaderInfoLog(fragment_shader_id);
        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &status);
        assert(status == GL_TRUE);
        
        // Attach shaders to program
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
    }
    
    void GLSLProgram::link()
    {
        GLint status;
        
        glLinkProgram(program_id);
        
        glValidateProgram(program_id);
        glGetProgramiv(program_id, GL_VALIDATE_STATUS, &status);
        
        if (status != GL_TRUE) {
            printProgramInfoLog();
        } else {
            DEBUG_PRINT("Program " << name << " successfully compiled & linked");
        }
    }
    
    void GLSLProgram::bind()
    {
        glUseProgram(program_id);
    }
    
    void GLSLProgram::printProgramInfoLog()
    {
        int infologLength = 0;
        int charsWritten  = 0;
        char *infoLog;
        
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &infologLength);
        
        if (infologLength > 0)
        {
            infoLog = (char *)malloc(infologLength);
            glGetProgramInfoLog(program_id, infologLength, &charsWritten, infoLog);
            printf("%s\n",infoLog);
            free(infoLog);
        }
    }
    
    void GLSLProgram::printShaderInfoLog(GLuint id)
    {
        int infologLength = 0;
        int charsWritten  = 0;
        char * infoLog;
        
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLength);
        
        if (infologLength > 0)
        {
            infoLog = (char *)malloc(infologLength);
            glGetShaderInfoLog(id, infologLength, &charsWritten, infoLog);
            printf("%s\n",infoLog);
            free(infoLog);
        }
    }
    
    GLuint GLSLProgram::getProgramID() const
    {
        return program_id;
    }
}