//
//  PointLight.cpp
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "PointLight.hpp"

namespace d3 {
    PointLight::PointLight()
    {
        setAmbientColor(Vec4(0.1, 0.1, 0.1, 1.0));
        setDiffuseColor(Vec4(1.0, 1.0, 1.0, 1.0));
        setSpecularColor(Vec4(1.0, 1.0, 1.0, 1.0));
        setAttenuation(Vec3(1, 0, 0));
        setOn(true);
    }
    
    void PointLight::setOn(bool state)
    {
        is_on_ = state;
    }
}