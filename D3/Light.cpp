//
//  Light.cpp
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Light.hpp"

namespace d3 {
    Light::Light(SceneNode & mover) : Movable(mover)
    {
        setAmbientColor(Vec4(0.1, 0.1, 0.1, 1.0));
        setDiffuseColor(Vec4(1.0, 1.0, 1.0, 1.0));
        setSpecularColor(Vec4(1.0, 1.0, 1.0, 1.0));
        setAttenuation(Vec3(1, 0, 0));
        
        parameters.position = Vec4(0.0, 0.0, 0.0, 1.0);
        parameters.spotCosCutoff = -1.0;
        parameters.spotCutoff = 180.0;
        parameters.spotExponent = 1.0;
        parameters.spotDirection = Vec3(0, -1, 0);
        
        direction = Vec3(0, -1, 0);
        target_node = nullptr;
        
        Application::get().getRenderer().registerLight(this);
    }
    
    Light::~Light()
    {
    }
    
    //! @return reference to light parameters
    Light::LightSourceParameters &  Light::getParametersRef()
    {
        if (target_node)
            parameters.spotDirection = target_node->getDerivedPosition() - getMover().getDerivedPosition();
        else
            parameters.spotDirection = getMover().getDerivedOrientation() * Vec3(direction.x, direction.y, direction.z);
        
        if (direction.w == 0.0)
            parameters.position = direction;
        
        return parameters;
    }
    
    //! @return reference to ambient color
    const Vec4 & Light::getAmbientColor() const
    {
        return parameters.ambient;
    }
    
    //! Sets up ambient color
    void Light::setAmbientColor(const Vec4 color)
    {
        parameters.ambient = color;
    }
    
    //! @return reference to diffuse color
    const Vec4 & Light::getDiffuseColor() const
    {
        return parameters.diffuse;
    }
    
    //! Sets up diffuse color
    void Light::setDiffuseColor(const Vec4 color)
    {
        parameters.diffuse = color;
    }
    
    //! @return reference to specular color
    const Vec4 & Light::getSpecularColor() const
    {
        return parameters.specular;
    }
    
    //! Sets up specular color
    void Light::setSpecularColor(const Vec4 color)
    {
        parameters.specular = color;
    }
    
    //! @return reference attenuation coefficients
    const Vec3 & Light::getAttenuation() const
    {
        return parameters.attenuation;
    }
    
    //! Sets up attenuation linear (x), quadratic (y) and cubic (z) coefficients
    void Light::setAttenuation(const Vec3 attenuation)
    {
        parameters.attenuation = attenuation;
    }
    
    //! Sets cutoff angle in degrees. For point light set to 180.
    void Light::setCutoff(float v)
    {
        parameters.spotCutoff = v;
        parameters.spotCosCutoff = cosf(v * kPiOver180);
    }
    
    //! @return cutoff angle in degrees
    float Light::getCutoff() const
    {
        return parameters.spotCutoff;
    }
    
    //! Sets spot exponent (0.0, 128.0)
    void Light::setSpotExponent(float v)
    {
        parameters.spotExponent = v;
    }
    
    //! @return spot exponent
    float Light::getSpotExponent() const
    {
        return parameters.spotExponent;
    }
    
    //! Look at target to follow
    void Light::setTarget(SceneNode * target_node)
    {
        this->target_node = target_node;
    }
    
    //! Sets direction (Note: direction is rotated by orientation)
    void Light::setDirection(Vec4 dir)
    {
        direction = dir;
    }
}