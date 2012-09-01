//
//  d3PointLight.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3PointLight_hpp
#define D3_d3PointLight_hpp

#include "d3Node.hpp"

namespace d3 {
    class d3Vec4;
    
#pragma mark Interface
    class d3PointLight : public d3Node::Attachment {
    protected:
        d3Vec4 ambient_color_;
        d3Vec4 diffuse_color_;
        d3Vec4 specular_color_;
        
        d3Vec3 attenuation_;    // constant, linear and quadratic attenuation

        bool is_on_;
        
    public:
        d3PointLight();
        
        void setOn(bool state);
        
        void setAmbientColor(d3Vec4 color);
        d3Vec4 getAmbientColor() const;
        
        void setDiffuseColor(d3Vec4 color);
        d3Vec4 getDiffuseColor() const;
        
        void setSpecularColor(d3Vec4 color);
        d3Vec4 getSpecularColor() const;
        
        void setAttenuation(d3Vec3 a);
        d3Vec3 getAttenuation() const;
               
    };
}

#endif
