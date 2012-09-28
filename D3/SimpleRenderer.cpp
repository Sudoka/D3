//
//  SimpleRenderer.cpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SimpleRenderer.hpp"

namespace d3 {
    GLfloat gCubeVertexData[216] =
    {
        // Data layout for each line below is:
        // positionX, positionY, positionZ,     normalX, normalY, normalZ,
        0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
        
        0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,
        
        -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,
        
        0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,
        
        0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f
    };
    
    #define BUFFER_OFFSET(i) ((char *)NULL + (i))
    
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLProgram * program;
    
    SimpleRenderer::SimpleRenderer(ResourceManager * resource_manager, int width, int height) : SceneRenderer(width, height)
    {       
        program = new GLProgram("simple", resource_manager->loadShader("simple.vsh", "simple.vsh", D3_VERTEX_PROGRAM),
                                resource_manager->loadShader("simple.fsh", "simple.fsh", D3_FRAGMENT_PROGRAM), YES);
        
        program->bind();
        
        glEnable(GL_DEPTH_TEST);
               
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gCubeVertexData), gCubeVertexData, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(program->getLocation("position"));
        glVertexAttribPointer(program->getLocation("position"), 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(program->getLocation("normal"));
        glVertexAttribPointer(program->getLocation("normal"), 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
    }
    
    void SimpleRenderer::render(Scene * scene)
    {
        glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // 1
        glViewport(0, 0, getScreenWidth(), getScreenHeight());
        
        Mat4 mvp = Mat4();
        Mat3 normal_transform = Mat4();
//DEBUG_PRINT(mvp)
        glUniformMatrix4fv(program->getLocation("modelViewProjectionMatrix"), 1, D3_TRANSPOSE, mvp);
        glUniformMatrix3fv(program->getLocation("normalMatrix"), 1, D3_TRANSPOSE, normal_transform);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glFlush();
        glFinish();
    }
}