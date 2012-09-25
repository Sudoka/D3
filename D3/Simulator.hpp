//
//  Simulator.h
//  D3
//
//  Created by Srđan Rašić on 9/16/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__Simulator__
#define __D3__Simulator__

namespace d3 {
    class Simulator {
    protected:
        //! Rendering operation
        class CollisionDetectOperation : public Node::VisitOperation {
            Scene * scene_;
            
        public:
            CollisionDetectOperation(Scene * scene);
            
            Scene * getScene() const;
            
            virtual void beginNode(Node *node);
        };
        
    public:        
        void simulate(Scene * scene);
        void simulate(std::vector<Node *> nodes);
    };
}

#endif
