//
//  d3PointLight.cpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3PointLight.hpp"

namespace d3 {
    d3PointLight::d3PointLight()
    {
        setAmbientColor(d3Vec4(0.1, 0.1, 0.1, 1.0));
        setDiffuseColor(d3Vec4(1.0, 1.0, 1.0, 1.0));
        setSpecularColor(d3Vec4(1.0, 1.0, 1.0, 1.0));
        setAttenuation(d3Vec3(1, 0, 0));
        setOn(true);
    }
    
    void d3PointLight::setOn(bool state)
    {
        is_on_ = state;
    }
    
    void d3PointLight::setAmbientColor(d3Vec4 color)
    {
        ambient_color_ = color;
    }
    
    d3Vec4 d3PointLight::getAmbientColor() const
    {
        return ambient_color_;
    }
    
    void d3PointLight::setDiffuseColor(d3Vec4 color)
    {
        diffuse_color_ = color;
    }
    
    d3Vec4 d3PointLight::getDiffuseColor() const
    {
        return diffuse_color_;
    }
    
    void d3PointLight::setSpecularColor(d3Vec4 color)
    {
        specular_color_ = color;
    }
    
    d3Vec4 d3PointLight::getSpecularColor() const
    {
        return specular_color_;
    }
    
    void d3PointLight::setAttenuation(d3Vec3 a)
    {
        attenuation_.x = a.x;   // constant
        attenuation_.y = a.y;   // linear
        attenuation_.z = a.z;   // quadratic
    }
    
    d3Vec3 d3PointLight::getAttenuation() const
    {
        return attenuation_;
    }
}