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
    bool aabbTest(Box b1, Box b2)
    {
        if (absf(b1.origin.x - b2.origin.x) > (b1.size.x + b2.size.x) / 2.0)
            return false;
        if (absf(b1.origin.y - b2.origin.y) > (b1.size.y + b2.size.y) / 2.0)
            return false;
        if (absf(b1.origin.z - b2.origin.z) > (b1.size.z + b2.size.z) / 2.0)
            return false;
        return true;
    }
    
    Mat4 getTranslationMat4(Vec3 v)
    {
        Mat4 m;
        m.a03 = v.x;
        m.a13 = v.y;
        m.a23 = v.z;
        
        return m;
    }
    
    Mat4 getScalingMat4(Vec3 v)
    {
        Mat4 m;
        m.a00 = v.x;
        m.a11 = v.y;
        m.a22 = v.z;
        return m;
    }
    
    Mat4 getRotationMat4(Vec3 v, float angle)
    {
        float c = cosf(angle);
        float s = sinf(angle);
        
        Mat4 m;
        m.a00 = v.x * v.x * (1-c) + c;
        m.a01 = v.x * v.y * (1-c) - v.z * s;
        m.a02 = v.x * v.z * (1-c) + v.y * s;
        
        m.a10 = v.y * v.x * (1-c) + v.z * s;
        m.a11 = v.y * v.y * (1-c) + c;
        m.a12 = v.y * v.z * (1-c) - v.x * s;
        
        m.a20 = v.z * v.x * (1-c) - v.y * s;
        m.a21 = v.z * v.y * (1-c) + v.x * s;
        m.a22 = v.z * v.z * (1-c) + c;
        
        return m;
    }
    
    Mat4 getFrustumMat4(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        Vec3 delta = Vec3(right, top, zFar) - Vec3(left, bottom, zNear);
        Vec3 sum = Vec3(right, top, zFar) + Vec3(left, bottom, zNear);
        Vec3 ratio = sum.div(delta);
        Vec3 twoRatio = Vec3(1, 1, 1).div(delta) * 2.0 * zNear;
        
        return Mat4(twoRatio.x, 0.0, ratio.x, 0.0,
                    0.0, twoRatio.y, ratio.y, 0.0,
                    0.0, 0.0, -ratio.z, -zNear*twoRatio.z,
                    0.0, 0.0, -1.0, 0.0);
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