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
        
        parameters.spotCosCutoff = -1.0;
        parameters.spotCutoff = 180.0;
    }
    
     PointLight::LightSourceParameters &  PointLight::getParametersRef()
    {
        Vec3 pos = getParent()->getDerivedPosition();
        parameters.position = Vec4(pos.x, pos.y, pos.z, 1.0);
        return parameters;
    }
}