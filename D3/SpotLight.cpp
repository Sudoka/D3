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
        spot_cutoff_ = 30;
        spot_exponent_ = 0;
        
        setDirection(Vec3(0, -1, 0));
        
        target_node_ = nullptr;
    }
    
    void SpotLight::setTarget(Node *target_node)
    {
        target_node_ = target_node;
    }
    
    void SpotLight::setDirection(Vec3 dir)
    {
        direction_ = dir;
    }
    
    Vec3 SpotLight::getDirection()
    {
        if (target_node_ != nullptr)
            return target_node_->getDerivedPosition() - getParent()->getDerivedPosition();
        
        return getParent()->getDerivedOrientation() * direction_;
    }
    
    void SpotLight::setCutoff(int v) { spot_cutoff_ = v; }    // TODO Boudaries
    int SpotLight::getCutoff() const { return spot_cutoff_; }
    
    void SpotLight::setExponent(int v) {spot_exponent_ = v; }
    int SpotLight::getExponent() const { return spot_exponent_; }
}