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
        root_node = new SceneNode("Root", * this);
        root_node->setNeedsUpdate(true);
        
        SceneNode & cam_node = (SceneNode&)root_node->createSubnode("MainCamera").setPosition(Vec3(5,5,5));
        camera = shared_ptr<Camera>(new Camera(cam_node));
    }
    
    Scene::~Scene() 
    {
        delete root_node;
    }
    
    //! @return Scene camera
    Camera & Scene::getCamera() const
    {
        return * camera;
    }
    
    //! @return Root node
    SceneNode & Scene::getRoot() const
    {
        return * root_node;
    };
    
    //! @return Reference to map with all nodes in scene
    const Scene::NodeMap & Scene::getNodeMap() const
    {
        return node_map;
    }
    
    //! @return Node named name
    SceneNode & Scene::getNode(String name)
    {
        auto it = node_map.find(name);
        assert(it != node_map.end());
        return * it->second;
    }
    
    //! Registers new listener
    void Scene::registerListener(Listener * listener)
    {
        listeners.push_back(listener);
    }
    
    //! Removes listener from list
    void Scene::unregisterListener(Listener * listener)
    {
        listeners.remove(listener);
    }
    
    //! Called internaly after new node is created
    void Scene::_nodeCreated(SceneNode * node)
    {
        assert(node_map.find(node->getName()) == node_map.end());
        node_map[node->getName()] = node;
        
        for (Listener * l : listeners)
            l->onNodeInsert(node);
    }
    
    //! Called internaly upon node deletion
    void Scene::_nodeWillBeDeleted(SceneNode * node)
    {
        for (Listener * l : listeners)
            l->onNodeRemove(node);
    
        node_map.erase(node->getName());
    }
}