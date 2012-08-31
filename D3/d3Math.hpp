//
//  d3math.hpp
//  D3
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3math_hpp
#define D3_d3math_hpp

#include <cmath>

namespace d3 {
    
    // Commonly used constants
    const float kPi = 3.14159265f;
    const float k2Pi = 2.0f * kPi;
    const float kPiOver2 = kPi / 2.0f;
    const float k1OverPi = 1.0f / kPi;
    const float k1Over2Pi = 1.0f / k2Pi;
    
    //! Wraps an angle in range -pi,pi
    float wrapPi(float theta);
    
    //! Same as acos(x) but if x is out of range, it is clamped
    //! to the nearest valid value.
    float safeAcos(float x);
    
    
#pragma mark Implementation
    inline float wrapPi(float theta) {
        theta += kPi;
        theta -= floor(theta * k1Over2Pi) * k2Pi;
        theta -= kPi;
        return theta;
    }
    
    inline float safeAcos(float x) {
        if (x <= -1.0f) {
            return kPi;
        } else if (x >= 1.0f) {
            return 0.0f;
        }
        
        return acosf(x);
    }
}

#endif
