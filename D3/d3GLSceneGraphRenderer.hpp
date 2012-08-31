//
//  d3GLSceneGraphRenderer.h
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3GLSceneGraphRenderer__
#define __D3__d3GLSceneGraphRenderer__

namespace d3 {
    class d3GLSceneGraphRenderer {
    protected:
        class d3GLNodeDrawOperation : public d3Node::VisitOperation {
        public:
            virtual void beginNode(d3Node *node);
            virtual void endNode(d3Node *node);
        };
        
    public:
        void render(d3Scene *scene);
    };
}

#endif
