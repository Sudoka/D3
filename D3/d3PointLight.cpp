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
    
    void d3PointLight::setDiffuseColor(d3Vec4 color)
    {
        diffuse_color_ = color;
    }
    
    void d3PointLight::setSpecularColor(d3Vec4 color)
    {
        specular_color_ = color;
    }
    
    void d3PointLight::setAmbientAndDiffuseColor(d3Vec4 color)
    {
        ambient_color_ = diffuse_color_ = color;
    }
    
    bool d3PointLight::isVisible() const
    {
        return is_on_;
    }
    
    void d3PointLight::apply()
    {
        d3Vec3 p = getParent()->getPosition();
        glEnable ( GL_LIGHTING ) ;
        glEnable(GL_LIGHT0);    // FIX light number
        glLightfv(GL_LIGHT0, GL_POSITION, d3Vec4(p.x, p.y, p.z, 1.0));
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color_);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color_);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color_);
    }
}