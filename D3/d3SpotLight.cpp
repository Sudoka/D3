//
//  d3SpotLight.cpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3SpotLight.hpp"

namespace d3 {
    d3SpotLight::d3SpotLight()
    {
        spot_cutoff_ = 60;
        spot_exponent_ = 0;
        spot_attenuation_[0] = 1;   // constant
        spot_attenuation_[1] = 0;   // linear
        spot_attenuation_[2] = 0;   // quadratic
    }
    
    d3Vec3 d3SpotLight::getDirection()
    {
        return d3Vec3(0,1,0); // FIX
    }
    
    void d3SpotLight::apply()
    {
        d3Vec3 p = getParent()->getPosition();
        glEnable ( GL_LIGHTING ) ;
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);    // FIX light number
        glLightfv(GL_LIGHT0, GL_POSITION, d3Vec4(p.x, p.y, p.z, 1.0));
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color_);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color_);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color_);
        
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff_);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent_);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, getDirection());
        
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, spot_attenuation_[0]);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, spot_attenuation_[1]);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, spot_attenuation_[2]);
        
    }
}