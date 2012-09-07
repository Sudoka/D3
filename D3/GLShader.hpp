//
//  GLShader.hpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GLShader__
#define ____GLShader__

#include "Types.hpp"

namespace d3 {
    class GLShader {
    protected:
        String source_;
        
        ShaderType program_type_;
        
        GLuint shader_id_;
        
        std::unordered_map<String, int> parameters_;
        
        bool is_compiled_;
        
    public:
        GLShader(ShaderType program_type, String path = "");
        
        SETGET(String, source_, Source)
        SETGET(ShaderType, program_type_, ProgramType)
        
        GLuint getShaderID() const { return shader_id_; }
        
        bool isLoaded() { return source_.size() > 1; }
        
        void compile();
        
        bool isCompiled() const { return is_compiled_; };
        
        int getVarIndex(String name);
        
        void printInfoLog();
    };
}

#endif 