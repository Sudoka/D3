//
//  Material.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _material_hpp
#define _material_hpp

namespace d3 {
    class Vec4;
    
#pragma mark Interface
    class Material {
    protected:
        Vec4 ambient_color_;
        Vec4 diffuse_color_;
        Vec4 specular_color_;
        int shininess_;             // 0..128
        
    public:
        Material();
        
        void setAmbientAndDiffuseColor(Vec4 color);
        
        SETGET(Vec4, ambient_color_, AmbientColor)
        SETGET(Vec4, diffuse_color_, DiffuseColor)
        SETGET(Vec4, specular_color_, SpecularColor)
        SETGET(int, shininess_, Shininess)
    };
}

#endif
