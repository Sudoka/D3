//
//  d3DirectionalLight.cpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3DirectionalLight.hpp"


namespace d3 {
    d3Vec3 d3DirectionalLight::getDirection()
    {
        return d3Vec3(0,1,0); // FIX
    }
    
    void d3DirectionalLight::apply()
    {
        d3Vec3 p = getParent()->getPosition();
        glEnable(GL_LIGHTING) ;
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);    // FIX light number
        glLightfv(GL_LIGHT0, GL_POSITION, d3Vec4(p.x, p.y, p.z, 0.0));
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color_);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color_);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color_);
    }
}