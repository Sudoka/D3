//
//  d3FileIO.cpp
//  D3
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3FileIO.hpp"
#include <fstream>

namespace d3 {
    d3String d3FileIO::loadString(d3String path)
    {
        using namespace std;
        d3String source;
        
        ifstream file(path.c_str(), ios::in | ios::binary | ios::ate);
        ifstream::pos_type size;
        char * memblock;
        
        if (file.is_open()) {
            size = file.tellg();
            memblock = new char [(long)size + 1];
            file.seekg (0, ios::beg);
            file.read (memblock, size);
            file.close();
            memblock[size] = '\0';
            source = d3String(memblock);
            delete [] memblock;
        }
        
        return source;
    }
}