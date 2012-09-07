//
//  Quat.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Quat_hpp
#define _Quat_hpp

#include "Math.hpp"
#include "Vec3.hpp"
#include "Mat3.hpp"
#include "Mat4.hpp"

#define TOLERANCE 0.00001f

namespace d3 {
#pragma mark Interface
    class Quat {
    public:
        union {
            struct { float x, y, z, w; };
            float q[4];
        } __attribute__((aligned(16)));
        
    public:
        //! Default constructor (identity).
        Quat();
        
        //! From floats.
        Quat(float x, float y, float z, float w);
        
        //! From axies and angle.
        Quat(Vec3 v, float s);
        
        //! From 3x3 matrix.
        Quat(Mat3 m);
        
        //! From 4x4 matrix.
        Quat(Mat4 m);
        
        void normalise();
        
        Quat conjugate() const;
        
        //! Addition.
        Quat operator+(const Quat& b) const;
        
        //! Subtraction.
        Quat operator-(const Quat& b) const;
        
        //! Multiplication.
        Quat operator*(const Quat& b) const;
        
        //! Multiplication with vector.
        Vec3 operator*(const Vec3& b) const;
        
        float getRotationAngle() const;
        
        Vec3 getRotationAxis() const;
    };
    
#pragma mark Implementation
    inline Quat::Quat() : x(0.f), y(0.f), z(0.f), w(1.f)
    {
    }
    
    inline Quat::Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
    {
    }
    
    inline Quat::Quat(Vec3 axies, float angle)
    {
        float sinAngle = sinf(angle * 0.5f);
        Vec3 vn(axies);
        vn.normalize();
        
        x = vn.x * sinAngle;
        y = vn.y * sinAngle;
        z = vn.z * sinAngle;
        w = cosf(angle * 0.5f);
    }
    
    inline Quat::Quat(Mat3 m)
    {
    }
    
    inline Quat::Quat(Mat4 m)
    {
    }
    
    inline void Quat::normalise()
    {
        float mag2 = w*w + x*x + y*y + z*z;
        if (fabsf(mag2) > TOLERANCE && fabsf(mag2 - 1.f) > TOLERANCE) {
            float mag = sqrtf(mag2);
            w /= mag;
            x /= mag;
            y /= mag;
            z /= mag;
        }
    }
    
    inline Quat Quat::conjugate() const
    {
        return Quat(-x, -y, -z, w);
    }
    
    inline Quat Quat::operator+(const Quat& rq) const
    {
        return Quat();
    }
    
    inline Quat Quat::operator-(const Quat& rq) const
    {
        return Quat();
    }
    
    inline Quat Quat::operator*(const Quat& rq) const
    {
        return Quat(w * rq.x + x * rq.w + y * rq.z - z * rq.y,
                      w * rq.y + y * rq.w + z * rq.x - x * rq.z,
                      w * rq.z + z * rq.w + x * rq.y - y * rq.x,
                      w * rq.w - x * rq.x - y * rq.y - z * rq.z);
    }
    
    inline Vec3 Quat::operator*(const Vec3& b) const
    {
        Vec3 vn(b);
        vn.normalize();
        
        Quat vecQuat(vn.x, vn.y, vn.z, 0.f);
        Quat resQuat = vecQuat * conjugate();
        resQuat = (*this) * resQuat;
        
        return Vec3(resQuat.x, resQuat.y, resQuat.z);
    }
    
    inline float Quat::getRotationAngle() const
    {
        // w = cos(theta / 2)
        return safeAcos(w) * 2.0f;
    }
    
    inline Vec3 Quat::getRotationAxis() const
    {
        // w = cos(theta/2)
        // sin^2(x) + cos^2(x) = 1
        float sinThetaOver2Sq = 1.0f - w*w;
        
        // Protect against numerical imprecision
        if (sinThetaOver2Sq <= 0.0f)
            return Vec3(1.0f, 0.0f, 0.0f);
    
        float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
        
        return Vec3(x * oneOverSinThetaOver2,
                      y * oneOverSinThetaOver2,
                      z * oneOverSinThetaOver2
                      );
    }
    
}

#endif
