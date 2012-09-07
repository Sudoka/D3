//
//  d3GLShader.hpp
//  D3
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3GLShader__
#define __D3__d3GLShader__

#include "d3Types.hpp"

namespace d3 {
    class d3GLShader {
    protected:
        d3String source_;
        
        d3ShaderType program_type_;
        
        GLuint shader_id_;
        
        std::unordered_map<d3String, int> parameters_;
        
        bool is_compiled_;
        
    public:
        d3GLShader(d3ShaderType program_type, d3String path = "");
        
        SETGET(d3String, source_, Source)
        SETGET(d3ShaderType, program_type_, ProgramType)
        
        GLuint getShaderID() const { return shader_id_; }
        
        bool isLoaded() { return source_.size() > 1; }
        
        void compile();
        
        bool isCompiled() const { return is_compiled_; };
        
        int getVarIndex(d3String name);
        
        void printInfoLog();
    };
}

#endif 