//
//  d3GLProgram.hpp
//  D3
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3GLProgram__
#define __D3__d3GLProgram__

namespace d3 {
    class d3GLProgram {
    protected:
        GLuint program_id_;
        
        shared_ptr<d3GLShader> vertex_shader_;
        shared_ptr<d3GLShader> fragment_shader_;
    public:
        d3GLProgram(shared_ptr<d3GLShader> vertex_shader, shared_ptr<d3GLShader> fragment_shader);
        
        void setVertexShader(shared_ptr<d3GLShader> vertex_shader);
        void setFragmentShader(shared_ptr<d3GLShader> fragment_shader);
        
        void compile();
        
        void link();
        
        void bind();
        
        void printInfoLog();
    };
}

#endif 
