//
//  GLSceneRenderer.h
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GLSceneGraphRenderer__
#define ____GLSceneGraphRenderer__

#include <iostream>

namespace d3 {
    class GLSceneRenderer : public SceneRenderer {
    protected:
        //! Rendering operation
        class GLNodeDrawOperation : public Node::VisitOperation {
        public:
            virtual void beginNode(Node *node);
            virtual void endNode(Node *node);
        };
        
        //! Enable lights operation
        class GLTurnLightsOperation : public Node::VisitOperation {
        public:
            virtual void beginNode(Node *node);
        };
                
    public:
        GLSceneRenderer(int width, int height);
        
        virtual void render(Scene * scene);
    };
}

#endif
