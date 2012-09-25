//
//  core.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _core_hpp
#define _core_hpp

#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "OpenGLHeaders.hpp"

namespace d3 {
    using std::shared_ptr;
    
    typedef std::string String;
    typedef unsigned int Size;
    
    enum PixelFormat { D3_RGB = GL_RGB, D3_RGBA = GL_RGBA, D3_GREY = GL_ALPHA };
    
    enum Type { D3_FLOAT, D3_INT, D3_PTR };
    
    enum ShaderType { D3_VERTEX_PROGRAM, D3_FRAGMENT_PROGRAM };
    
    inline String toString(int num) {
        std::stringstream ss;
        ss << num;
        return ss.str();
    }
    
    inline String operator+(const String & left, int & right) {
        return left + toString(right);
    }

#define YES true
#define NO false
    
#define SETGET(type, member, name) \
inline void set##name(type value) { member = value; } \
inline type get##name() const { return member; }
}

#endif
