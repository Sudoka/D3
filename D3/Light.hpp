//
//  Light.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Light_hpp
#define _Light_hpp

#include "SceneNode.hpp"

namespace d3 {
    class Vec4;
    
    class Light : public Movable {
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

    public:
        //! Default constructor
        Light(SceneNode & mover);
        
        //! Destructor
        virtual ~Light();
        
        //! @return reference to light parameters
        virtual LightSourceParameters & getParametersRef();
                
        //! @return reference to ambient color
        const Vec4 & getAmbientColor() const;
        
        //! Sets up ambient color
        void setAmbientColor(const Vec4 color);
        
        //! @return reference to diffuse color
        const Vec4 & getDiffuseColor() const;
        
        //! Sets up diffuse color
        void setDiffuseColor(const Vec4 color);
        
        //! @return reference to specular color
        const Vec4 & getSpecularColor() const;
        
        //! Sets up specular color
        void setSpecularColor(const Vec4 color);
        
        //! @return reference attenuation coefficients
        const Vec3 & getAttenuation() const;
        
        //! Sets up attenuation linear (x), quadratic (y) and cubic (z) coefficients
        void setAttenuation(const Vec3 attenuation);
        
        //! Sets cutoff angle in degrees. For point light set to 180.
        void setCutoff(float v);
        
        //! @return cutoff angle in degrees
        float getCutoff() const;
        
        //! Sets spot exponent (0.0, 128.0)
        void setSpotExponent(float v);
        
        //! @return spot exponent
        float getSpotExponent() const;
        
        //! Look at target to follow
        void setTarget(SceneNode * target_node);
        
        //! Sets direction (Note: direction is rotated by orientation)
        void setDirection(Vec4 dir);
        
    protected:
        LightSourceParameters parameters;
        SceneNode * target_node;
        Vec4 direction;
    };
}

#endif
