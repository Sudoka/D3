//
//  SpotLight.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _SpotLight_hpp
#define _SpotLight_hpp

#include "PointLight.hpp"

namespace d3 {
    
    class SpotLight : public PointLight {
    protected:       
        SceneNode * target_node_;
        Vec3 direction_;
        
    public:
        SpotLight();
        
        virtual LightSourceParameters & getParametersRef();
        
        void setCutoff(float v);
        float getCutoff() const;
        
        void setExponent(float v);
        float getExponent() const;
        
        //! Look at target to follow
        void setTarget(SceneNode * target_node);
        
        //! Sets direction (Note: direction is rotated by orientation)
        void setDirection(Vec3 dir);
    };
}

#endif
