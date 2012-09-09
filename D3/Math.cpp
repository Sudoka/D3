//
//  Math.cpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Math.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"

namespace d3 {
    Mat4 getTranslationMatrix(Vec3 v)
    {
        Mat4 m;
        m.a03 = v.x;
        m.a13 = v.y;
        m.a23 = v.z;
        
        return m;
    }
    
    Mat4 getScalingMatrix(Vec3 v)
    {
        Mat4 m;
        m.a00 = v.x;
        m.a11 = v.y;
        m.a22 = v.z;
        return m;
    }
    
    Mat3 getRotationMatrix(Vec3 axis, float angle)
    {
        Mat3 m;
        
        double c = cosf(angle);
        double s = sinf(angle);
        double t = 1.0 - c;
        
        axis.normalize();
    
        m.a00 = c + axis.x*axis.x*t;
        m.a11 = c + axis.y*axis.y*t;
        m.a22 = c + axis.z*axis.z*t;
        
        double tmp1 = axis.x*axis.y*t;
        double tmp2 = axis.z*s;
        m.a10 = tmp1 + tmp2;
        m.a01 = tmp1 - tmp2;
        tmp1 = axis.x*axis.z*t;
        tmp2 = axis.y*s;
        m.a20 = tmp1 - tmp2;
        m.a02 = tmp1 + tmp2;    tmp1 = axis.y*axis.z*t;
        tmp2 = axis.x*s;
        m.a21 = tmp1 + tmp2;
        m.a12 = tmp1 - tmp2;
        
        return m;
    }
    
    Vec3 lerp(Vec3 v0, Vec3 v1, float t)
    {
        return v0 * (1.0 - t) + v1 * t;
    }
    
    Quat lerp(Quat q0, Quat q1, float t)
    {
        return q0.scale(1.0 - t) + q1.scale(t);
    }
    
    Quat slerp(Quat q0, Quat q1, float t)
    {
		float cosOmega = q0.dot(q1);
        
		float q1w = q1.w;
        float q1x = q1.x;
        float q1y = q1.y;
        float q1z = q1.z;
        
        if (cosOmega < 0.0f) {
            q1w = -q1w;
            q1x = -q1x;
            q1y = -q1y;
            q1z = -q1z;
            cosOmega = -cosOmega;
        }
        
        assert(cosOmega < 1.1f);
        
        float k0, k1;
        
        if (cosOmega > 0.9999f) {
            k0 = 1.0f - t;
            k1 = t;
        } else {
            float sinOmega = sqrtf(1.0f - cosOmega*cosOmega);
            float omega = atan2(sinOmega, cosOmega);
            float oneOverSinOmega = 1.0f / sinOmega;
            
            k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
            k1 = sin(t * omega) * oneOverSinOmega;
        }
        
        return Quat(k0*q0.x + k1*q1x, k0*q0.y + k1*q1y, k0*q0.z + k1*q1z, k0*q0.w + k1*q1w);
    }
}