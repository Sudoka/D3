//
//  SceneSimulator.h
//  D3
//
//  Created by Srđan Rašić on 9/16/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__Simulator__
#define __D3__Simulator__

namespace d3 {
    class SceneSimulator {
    protected:
        //! Rendering operation
        class CollisionDetectOperation : public SceneNode::VisitOperation {
            Scene * scene_;
            
        public:
            CollisionDetectOperation(Scene * scene);
            
            Scene * getScene() const;
            
            virtual void beginNode(SceneNode *node);
        };
        
    public:        
        void simulate(Scene * scene, float dt);
        void simulate(std::vector<SceneNode *> nodes);
    };
}

#endif
