//
//  d3GLSceneRenderer.h
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3GLSceneGraphRenderer__
#define __D3__d3GLSceneGraphRenderer__

#include <iostream>

namespace d3 {
    class d3GLSceneRenderer : public d3SceneRenderer {
    protected:
        //! Rendering operation
        class d3GLNodeDrawOperation : public d3Node::VisitOperation {
        public:
            virtual void beginNode(d3Node *node);
            virtual void endNode(d3Node *node);
        };
        
        //! Enable lights operation
        class d3GLTurnLightsOperation : public d3Node::VisitOperation {
        public:
            virtual void beginNode(d3Node *node);
        };
                
    public:
        d3GLSceneRenderer(int width, int height);
        
        virtual void render(d3Scene * scene);
    };
}

#endif
