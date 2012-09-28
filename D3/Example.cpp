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
    (new d3::Example("Resources"))->run();
    return EXIT_SUCCESS;
}