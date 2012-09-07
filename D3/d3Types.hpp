//
//  d3core.hpp
//  D3
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3core_hpp
#define D3_d3core_hpp

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include "d3Gl.hpp"

namespace d3 {
    using std::shared_ptr;
#pragma mark Custom data types
    typedef std::string d3String;
    typedef unsigned int d3Size;
    
    enum d3PixelFormat { D3_RGB = GL_RGB, D3_RGBA = GL_RGBA, D3_GREY = GL_ALPHA };
    
    enum d3Type { D3_FLOAT, D3_INT, D3_PTR };
    
    enum d3ShaderType { D3_VERTEX_PROGRAM, D3_FRAGMENT_PROGRAM };
    

#define SETGET(type, member, name) \
inline void set##name(type value) { member = value; } \
inline type get##name() const { return member; }
}

#endif
