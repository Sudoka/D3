//
//  d3GLSLRenderer.h
//  D3
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3GLSLRenderer__
#define __D3__d3GLSLRenderer__

namespace d3 {
    class d3GLSLRenderer : public d3SceneRenderer {
    protected:
        //! Rendering operation
        class d3GLNodeDrawOperation : public d3Node::VisitOperation {
        public:
            virtual void beginNode(d3Node *node);
            virtual void endNode(d3Node *node);
        };
        
    public:
        d3GLSLRenderer(int width, int height);
        
        virtual void render(d3Scene * scene);
    };
}

#endif