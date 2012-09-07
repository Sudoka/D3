//
//  DirectionalLight.cpp
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "DirectionalLight.hpp"


namespace d3 {
    DirectionalLight::DirectionalLight()
    {
        setDirection(Vec3(0, 0, 1));
    }
    
    void DirectionalLight::setDirection(Vec3 dir)
    {
        direction_ = dir;
    }
    
    Vec3 DirectionalLight::getDirection()
    {
        return direction_;
    }
}