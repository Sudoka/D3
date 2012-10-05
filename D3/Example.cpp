//
//  Example.cpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#define GLUT        // Use GLUT as Window manager
#define D3_COMPILE  // Compile engine (include all cpps to avoid libraries for now)
#include "d3.hpp"

int main(int argc, char** argv)
{
    d3::Vec4 v(1,2,3,4);
    
    DEBUG_PRINT(d3::to8BitVec4(v))
    
    (new d3::Example("/Users/srdan/Development/D3/Resources"))->run();
    return EXIT_SUCCESS;
}