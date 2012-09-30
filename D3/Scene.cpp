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
        root_node = new SceneNode("Root", this);
        root_node->setNeedsUpdate(true);
        
        camera = shared_ptr<Camera>(new Camera());
        root_node->createSubnode("MainCamera", camera)->setPosition(Vec3(5,5,5));
    }
    
    Scene::~Scene()
    {
        delete root_node;
    }
}