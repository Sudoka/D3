//
//  d3Material.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3material_hpp
#define D3_d3material_hpp

namespace d3 {
    class d3Vec4;
    
#pragma mark Interface
    class d3Material {
    protected:
        d3Vec4 ambient_color_;
        d3Vec4 diffuse_color_;
        d3Vec4 specular_color_;
        int shininess_;             // 0..128
        
    public:
        d3Material();
        
        void setAmbientAndDiffuseColor(d3Vec4 color);
        
        void setAmbientColor(d3Vec4 color);
        d3Vec4 getAmbientColor() const;
        
        void setDiffuseColor(d3Vec4 color);
        d3Vec4 getDiffuseColor() const;
        
        void setSpecularColor(d3Vec4 color);
        d3Vec4 getSpecularColor() const;
        
        void setShininess(int value);
        int getShininess() const;
    };
}

#endif
