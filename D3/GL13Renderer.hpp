//
//  GL13Renderer.h
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GL13Renderer__
#define ____GL13Renderer__

#include <iostream>

namespace d3 {
    //! Fixed-function pipeline renderer (GL v1.3)
    class GL13Renderer : public SceneRenderer {
    protected:
                
    public:
        GL13Renderer(int width, int height);
        
        virtual void render(Scene * scene);
    };
}

#endif
