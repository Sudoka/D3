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
}