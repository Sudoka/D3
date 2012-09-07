//
//  GLSLRenderer.h
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GLSLRenderer__
#define ____GLSLRenderer__

namespace d3 {
    // Renderer with shader support (TBD)
    class GLSLRenderer : public SceneRenderer {
    protected:
        //! Rendering operation
        class GLNodeDrawOperation : public Node::VisitOperation {
        public:
            virtual void beginNode(Node *node);
            virtual void endNode(Node *node);
        };
        
    public:
        GLSLRenderer(int width, int height);
        
        virtual void render(Scene * scene);
    };
}

#endif