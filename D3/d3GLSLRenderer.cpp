//
//  d3GLSLRenderer.cpp
//  D3
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3GLSLRenderer.hpp"
#include "d3Gl.hpp"

namespace d3 {
        
    void d3GLSLRenderer::d3GLNodeDrawOperation::beginNode(d3Node *node)
    {
    }
    
    void d3GLSLRenderer::d3GLNodeDrawOperation::endNode(d3Node *node)
    {
    }
    
    d3GLSLRenderer::d3GLSLRenderer(int width, int height) : d3SceneRenderer(width, height)
    {        
    }
    
    void d3GLSLRenderer::render(d3Scene *scene)
    {
    }
}