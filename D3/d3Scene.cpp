//
//  d3Root.cpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Scene.hpp"
#include "d3Camera.hpp"
#include "d3gl.hpp"

namespace d3 {
    d3Scene::d3Scene()
    {
        root_node_ = new d3Node("Root");
        root_node_->setNeedsUpdate(false);
        
        camera_ = (d3Camera*)root_node_->createSubnode("MainCamera", new d3Camera)->getAttachedObject();
    }
        
    d3Camera * d3Scene::getCamera() const
    {
        return camera_;
    }
    
    d3Node * d3Scene::getRootNode() const
    {
        return root_node_;
    }
}