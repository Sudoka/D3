//
//  Material.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Material_hpp
#define _Material_hpp

namespace d3 {
    class Vec4;
    
#pragma mark Interface
    class Material {
    public:       
    protected:
        Vec4 ambient_color;
        Vec4 diffuse_color;
        Vec4 specular_color;
        float shininess;
        
    public:
        Material();
        
        //! Sets up ambient and diffuse color
        void setAmbientAndDiffuseColor(Vec4 color);
        
        //! @return reference to ambient color
        const Vec4 & getAmbientColor() const { return ambient_color; }
        
        //! Sets up ambient color
        void setAmbientColor(const Vec4 color) { ambient_color = color; }
        
        //! @return reference to diffuse color
        const Vec4 & getDiffuseColor() const { return diffuse_color; }
        
        //! Sets up diffuse color
        void setDiffuseColor(const Vec4 color) { diffuse_color = color; }
        
        //! @return reference to specular color
        const Vec4 & getSpecularColor() const { return specular_color; }
        
        //! Sets up specular color
        void setSpecularColor(const Vec4 color) { specular_color = color; }
        
        //! @return material's shininess exponent
        float getShininess() const { return shininess; }
        
        //! Sets up shininess exponent
        void setShininess(float value) { shininess = value; }
        
    };
}

#endif
