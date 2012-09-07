//
//  Texture.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Texture_hpp
#define _Texture_hpp

namespace d3 {
    class Image;
    
#pragma mark Interface
    class Texture {
    protected:
        unsigned int tex_id_;
        
        float rotation = 60;
        
    public:
        Texture(Image *image);
        
        virtual void bind();
    };
}

#endif
