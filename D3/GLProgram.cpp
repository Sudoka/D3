//
//  GLProgram.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLProgram.hpp"

namespace d3 {
    GLProgram::GLProgram(String name, shared_ptr<GLShader> vertex_shader, shared_ptr<GLShader> fragment_shader, bool compile_and_link)
    {
        this->name = name;
        program_id_ = glCreateProgram();
        DEBUG_PRINT("Program " << name << " created with id " << getProgramID())

        setVertexShader(vertex_shader);
        setFragmentShader(fragment_shader);
        
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
    
    void GLProgram::setParamMat4(String name, const Mat4 & mat)
    {
        glUniformMatrix4fv(getLocation(name), 1, 0, mat);
    }
    
    void GLProgram::setParamMat3(String name, const Mat3 & mat)
    {
        glUniformMatrix3fv(getLocation(name), 1, 0, mat);
    }
    
    void GLProgram::setParamVec4(String name, const Vec4 & vec)
    {
        glUniform4fv(getLocation(name), 1, vec);
    }
    
    void GLProgram::setParamVec3(String name, const Vec3 & vec)
    {
        glUniform3fv(getLocation(name), 1, vec);
    }
    
    void GLProgram::setParamBool(String name, bool value)
    {
        glUniform1i(getLocation(name), value);
    }
    
    void GLProgram::setParamInt(String name, int value)
    {
        glUniform1i(getLocation(name), value);
    }
    
    void GLProgram::setParamFloat(String name, float value)
    {
        glUniform1f(getLocation(name), value);
    }
    
    void  GLProgram::disableArrayPtr(String name)
    {
        glDisableVertexAttribArray(getLocation(name));
    }
    
    void  GLProgram::enableFloatArrayPtr(String name, int size, GLsizei stride, const float * ptr)
    {
        glEnableVertexAttribArray(getLocation(name));
        glVertexAttribPointer(getLocation(name), size, GL_FLOAT, GL_FALSE, stride, ptr);
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
        
        if (status != GL_TRUE) {
            printInfoLog();
        } else {
            DEBUG_PRINT("Program " << name << " successfully compiled & linked");
        }
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
    
    GLuint GLProgram::getProgramID() const
    {
        return program_id_;
    }
    
    void GLProgram::printParams() {
        for(auto it : parameters_) {
            std::cout << it.first << ": " << it.second << std::endl;
        }
    }
    
    String GLProgram::getName() const
    {
        return name;
    }
}