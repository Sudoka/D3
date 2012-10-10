//
//  Simulator.cpp
//  D3
//
//  Created by Srđan Rašić on 9/16/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SceneSimulator.hpp"

namespace d3 {
    /* Updatable */
    SceneSimulator::Updatable::Updatable()
    {
        Application::get().getSimulator().registerUpdatable(this);
    }
    
    SceneSimulator::Updatable::~Updatable()
    {
        Application::get().getSimulator().unregisterUpdatable(this);
    }
    
    /* Scene Simulator */
    SceneSimulator::SceneSimulator(Scene * scene) : scene(scene)
    {
    }
    
    //! Registers updatable
    void SceneSimulator::registerUpdatable(Updatable * updatable)
    {
        updatable_list.push_back(updatable);
    }
    
    //! Unregisters updatable
    void SceneSimulator::unregisterUpdatable(Updatable * updatable)
    {
        updatable_list.remove(updatable);
    }
    
    //! Simulate scene animables nad updatables
    void SceneSimulator::simulate(float dt)
    {
        for(Updatable * u : updatable_list)
            u->update(dt);
    }
    
    //! Check for collisions between node and part of scene graph
    void SceneSimulator::checkForCollisions(SceneNode * root_node, SceneNode * node)
    {
        NodeList list;
        root_node->traverse(shared_ptr<SceneNode::VisitOperation>(new NodeGatherOperation(list)));
        
        for (SceneNode * node2 : list) {            
            if (aabbTest(node->getBoundingBox(true), node2->getBoundingBox(true))) {
                if (node->getListener()) {
                    node->getListener()->onCollision(node2);
                }
            }
        }
    }
    
    /* Node Gather operation */
    SceneSimulator::NodeGatherOperation::NodeGatherOperation(NodeList & list) : list(list) {}
    
    void SceneSimulator::NodeGatherOperation::beginNode(SceneNode * node)
    {
        list.push_back(node);
    }
    

}