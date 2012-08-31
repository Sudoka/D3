//
//  d3Quat.hpp
//  D3
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Quat_hpp
#define D3_d3Quat_hpp

#include "d3Math.hpp"
#include "d3Vec3.hpp"
#include "d3Mat3.hpp"
#include "d3Mat4.hpp"

namespace d3 {
#pragma mark Interface
    class d3Quat {
    public:
        union {
            struct { float x, y, z, w; };
            float q[4];
        } __attribute__((aligned(16)));
        
    public:
        //! Default constructor (identity).
        d3Quat();
        
        //! From floats.
        d3Quat(float x, float y, float z, float w);
        
        //! From vector (imaginary) and scalar.
        d3Quat(d3Vec3 v, float s);
        
        //! From 3x3 matrix.
        d3Quat(d3Mat3 m);
        
        //! From 4x4 matrix.
        d3Quat(d3Mat4 m);
        
        //! Addition.
        d3Quat operator+(const d3Quat& b) const;
        
        //! Subtraction.
        d3Quat operator-(const d3Quat& b) const;
        
        //! Multiplication.
        d3Quat operator*(const d3Quat& b) const;
        
        float getRotationAngle() const;
        
        d3Vec3 getRotationAxis() const;
    };
    
#pragma mark Implementation
    inline d3Quat::d3Quat() : x(0.f), y(0.f), z(0.f), w(1.f)
    {
    }
    
    inline d3Quat::d3Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
    {
    }
    
    inline d3Quat::d3Quat(d3Vec3 v, float s) : x(v.x), y(v.y), z(v.z), w(s)
    {
    }
    
    inline d3Quat::d3Quat(d3Mat3 m)
    {
    }
    
    inline d3Quat::d3Quat(d3Mat4 m)
    {
    }
    
    inline d3Quat d3Quat::operator+(const d3Quat& b) const
    {
        return d3Quat();
    }
    
    inline d3Quat d3Quat::operator-(const d3Quat& b) const
    {
        return d3Quat();
    }
    
    inline d3Quat d3Quat::operator*(const d3Quat& b) const
    {
        return d3Quat();
    }
    
    inline float d3Quat::getRotationAngle() const
    {
        // w = cos(theta / 2)
        return safeAcos(w) * 2.0f * 180.0 * k1OverPi;
    }
    
    inline d3Vec3 d3Quat::getRotationAxis() const
    {
        // w = cos(theta/2)
        // sin^2(x) + cos^2(x) = 1
        float sinThetaOver2Sq = 1.0f - w*w;
        
        // Protect against numerical imprecision
        if (sinThetaOver2Sq <= 0.0f)
            return d3Vec3(1.0f, 0.0f, 0.0f);
    
        float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
        
        return d3Vec3(x * oneOverSinThetaOver2,
                      y * oneOverSinThetaOver2,
                      z * oneOverSinThetaOver2
                      );
    }
    
}

#endif
