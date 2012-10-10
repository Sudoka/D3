//
//  Texture.cpp
//  
//
//  Created by Srđan Rašić on 8/30/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Texture.hpp"

namespace d3 {
    //! Creates new texture from image data
    Texture::Texture(Image *image)
    {
        glEnable(GL_TEXTURE_2D);
        
        glGenTextures(1, &tex_id_);
        glBindTexture(GL_TEXTURE_2D, tex_id_);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getData());
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glDisable(GL_TEXTURE_2D);
        
    }
    
    //! Binds texture to device
    void Texture::_bind()
    {
        glBindTexture(GL_TEXTURE_2D, tex_id_);
    }
}