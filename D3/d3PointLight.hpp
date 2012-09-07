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
        
        SETGET(d3Vec4, ambient_color_, AmbientColor)
        SETGET(d3Vec4, diffuse_color_, DiffuseColor)
        SETGET(d3Vec4, specular_color_, SpecularColor)
        SETGET(d3Vec3, attenuation_, Attenuation)               
    };
}

#endif
