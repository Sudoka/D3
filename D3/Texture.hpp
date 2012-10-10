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
    
    //! Encapsulates GPU texture object
    class Texture {
    public:
        //! Creates new texture from image data
        Texture(Image *image);
        
        //! Binds texture to device
        virtual void _bind();
        
    protected:
        unsigned int tex_id_;
        
    };
}

#endif
