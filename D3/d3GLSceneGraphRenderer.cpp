//
//  d3GLGraphRenderer.cpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3GLSceneGraphRenderer.hpp"
#include "d3Gl.hpp"

namespace d3 {
    void d3GLSceneGraphRenderer::d3GLNodeDrawOperation::beginNode(d3Node *node)
    {
        glPushMatrix();
        glTranslatef(node->getPosition().x, node->getPosition().y, node->getPosition().z);
        d3Vec3 axis = node->getOrientation().getRotationAxis();
        float angle = node->getOrientation().getRotationAngle();
        glRotatef(angle, axis.x, axis.y, axis.z);
        glScalef(node->getScale().x, node->getScale().y, node->getScale().z);
        
        // draw attached object
        if (node->getAttachedObject()) {
        
            d3StateOperation *so;
            d3RenderOperation *ro;
            
            // if state
            if ((so = node->getAttachedObject()->getStateOperation()) != nullptr)
                so->apply();
            
            // if renderable
            if ((ro = node->getAttachedObject()->getRenderOperation()) != nullptr)
                ro->render();
        }
    }
    
    void d3GLSceneGraphRenderer::d3GLNodeDrawOperation::endNode(d3Node *node)
    {
        glPopMatrix();
    }
    
    void d3GLSceneGraphRenderer::render(d3Scene *scene)
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        
        scene->getCamera()->apply();
    
        scene->getRootNode()->traverse(new d3GLNodeDrawOperation());
        
        glFlush();
    }
}