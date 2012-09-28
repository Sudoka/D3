//
//  SimpleRenderer.h
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__SimpleRenderer__
#define __D3__SimpleRenderer__

namespace d3 {
    class ResourceManager;
    
    class SimpleRenderer : public SceneRenderer {
    public:
        SimpleRenderer(ResourceManager * resource_manager, int width, int height);
        
        virtual void render(Scene * scene);
    };
}

#endif