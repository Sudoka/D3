//
//  PointLight.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _PointLight_hpp
#define _PointLight_hpp

#include "Node.hpp"

namespace d3 {
    class Vec4;
    
#pragma mark Interface
    class PointLight : public Node::Attachment {
    public:
        struct LightSourceParameters {
            Vec4 ambient;
            Vec4 diffuse;
            Vec4 specular;
            Vec4 position;
            Vec3 spotDirection;
            float spotExponent;
            float spotCutoff; // (range: [0.0,90.0], 180.0)
            float spotCosCutoff; // (range: [1.0,0.0],-1.0)
            Vec3 attenuation;
        };
        
    protected:
        LightSourceParameters parameters;
        
    public:
        PointLight();
        
        virtual PointLight * clone() const {
            PointLight * p = new PointLight();
            p->parameters = parameters;
            return p;
        }
        
        virtual LightSourceParameters & getParametersRef();
                
        SETGET(Vec4, parameters.ambient, AmbientColor)
        SETGET(Vec4, parameters.diffuse, DiffuseColor)
        SETGET(Vec4, parameters.specular, SpecularColor)
        SETGET(Vec3, parameters.attenuation, Attenuation)
    };
}

#endif
