//
//  GeometryFactory.cpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GeometryFactory.hpp"
#include "Drawable.hpp"

//TODO: Fix colors! Must be 4 floats!

namespace d3 {
    static float CubeVertexData[216] =
    {
        // positionX, positionY, positionZ
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 0.0f,
        
        0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,
        
        -0.5f, 0.5f, -0.5f,     -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,      -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,      -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      0.0f, -1.0f, 0.0f,
        
        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
            
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, -1.0f
    };
    
    std::unordered_map<String, shared_ptr<TexturedMesh>> GeometryFactory::primitive_map;
    
    shared_ptr<TexturedMesh> GeometryFactory::getPrimitive(String name)
    {
        auto it = primitive_map.find(name);
        
        if(it != primitive_map.end())
            return it->second;
        
        // else create
        if (name == "plane")
            primitive_map[name] = createPlane();
        else if (name == "boundingBox")
            primitive_map[name] = createBoundingBox();
        else if (name == "box")
            primitive_map[name] = createBox();
        
        it = primitive_map.find(name);
        assert(it != primitive_map.end());
        return it->second;
    }
    
    shared_ptr<TexturedMesh> GeometryFactory::createPlane()
    {
        float width = 1;
        float height = 1;
        
        int subdivs = 30;
        float offsetX = 1.0 / subdivs;
        float offsetZ = 1.0 / subdivs;
        
        unsigned size = subdivs * (4 + subdivs * 2) * sizeof(Vec3) * 3;
        
        shared_ptr<BufferedVertexData> vbo(new BufferedVertexData(size, sizeof(Vec3) * 3, GL_STATIC_DRAW, GL_ARRAY_BUFFER, nullptr));
        
        vbo->setAttribute("in_position", VertexData::AttribProps(0, 3, GL_FLOAT));
        vbo->setAttribute("in_normal",   VertexData::AttribProps(sizeof(Vec3), 3, GL_FLOAT));
        vbo->setAttribute("in_texcoord", VertexData::AttribProps(sizeof(Vec3) * 2, 2, GL_FLOAT));
        
        Vec3 * vbo_array = (Vec3 *)vbo->mapData();
        
        int idx = 0;
        for (int j = 1; j <= subdivs; j++) {
            vbo_array[idx++] = Vec3((offsetX * (j - 1) - 0.5) * width, 0, - 0.5 * height);  // vertex
            vbo_array[idx++] = Vec3(0, 1, 0);                                               // normal
            vbo_array[idx++] = Vec3(offsetX * (j - 1), 0.0, 0);                             // texture coordinate
            
            vbo_array[idx++] = Vec3((offsetX * j - 0.5) * width, 0, - 0.5 * height);
            vbo_array[idx++] = Vec3(0, 1, 0);
            vbo_array[idx++] = Vec3(offsetX * j, 0.0, 0);
            
            for (int i = 1; i <= subdivs; i++) {
                vbo_array[idx++] = Vec3((offsetX * (j - 1) - 0.5) * width, 0, (offsetZ * i - 0.5) * height);
                vbo_array[idx++] = Vec3(0, 1, 0);
                vbo_array[idx++] = Vec3(offsetX * (j - 1), offsetZ * i, 0);
                
                vbo_array[idx++] = Vec3((offsetX * j - 0.5) * width, 0, (offsetZ * i - 0.5) * height);
                vbo_array[idx++] = Vec3(0, 1, 0);
                vbo_array[idx++] = Vec3(offsetX * j, offsetZ * i, 0);
            }
            
            vbo_array[idx++] = Vec3((offsetX * j - 0.5) * width, 0, (offsetZ * subdivs - 0.5) * height);
            vbo_array[idx++] = Vec3(0, 1, 0);
            vbo_array[idx++] = Vec3(offsetX * j - 1.0, offsetX * subdivs, 0);
            
            vbo_array[idx++] = Vec3((offsetX * j - 0.5) * width, 0, - 0.5 * height);
            vbo_array[idx++] = Vec3(0, 1, 0);
            vbo_array[idx++] = Vec3(offsetX * j, 0.0, 0);
        }
        
        vbo->unmapData();
        
        return shared_ptr<TexturedMesh>(new TexturedMesh(nullptr, vbo, GL_TRIANGLE_STRIP, idx/3));
    }
    
    shared_ptr<TexturedMesh> GeometryFactory::createBoundingBox()
    {
        // vertex array
        shared_ptr<BufferedVertexData> vbo(new BufferedVertexData(sizeof(Vec3) * 8,
                                                                  sizeof(Vec3), GL_STATIC_DRAW, GL_ARRAY_BUFFER, nullptr));
        
        vbo->setAttribute("in_position", VertexData::AttribProps(0, 3, GL_FLOAT));
        
        Vec3 * vertex_array = (Vec3 *)vbo->mapData();
        
        float half_x = 1 / 2.0;
        float half_y = 1 / 2.0;
        float half_z = 1 / 2.0;
        
        vertex_array[0] = Vec3(-half_x, -half_y,  half_z);
        vertex_array[1] = Vec3( half_x, -half_y,  half_z);
        vertex_array[2] = Vec3( half_x, -half_y, -half_z);
        vertex_array[3] = Vec3(-half_x, -half_y, -half_z);
        
        vertex_array[4] = Vec3(-half_x, half_y, half_z);
        vertex_array[5] = Vec3( half_x, half_y, half_z);
        vertex_array[6] = Vec3( half_x, half_y, -half_z);
        vertex_array[7] = Vec3(-half_x, half_y, -half_z);
        
        vbo->unmapData();
        
        // indices
        shared_ptr<BufferedVertexData> ibo(new BufferedVertexData(sizeof(unsigned short) * 16,
                                                                  sizeof(unsigned short), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER, nullptr));
        
        unsigned short * indices = (unsigned short*)ibo->mapData();
        
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
        
        ibo->unmapData();
        
        return shared_ptr<TexturedMesh>(new TexturedMesh(ibo, vbo, GL_LINE_STRIP, 16));
    }

    shared_ptr<TexturedMesh> GeometryFactory::createBox()
    {
        shared_ptr<BufferedVertexData> vbo(new BufferedVertexData(216 * sizeof(float), sizeof(float) * 6, GL_STATIC_DRAW, GL_ARRAY_BUFFER, nullptr));
        
        vbo->setAttribute("in_position", VertexData::AttribProps(0, 3, GL_FLOAT));
        vbo->setAttribute("in_normal", VertexData::AttribProps(sizeof(float) * 3, 3, GL_FLOAT));
        
        float * vertex_array = (float *)vbo->mapData();
        memcpy(vertex_array, CubeVertexData, sizeof(float)*216);
        vbo->unmapData();
        
        return shared_ptr<TexturedMesh>(new TexturedMesh(nullptr, vbo, GL_TRIANGLES, 36));
    }
}