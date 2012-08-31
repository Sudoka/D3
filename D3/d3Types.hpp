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
#include "d3Gl.hpp"

namespace d3 {
#pragma mark Custom data types
    typedef std::string d3String;
    typedef unsigned int d3Size;
    
    enum d3PixelFormat { D3_RGB = GL_RGB, D3_RGBA = GL_RGBA, D3_GREY = GL_ALPHA };
}

#endif
