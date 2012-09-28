//
//  Simulator.cpp
//  D3
//
//  Created by Srđan Rašić on 9/16/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SceneSimulator.hpp"

namespace d3 {
    SceneSimulator::CollisionDetectOperation::CollisionDetectOperation(Scene * scene) : scene_(scene)
    {
    }
    
    Scene * SceneSimulator::CollisionDetectOperation::getScene() const
    {
        return scene_;
    }
    
    void SceneSimulator::CollisionDetectOperation::beginNode(d3::Node *node)
    {
        for (Node * node2 : getScene()->getNodeSet()) {
            //Node * node2 = n;
            
            // skip self
            if (node == node2)
                continue;
            
            if (aabbTest(node->getBoundingBox(true), node2->getBoundingBox(true))) {
                if (node->getListener()) {
                    node->getListener()->onCollision(node2);
                }
            }
        }
    }
    
    void SceneSimulator::simulate(Scene * scene, float dt)
    {
        // detect collisions
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new CollisionDetectOperation(scene)));
        
        ParticleSystem::getInstance()->simulate(dt);
    }
}