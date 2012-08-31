//
//  d3Box.cpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Box.hpp"
#include "d3Gl.hpp"

namespace d3 {
    static float vertices_[72] = {
        1, 1, 1,    -1, 1, 1,   -1,-1, 1,   1,-1, 1,    // v0,v1,v2,v3 (front)
        1, 1, 1,    1,-1, 1,    1,-1,-1,    1, 1,-1,    // v0,v3,v4,v5 (right)
        1, 1, 1,    1, 1,-1,    -1, 1,-1,   -1, 1, 1,   // v0,v5,v6,v1 (top)
        -1, 1, 1,   -1, 1,-1,   -1,-1,-1,   -1,-1, 1,   // v1,v6,v7,v2 (left)
        -1,-1,-1,   1,-1,-1,    1,-1, 1,    -1,-1, 1,   // v7,v4,v3,v2 (bottom)
        1,-1,-1,    -1,-1,-1,   -1, 1,-1,   1, 1,-1     // v4,v7,v6,v5 (back)
    };
    
    static float normals_[72] = {
        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
        -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  // v1,v6,v7,v2 (left)
        0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
        0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1    // v4,v7,v6,v5 (back)
    };
    
    static float colors_[72] = {
        1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
        1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
        1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
        1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
        0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1    // v4,v7,v6,v5 (back)
    };
    
    static unsigned int indices_[36]  = {
        0, 1, 2,   2, 3, 0,     // front
        4, 5, 6,   6, 7, 4,     // right
        8, 9,10,  10,11, 8,     // top
        12,13,14,  14,15,12,    // left
        16,17,18,  18,19,16,    // bottom
        20,21,22,  22,23,20     // back
    };
    
    d3Box::d3Box()
    {        
        render_operation_ = new d3RenderOperation();
        render_operation_->setVertexArray(new d3ArrayDescriptor<float>(vertices_, 72, 0));
        render_operation_->setNormalArray(new d3ArrayDescriptor<float>(normals_, 72, 0));
        render_operation_->setColorArray(new d3ArrayDescriptor<float>(colors_, 72, 0));
        render_operation_->setIndices(new d3ArrayDescriptor<unsigned int>(indices_, 36, 0));
        render_operation_->setGeometryType(GL_TRIANGLES);
    }
    
    bool d3Box::isVisible() const
    {
        return true;
    }
}