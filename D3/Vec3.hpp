//
//  Vec3.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Vec3_hpp
#define _Vec3_hpp

#include "mat3.hpp"
#include <cmath>

namespace d3 {
    
#pragma mark Interface
    class Vec3 {
    public:
        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            struct { float s, t, p; };
            float v[3];
        } __attribute__((aligned(16)));
        
    public:
        Vec3();
        
        Vec3(float x, float y, float z);
        
        bool operator==(const Vec3& b) const;
        bool operator!=(const Vec3& b) const;
        
        //! Component-wise addition.
        Vec3 operator+(const Vec3& b) const;
        
        //! Component-wise subtraction.
        Vec3 operator-(const Vec3& b) const;
        
        //! Dot product.
        float operator*(const Vec3& b) const;
        
        //! 1x3 vector by 3x3 matrix multiplication.
        Vec3 operator*(const Mat3& b) const;
        
        //! Scalar multiplication.
        Vec3 operator*(float k) const;
        
        //! Cross product.
        Vec3 cross(const Vec3& b) const;
        
        //! Component-wise multiplication
        Vec3 mul(const Vec3& b) const;
        
        //! Vector length.
        float length() const;
        
        //! Vector normalization.
        void normalize();
        
        //! Convert to const float*.
        operator const float*() const;
    };
    
#pragma mark Implementation
    inline Vec3::Vec3() : x(0.f), y(0.f), z(0.f) {}
    
    inline Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    inline bool Vec3::operator==(const Vec3& b) const
    {
        return !( *this != b );
    }
    
    inline bool Vec3::operator!=(const Vec3& b) const
    {
        return x != b.x || y != b.y || z != b.z;
    }
    
    inline Vec3 Vec3::operator+(const Vec3& b) const
    {
        return Vec3(x + b.x, y + b.y, z + b.z);
    }
    
    inline Vec3 Vec3::operator-(const Vec3& b) const
    {
        return Vec3(x - b.x, y - b.y, z - b.z);
    }
    
    inline float Vec3::operator*(const Vec3& b) const
    {
        return x * b.x + y * b.y + z * b.z;
    }
    
    inline Vec3 Vec3::operator*(const Mat3& b) const
    {
        return Vec3(x * b.a00 + y * b.a10 + z * b.a20,
                      x * b.a01 + y * b.a11 + z * b.a21,
                      x * b.a02 + y * b.a12 + z * b.a22);
    }
    
    inline Vec3 Vec3::operator*(float k) const
    {
        return Vec3(k * x, k * y, k * z);
    }
    
    inline Vec3 Vec3::cross(const Vec3& b) const
    {
        return Vec3(y * b.z - z * b.y,
                      z * b.x - x * b.z,
                      x * b.y - y * b.x);
    }
    
    inline Vec3 Vec3::mul(const Vec3& b) const
    {
        return Vec3(x * b.x,
                      y * b.y,
                      z * b.z);
    }
    
    inline float Vec3::length() const
    {
        return sqrtf(x*x + y*y + z*z);
    }
    
    inline void Vec3::normalize()
    {
        float l = length();
        x = x / l;
        y = y / l;
        z = z / l;
    }
    
    inline Vec3::operator const float*() const
    {
        return (float*)this;
    }
}

#endif
