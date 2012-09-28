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
    static float CubeVertexData[108] =
    {
        // positionX, positionY, positionZ
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f
    };
    
    static float CubeNormalData[108] =
    {
        //normalX, normalY, normalZ,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f
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
    
    shared_ptr<Geometry> GeometryFactory::createBoundingBox(Vec3 volume)
    {
        // vertex array
        Vec3 * vertex_array = new Vec3[8];
        
        float half_x = volume.x / 2.0;
        float half_y = volume.y / 2.0;
        float half_z = volume.z / 2.0;
        
        vertex_array[0] = Vec3(-half_x, -half_y,  half_z);
        vertex_array[1] = Vec3( half_x, -half_y,  half_z);
        vertex_array[2] = Vec3( half_x, -half_y, -half_z);
        vertex_array[3] = Vec3(-half_x, -half_y, -half_z);
        
        vertex_array[4] = Vec3(-half_x, half_y, half_z);
        vertex_array[5] = Vec3( half_x, half_y, half_z);
        vertex_array[6] = Vec3( half_x, half_y, -half_z);
        vertex_array[7] = Vec3(-half_x, half_y, -half_z);
        
        // indices
        unsigned int * indices = new unsigned int[16];
        indices[0] = 4;
        indices[1] = 0;
        indices[2] = 1;
        indices[3] = 5;
        indices[4] = 6;
        indices[5] = 2;
        indices[6] = 3;
        indices[7] = 7;
        indices[8] = 4;
        indices[9] = 5;
        indices[10] = 1;
        indices[11] = 2;
        indices[12] = 6;
        indices[13] = 7;
        indices[14] = 3;
        indices[15] = 0;
        
        Geometry * g = new Geometry(shared_ptr<float>((float*)vertex_array),
                                    shared_ptr<unsigned int>(indices),
                                    16);
        g->setVertexPointerStride(sizeof(Vec3));
        g->setGeometryType(GL_LINE_STRIP);
        
        return shared_ptr<Geometry>(g);
    }
    
    shared_ptr<Geometry> GeometryFactory::createBox()
    {
        float * vertices = new float[108]; memcpy(vertices, CubeVertexData, sizeof(float)*108);
        float * normals = new float[108]; memcpy(normals, CubeNormalData, sizeof(float)*108);
        
        Geometry * g = new Geometry(shared_ptr<float>(vertices), 36);
        
        g->setNormalArray(shared_ptr<float>(normals));
        g->setVertexPointerStride(0);
        g->setNormalPointerStride(0);
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