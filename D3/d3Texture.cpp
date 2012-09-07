//
//  d3Texture.cpp
//  D3
//
//  Created by Srđan Rašić on 8/30/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Texture.hpp"

namespace d3 {
    
    d3Texture::d3Texture(d3Image *image)
    {
        glEnable(GL_TEXTURE_2D);
        
        glGenTextures(1, &tex_id_);
        glBindTexture(GL_TEXTURE_2D, tex_id_);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, image->getNumberOfChannels(), image->getWidth(), image->getHeight(), 0, image->getPixelFormat(), GL_UNSIGNED_BYTE, image->getData());
        
        glDisable(GL_TEXTURE_2D);
        
    }
    
    void d3Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, tex_id_);
    }
}