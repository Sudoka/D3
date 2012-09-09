//
//  math.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _math_hpp
#define _math_hpp

#include <cmath>

namespace d3 {
    class Mat3;
    class Mat4;
    class Vec3;
    class Quat;
    
    // Commonly used constants
    const float kPi = 3.14159265f;
    const float k2Pi = 2.0f * kPi;
    const float kPiOver2 = kPi / 2.0f;
    const float kPiOver180 = kPi / 180.0f;
    const float k1OverPi = 1.0f / kPi;
    const float k1Over2Pi = 1.0f / k2Pi;
    
    //! Wraps an angle in range -pi,pi
    float wrapPi(float theta);
    
    //! Same as acos(x) but if x is out of range, it is clamped
    //! to the nearest valid value.
    float safeAcos(float x);
    
    struct Frustum {
        float left, right;
        float down, up;
        float near, far;
    };
    
    float clamp(float min, float max, float value);
    
    //! Transform matrices
    Mat4 getTranslationMatrix(Vec3 v);
    
    Mat4 getScalingMatrix(Vec3 v);
    
    Mat3 getRotationMatrix(Vec3 axis, float angle);
    
    Vec3 lerp(Vec3 v0, Vec3 v1, float t);
    
    //! Linear Quaternion interpolation
    Quat lerp(Quat q0, Quat q1, float t);
    
    //! Spherical Quaternion interpolation
    Quat slerp(Quat q0, Quat q1, float t);
    
    float randf();
    
    int randi(int min, int max);
    
    
#pragma mark Implementation
    inline float clamp(float min, float max, float value) {
        return (value < min) ? min : ( value > max ? max : value );
    }
    
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
    
    inline float randf() {
        return (float)(rand() % 65000) / 65000.0;
    }
    
    inline int randi(int min, int max) {
        return rand() % (-min + max) + min; // fix?
    }
}

#endif
