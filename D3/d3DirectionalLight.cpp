//
//  d3DirectionalLight.cpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3DirectionalLight.hpp"


namespace d3 {
    d3DirectionalLight::d3DirectionalLight()
    {
        setDirection(d3Vec3(0, 0, 1));
    }
    
    void d3DirectionalLight::setDirection(d3Vec3 dir)
    {
        direction_ = dir;
    }
    
    d3Vec3 d3DirectionalLight::getDirection()
    {
        return direction_;
    }
}