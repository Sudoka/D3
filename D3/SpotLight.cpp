//
//  SpotLight.cpp
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SpotLight.hpp"

namespace d3 {
    SpotLight::SpotLight()
    {
        parameters.spotCutoff = 30;
        parameters.spotCosCutoff = 0.866025404;
        parameters.spotExponent = 1.0;
        parameters.spotDirection = Vec3(0, -1, 0);
        parameters.position = Vec4(0.0, 0.0, 0.0, 1.0);
        
        direction_ = Vec3(0, -1, 0);
        
        target_node_ = nullptr;
    }
    
    SpotLight::LightSourceParameters & SpotLight::getParametersRef()
    {
        if (target_node_ != nullptr)
            parameters.spotDirection = target_node_->getDerivedPosition() - getParent()->getDerivedPosition();
        
        parameters.spotDirection = getParent()->getDerivedOrientation() * direction_;
        
        return parameters;
    }
    
    void SpotLight::setTarget(SceneNode *target_node)
    {
        target_node_ = target_node;
    }
    
    void SpotLight::setDirection(Vec3 dir)
    {
        direction_ = dir;
    }
    
    void SpotLight::setCutoff(float v) { parameters.spotCutoff = v; parameters.spotCosCutoff = cosf(v * kPiOver180); }
    float SpotLight::getCutoff() const { return parameters.spotCutoff; }
    
    void SpotLight::setExponent(float v) {parameters.spotExponent = v; }
    float SpotLight::getExponent() const { return parameters.spotExponent; }
}