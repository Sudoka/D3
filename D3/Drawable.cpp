//
//  Drawable.cpp
//  D3
//
//  Created by Srđan Rašić on 10/8/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Drawable.hpp"

namespace d3 {
    //! Default constructor. Registers drawable to Renderer.
    Drawable::Drawable()
    {
        Application::get().getRenderer().registerDrawable(this);
    }
    
    //! Virtual destructor. Unregisters drawable from Renderer.
    Drawable::~Drawable()
    {
        Application::get().getRenderer().unregisterDrawable(this);
    }
    
    //! Draws all occurances
    void Drawable::_drawOccurrences(SceneRenderer & renderer)
    {
        preDraw(renderer);
        for (SceneNode * node : getOriginList())
            drawOccurrence(renderer, * node);
        postDraw(renderer);
    }
}