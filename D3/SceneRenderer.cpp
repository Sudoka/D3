//
//  SceneRenderer.cpp
//  D3
//
//  Created by Srđan Rašić on 10/10/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SceneRenderer.hpp"

namespace d3 {
    //! Creates scene renderer
    SceneRenderer::SceneRenderer(Scene * scene) : scene(scene) {}
    
    //! Virtual destructor
    SceneRenderer::~SceneRenderer() {}
    
    //! Adds drawable to drawable queue
    void SceneRenderer::registerDrawable(Drawable * drawable)
    {
        drawable_list.push_back(drawable);
    }
    
    //! Removes drawable from drawable queue
    void SceneRenderer::unregisterDrawable(Drawable * drawable)
    {
        drawable_list.remove(drawable);
    }
    
    //! Inserts light in light map
    void SceneRenderer::registerLight(Light * light)
    {
        auto it = light_map.find(light);
        
        if (it == light_map.end()) {
            light_map[light] = (int)light_map.size();
        }
    }
    
    //! Removes light from map
    void SceneRenderer::unregisterLight(Light * light)
    {
        light_map.erase(light);
    }
}