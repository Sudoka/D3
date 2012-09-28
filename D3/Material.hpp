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
        
        const Vec4 & getAmbientColor() const {
            return ambient_color_;
        }
        
        void setAmbientColor(const Vec4 color) {
            ambient_color_ = color;
        }
        
        const Vec4 & getDiffuseColor() const {
            return diffuse_color_;
        }
        
        void setDiffuseColor(const Vec4 color) {
            diffuse_color_ = color;
        }
        
        const Vec4 & getSpecularColor() const {
            return specular_color_;
        }
        
        void setSpecularColor(const Vec4 color) {
            specular_color_ = color;
        }
        
        SETGET(int, shininess_, Shininess)
    };
}

#endif
