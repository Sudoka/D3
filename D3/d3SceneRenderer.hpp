//
//  d3SceneRenderer.hpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3SceneRenderer_hpp
#define D3_d3SceneRenderer_hpp

namespace d3 {
    class d3SceneRenderer {
    private:
        int screen_width_;
        int screen_height_;
        
    public:
        d3SceneRenderer(int screen_width, int screen_height) { setScreenSize(screen_width, screen_height); }
        
        //! Renders scene
        virtual void render(d3Scene * scene) =0;
        
        //! Sets screen (window) size
        void setScreenSize(int width, int height) { screen_width_ = width; screen_height_ = height; }
        
        //! @return Screen width
        int getScreenWidth() const { return screen_width_; }
        
        //! @return Screen height
        int getScreenHeight() const { return screen_height_; }
    };
}

#endif
