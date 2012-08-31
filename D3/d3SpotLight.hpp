//
//  d3SpotLight.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3SpotLight_hpp
#define D3_d3SpotLight_hpp

#include "d3PointLight.hpp"

namespace d3 {
    
    class d3SpotLight : public d3PointLight {
    protected:
        float spot_cutoff_;      // 0..90 or 180
        float spot_exponent_;    // 0..128
        
        float spot_attenuation_[3];    // constant, linear and quadratic attenuation
        
    public:
        d3SpotLight();
        
        //! Gets direction
        d3Vec3 getDirection();
        
        //! d3StateOperation: applies state
        void apply();
    };
}

#endif
