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
    public:
        GLProgram(shared_ptr<GLShader> vertex_shader, shared_ptr<GLShader> fragment_shader);
        
        void setVertexShader(shared_ptr<GLShader> vertex_shader);
        void setFragmentShader(shared_ptr<GLShader> fragment_shader);
        
        void compile();
        
        void link();
        
        void bind();
        
        void printInfoLog();
    };
}

#endif 
