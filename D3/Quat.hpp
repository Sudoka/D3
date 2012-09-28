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
#include <assert.h>

#define TOLERANCE 0.0000001f

namespace d3 {
#pragma mark Interface
    class Quat {
    public:
        union {
            struct { float x, y, z, w; };
            struct { Vec3 v; float s; };
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
        
        Quat normalized() const;
        
        Quat conjugate() const;
        
        Quat inverse() const;
        
        Quat scale(float k) const;
        
        float norm() const;
        
        float dot(Quat rq) const;
        
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
        
        operator Mat4 () const;
    };
    
#pragma mark Implementation
    inline Quat::Quat() : x(0.f), y(0.f), z(0.f), w(1.f)
    {
    }
    
    inline Quat::Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
    {
    }
    
    inline Quat::Quat(Vec3 axis, float theta)
    {
        assert(fabs(axis.length() - 1.0f) < 0.01f); // Compute the half angle and its sin
        
        float thetaOver2 = theta * .5f;
        float sinThetaOver2 = sin(thetaOver2); // Set the values
        w = cos(thetaOver2);
        x = axis.x * sinThetaOver2; y = axis.y * sinThetaOver2; z = axis.z * sinThetaOver2;
    }
    
    inline Quat::Quat(Mat3 m)
    {
    }
    
    inline Quat::Quat(Mat4 m)
    {
    }
    
    inline void Quat::normalise()
    {
        float mag = (float)sqrt(w*w + x*x + y*y + z*z);
        
        // Check for bogus length to protect against divide by zero
        if (mag > 0.0f) {
            // Normalize it
            float oneOverMag = 1.0f / mag;
            
            w *= oneOverMag;
            x *= oneOverMag;
            y *= oneOverMag;
            z *= oneOverMag;
        } else {
            // Houston, we have a problem
            //assert(false);
            // In a release build, just slam it to something
            w = 1.0f;
            x = y = z = 0.0f;
        }
    }
    
    inline Quat Quat::normalized() const
    {
        Quat q(*this);
        q.normalise();
        return q;
    }
    
    inline Quat Quat::conjugate() const
    {
        return Quat(-x, -y, -z, w);
    }
    
    inline Quat Quat::inverse() const
    {
        return conjugate().scale(1.0/norm());
    }
    
    inline Quat Quat::scale(float k) const
    {
        return Quat(x*k, y*k, z*k, w*k);
    }
    
    inline float Quat::norm() const
    {
        return (w*w + x*x + y*y + z*z);
    }
    
    inline float Quat::dot(d3::Quat rq) const
    {
        return w * rq.w + x * rq.x + y * rq.y + z * rq.z;
    }
    
    inline Quat Quat::operator+(const Quat& rq) const
    {
        return Quat(x+rq.x, y+rq.y, z+rq.z, w+rq.w);
    }
    
    inline Quat Quat::operator-(const Quat& rq) const
    {
        return Quat(x-rq.x, y-rq.y, z-rq.z, w-rq.w);
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
    
    inline Quat::operator Mat4 () const
    {
//        Mat4 m;
//        // Compute a few values to optimize common subexpressions
//        float ww = 2.0f * w;
//        float xx = 2.0f * x;
//        float yy = 2.0f * y;
//        float zz = 2.0f * z;
//
//        m.a00 = 1.0f - yy*y - zz*z;
//        m.a01 = xx*y + ww*z;
//        m.a02 = xx*z - ww*x;
//        m.a10 = xx*y - ww*z;
//        m.a11 = 1.0f - xx*x - zz*z;
//        m.a12 = yy*z + ww*x;
//        m.a20 = xx*z + ww*y;
//        m.a21 = yy*z - ww*x;
//        m.a22 = 1.0f - xx*x - yy*y;
//        
//        return m;
        
//        return getRotationMat4(getRotationAxis(), getRotationAngle());
               
        float _2x = x + x;
        float _2y = y + y;
        float _2z = z + z;
        float _2w = w + w;
        
        return Mat4( 1.0f - _2y * y - _2z * z,
            _2x * y + _2w * z,
            _2x * z - _2w * y,
            0.0f,
            _2x * y - _2w * z,
            1.0f - _2x * x - _2z * z,
            _2y * z + _2w * x,
            0.0f,
            _2x * z + _2w * y,
            _2y * z - _2w * x,
            1.0f - _2x * x - _2y * y,
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f );
    }
    
}

#endif
