//
//  Root.cpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Scene.hpp"
#include "Camera.hpp"
#include "OpenGLHeaders.hpp"

namespace d3 {
    Scene::Scene()
    {
        root_node_ = new Node("Root", this);
        root_node_->setNeedsUpdate(true);
        
        camera_ = (Camera*)root_node_->createSubnode("MainCamera", new Camera())->getAttachedObject();
    }
    
    Scene::~Scene()
    {
        delete root_node_;
    }
        
    Camera * Scene::getCamera() const
    {
        return camera_;
    }
    
    Node * Scene::getRoot() const
    {
        return root_node_;
    }
    
    Scene::NodeSet & Scene::getNodeSet()
    {
        return scene_nodes_;
    }
    
    void Scene::registerNode(Node * node)
    {
        scene_nodes_.insert(node);
    }
    
    void Scene::unregisterNode(Node * node)
    {
        scene_nodes_.erase(node);
    }
}