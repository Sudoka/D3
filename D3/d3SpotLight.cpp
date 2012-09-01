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
        spot_cutoff_ = 30;
        spot_exponent_ = 0;
        
        setDirection(d3Vec3(0, -1, 0));
        
        target_node_ = nullptr;
    }
    
    void d3SpotLight::setTarget(d3Node *target_node)
    {
        target_node_ = target_node;
    }
    
    void d3SpotLight::setDirection(d3Vec3 dir)
    {
        direction_ = dir;
    }
    
    d3Vec3 d3SpotLight::getDirection()
    {
        if (target_node_ != nullptr)
            return target_node_->getPosition() - getParent()->getPosition();
        
        return direction_;
    }
    
    void d3SpotLight::setCutoff(int v) { spot_cutoff_ = v; }    // TODO Boudaries
    int d3SpotLight::getCutoff() const { return spot_cutoff_; }
    
    void d3SpotLight::setExponent(int v) {spot_exponent_ = v; }
    int d3SpotLight::getExponent() const { return spot_exponent_; }
}