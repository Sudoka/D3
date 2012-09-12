//
//  GeometryFactory.cpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GeometryFactory.hpp"

//TODO: Fix colors! Must be 4 floats!

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
    
    static unsigned int indices_[36]  = {
        0, 1, 2,   2, 3, 0,     // front
        4, 5, 6,   6, 7, 4,     // right
        8, 9,10,  10,11, 8,     // top
        12,13,14,  14,15,12,    // left
        16,17,18,  18,19,16,    // bottom
        20,21,22,  22,23,20     // back
    };
    
    
    shared_ptr<Geometry> GeometryFactory::createPlane()
    {
        float width = 2;
        float height = 2;
        
        int subdivs = 30;
        float offsetX = 1.0 / subdivs;
        float offsetZ = 1.0 / subdivs;
        
        Vec3 * vertex_array = new Vec3[subdivs * (4 + subdivs * 2)];
        Vec3 * normal_array = new Vec3[subdivs * (4 + subdivs * 2)];
        Vec3 * texcoord_array = new Vec3[subdivs * (4 + subdivs * 2)];
        
        int idx = 0;
        for (int j = 1; j <= subdivs; j++) {
            vertex_array[idx] = Vec3((offsetX * (j - 1) - 0.5) * width, 0, - 0.5 * height);  // vertex
            normal_array[idx] = Vec3(0, 1, 0);                                               // normal
            texcoord_array[idx++] = Vec3(offsetX * (j - 1), 0.0, 0);                             // texture coordinate
            
            vertex_array[idx] = Vec3((offsetX * j - 0.5) * width, 0, - 0.5 * height);
            normal_array[idx] = Vec3(0, 1, 0);
            texcoord_array[idx++] = Vec3(offsetX * j, 0.0, 0);
            
            for (int i = 1; i <= subdivs; i++) {
                vertex_array[idx] = Vec3((offsetX * (j - 1) - 0.5) * width, 0, (offsetZ * i - 0.5) * height);
                normal_array[idx] = Vec3(0, 1, 0);
                texcoord_array[idx++] = Vec3(offsetX * (j - 1), offsetZ * i, 0);
                
                vertex_array[idx] = Vec3((offsetX * j - 0.5) * width, 0, (offsetZ * i - 0.5) * height);
                normal_array[idx] = Vec3(0, 1, 0);
                texcoord_array[idx++] = Vec3(offsetX * j, offsetZ * i, 0);
            }
            
            vertex_array[idx] = Vec3((offsetX * j - 0.5) * width, 0, (offsetZ * subdivs - 0.5) * height);
            normal_array[idx] = Vec3(0, 1, 0);
            texcoord_array[idx++] = Vec3(offsetX * j - 1.0, offsetX * subdivs, 0);
            
            vertex_array[idx] = Vec3((offsetX * j - 0.5) * width, 0, - 0.5 * height);
            normal_array[idx] = Vec3(0, 1, 0);
            texcoord_array[idx++] = Vec3(offsetX * j, 0.0, 0);
        }
        
        Geometry * g = new Geometry(shared_ptr<float>((float*)vertex_array), idx);

        g->setNormalArray(shared_ptr<float>((float*)normal_array));
        g->setTexCoordArray(shared_ptr<float>((float*)texcoord_array));
        
        g->setGeometryType(GL_TRIANGLE_STRIP);
        g->setVertexPointerStride(sizeof(Vec3));
        g->setNormalPointerStride(sizeof(Vec3));
        g->setTexCoordPointerStride(sizeof(Vec3));
        
        return shared_ptr<Geometry>(g);
    }
    
    shared_ptr<Geometry> GeometryFactory::createBox()
    {
        float * vertices = new float[72]; memcpy(vertices, vertices_, sizeof(float)*72);
        float * normals = new float[72]; memcpy(normals, normals_, sizeof(float)*72);
        unsigned int * indices = new unsigned int[36]; memcpy(indices, indices_, sizeof(unsigned int)*36);
        
        
        Geometry * g = new Geometry(shared_ptr<float>(vertices),
                                    shared_ptr<unsigned int>(indices),
                                    36);
        
        g->setNormalArray(shared_ptr<float>(normals));

        g->setGeometryType(GL_TRIANGLES);
        
        return shared_ptr<Geometry>(g);
    }
    
    shared_ptr<Geometry> GeometryFactory::createCylinder()
    {
        int segments = 15;
        float offset = 1.0 / segments;

        Vec3 * vertex_array = new Vec3[segments*2+2];
        Vec3 * texcoord_array = new Vec3[segments*2+2];
        
        int idx = 0;
        for (int i = 0; i < segments; i++) {
            vertex_array[idx] = Vec3(cosf(offset * i * k2Pi), sinf(offset * i * k2Pi), -0.5f);
            texcoord_array[idx++] = Vec3(offset * i, 0, 0);
            vertex_array[idx] = Vec3(cosf(offset * i * k2Pi), sinf(offset * i * k2Pi), 0.5f);
            texcoord_array[idx++] = Vec3(offset * i, 1, 0);
        }
        
        vertex_array[idx] = Vec3(cosf(0), sinf(0), -0.5f);
        texcoord_array[idx++] = Vec3(1, 0, 0);
        
        vertex_array[idx] = Vec3(cosf(0), sinf(0), 0.5f);
        texcoord_array[idx++] = Vec3(1, 1, 0);
        
        Geometry * g = new Geometry(shared_ptr<float>((float*)vertex_array), idx/2);
        g->setTexCoordArray(shared_ptr<float>((float*)texcoord_array));
        g->setGeometryType(GL_TRIANGLE_STRIP);
        g->setVertexPointerStride(sizeof(Vec3));
        g->setTexCoordPointerStride(sizeof(Vec3));
        
        return shared_ptr<Geometry>(g);
    }
    
    shared_ptr<Geometry> GeometryFactory::createAxes()
    {
        Vec3 * vertex = new Vec3[6];
        Vec4 * color = new Vec4[6];
        
        // X-axis
        color[0] = color[1] = Vec4(1.f, 0.f, 0.f, 1.0f);      // color
        vertex[0] = Vec3(-1000.f, 0.f, 0.f);                     // star point
        vertex[1] = Vec3( 1000.f, 0.f, 0.f);                     // end point
        
        // Y-axis
        color[2] = color[3] = Vec4(0.f, 1.f, 0.f, 1.0f);      // color
        vertex[2] = Vec3(0.f, -1000.f, 0.f);                     // star point
        vertex[3] = Vec3(0.f,  1000.f, 0.f);                     // end point
        
        // Z-axis
        color[4] = color[5] = Vec4(0.f, 0.f, 1.f, 1.0f);      // color
        vertex[4] = Vec3(0.f, 0.f, -1000.f);                     // star point
        vertex[5] = Vec3(0.f, 0.f,  1000.f);                    // end point
        
        Geometry * g = new Geometry(shared_ptr<float>((float*)vertex), 6);
        g->setColorArray(shared_ptr<float>((float*)color));

        g->setGeometryType(GL_LINES);
        g->setVertexPointerStride(sizeof(Vec3));
        g->setColorPointerStride(sizeof(Vec3));
        
        return shared_ptr<Geometry>(g);
    }
    
    shared_ptr<Geometry> GeometryFactory::createArrow(Vec3 v)
    {
        Vec3 * vertex = new Vec3[2];
        Vec4 * color = new Vec4[3];
        
        // X-axis
        color[0] = color[1] = Vec4(1.0f, 1.0f, 1.0f, 1.0f);      // color
        vertex[0] = Vec3(0.f, 0.f, 0.f);                     // star point
        vertex[1] = v.unit() * 10.0;                     // end point
        
        Geometry * g = new Geometry(shared_ptr<float>((float*)vertex), 2);
        g->setColorArray(shared_ptr<float>((float*)color));
        
        g->setGeometryType(GL_LINES);
        g->setVertexPointerStride(sizeof(Vec3));
        g->setColorPointerStride(sizeof(Vec3));
        
        return shared_ptr<Geometry>(g);
    }
}