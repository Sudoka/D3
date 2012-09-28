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
        m.m[12] = v.x;
        m.m[13] = v.y;
        m.m[14] = v.z;
        
        return m;
    }
    
    Mat4 getScalingMat4(Vec3 v)
    {
        Mat4 m;
        m.m[0] = v.x;
        m.m[5] = v.y;
        m.m[10] = v.z;
        return m;
    }
    
    Mat4 getRotationMat4(Vec3 v, float angle)
    {
        float c = cosf(angle);
        float s = sinf(angle);
        float cc = 1.0f - c;
        
        return Mat4(
            c + cc * v.x * v.x,
            cc * v.x * v.y + v.z * s,
            cc * v.x * v.z - v.y * s,
            0.0f,
            cc * v.x * v.y - v.z * s,
            c + cc * v.y * v.y,
            cc * v.y * v.z + v.x * s,
            0.0f,
            cc * v.x * v.z + v.y * s,
            cc * v.y * v.z - v.x * s,
            c + cc * v.z * v.z,
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f);
    }
    
    Mat4 getPerspective(float fovy, float aspect, float zNear, float zFar)
    {
        float ctg = 1.0f / tanf(fovy / 2.0f);
        
        return Mat4(ctg / aspect, 0.0f, 0.0f, 0.0f,
                    0.0f, ctg, 0.0f, 0.0f,
                    0.0f, 0.0f, (zFar + zNear) / (zNear - zFar), -1.0f,
                    0.0f, 0.0f, (2.0f * zFar * zNear) / (zNear - zFar), 0.0f);
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
//
//    Mat3 getRotationMatrix(Vec3 axis, float angle)
//    {
//        Mat3 m;
//        
//        double c = cosf(angle);
//        double s = sinf(angle);
//        double t = 1.0 - c;
//        
//        axis.normalize();
//    
//        m.a00 = c + axis.x*axis.x*t;
//        m.a11 = c + axis.y*axis.y*t;
//        m.a22 = c + axis.z*axis.z*t;
//        
//        double tmp1 = axis.x*axis.y*t;
//        double tmp2 = axis.z*s;
//        m.a10 = tmp1 + tmp2;
//        m.a01 = tmp1 - tmp2;
//        tmp1 = axis.x*axis.z*t;
//        tmp2 = axis.y*s;
//        m.a20 = tmp1 - tmp2;
//        m.a02 = tmp1 + tmp2;    tmp1 = axis.y*axis.z*t;
//        tmp2 = axis.x*s;
//        m.a21 = tmp1 + tmp2;
//        m.a12 = tmp1 - tmp2;
//        
//        return m;
//    }
    
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