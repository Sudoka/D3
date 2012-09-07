//
//  GLSLRenderer.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLSLRenderer.hpp"
#include "OpenGLHeaders.hpp"

namespace d3 {
        
    void GLSLRenderer::GLNodeDrawOperation::beginNode(Node *node)
    {
    }
    
    void GLSLRenderer::GLNodeDrawOperation::endNode(Node *node)
    {
    }
    
    GLSLRenderer::GLSLRenderer(int width, int height) : SceneRenderer(width, height)
    {        
    }
    
    void GLSLRenderer::render(Scene *scene)
    {
    }
}