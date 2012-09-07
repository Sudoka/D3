//
//  PointLight.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _PointLight_hpp
#define _PointLight_hpp

#include "Node.hpp"

namespace d3 {
    class Vec4;
    
#pragma mark Interface
    class PointLight : public Node::Attachment {
    protected:
        Vec4 ambient_color_;
        Vec4 diffuse_color_;
        Vec4 specular_color_;
        
        Vec3 attenuation_;    // constant, linear and quadratic attenuation

        bool is_on_;
        
    public:
        PointLight();
        
        void setOn(bool state);
        
        SETGET(Vec4, ambient_color_, AmbientColor)
        SETGET(Vec4, diffuse_color_, DiffuseColor)
        SETGET(Vec4, specular_color_, SpecularColor)
        SETGET(Vec3, attenuation_, Attenuation)               
    };
}

#endif
