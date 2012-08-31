//
//  d3Texture.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Texture_hpp
#define D3_d3Texture_hpp

namespace d3 {
    class d3Image;
    
#pragma mark Interface
    class d3Texture {
    protected:
        unsigned int tex_id_;
        
    public:
        d3Texture(d3Image *image);
        
        virtual void bind();
    };
}

#endif
