//
//  core.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _core_hpp
#define _core_hpp

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include "OpenGLHeaders.hpp"

namespace d3 {
    using std::shared_ptr;
#pragma mark Custom data types
    typedef std::string String;
    typedef unsigned int Size;
    
    enum PixelFormat { D3_RGB = GL_RGB, D3_RGBA = GL_RGBA, D3_GREY = GL_ALPHA };
    
    enum Type { D3_FLOAT, D3_INT, D3_PTR };
    
    enum ShaderType { D3_VERTEX_PROGRAM, D3_FRAGMENT_PROGRAM };
    

#define SETGET(type, member, name) \
inline void set##name(type value) { member = value; } \
inline type get##name() const { return member; }
}

#endif
