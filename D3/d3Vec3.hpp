//
//  d3Vec3.hpp
//  D3
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Vec3_hpp
#define D3_d3Vec3_hpp

#include "d3mat3.hpp"
#include <cmath>

namespace d3 {
    
#pragma mark Interface
    class d3Vec3 {
    public:
        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            struct { float s, t, p; };
            float v[3];
        } __attribute__((aligned(16)));
        
    public:
        d3Vec3();
        
        d3Vec3(float x, float y, float z);
        
        bool operator==(const d3Vec3& b) const;
        bool operator!=(const d3Vec3& b) const;
        
        //! Component-wise addition.
        d3Vec3 operator+(const d3Vec3& b) const;
        
        //! Component-wise subtraction.
        d3Vec3 operator-(const d3Vec3& b) const;
        
        //! Dot product.
        float operator*(const d3Vec3& b) const;
        
        //! 1x3 vector by 3x3 matrix multiplication.
        d3Vec3 operator*(const d3Mat3& b) const;
        
        //! Scalar multiplication.
        d3Vec3 operator*(float k) const;
        
        //! Cross product.
        d3Vec3 cross(const d3Vec3& b) const;
        
        //! Component-wise multiplication
        d3Vec3 mul(const d3Vec3& b) const;
        
        //! Vector length.
        float length() const;
        
        //! Vector normalization.
        void normalize();
        
        //! Convert to const float*.
        operator const float*() const;
    };
    
#pragma mark Implementation
    inline d3Vec3::d3Vec3() : x(0.f), y(0.f), z(0.f) {}
    
    inline d3Vec3::d3Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    inline bool d3Vec3::operator==(const d3Vec3& b) const
    {
        return !( *this != b );
    }
    
    inline bool d3Vec3::operator!=(const d3Vec3& b) const
    {
        return x != b.x || y != b.y || z != b.z;
    }
    
    inline d3Vec3 d3Vec3::operator+(const d3Vec3& b) const
    {
        return d3Vec3(x + b.x, y + b.y, z + b.z);
    }
    
    inline d3Vec3 d3Vec3::operator-(const d3Vec3& b) const
    {
        return d3Vec3(x - b.x, y - b.y, z - b.z);
    }
    
    inline float d3Vec3::operator*(const d3Vec3& b) const
    {
        return x * b.x + y * b.y + z * b.z;
    }
    
    inline d3Vec3 d3Vec3::operator*(const d3Mat3& b) const
    {
        return d3Vec3(x * b.a00 + y * b.a10 + z * b.a20,
                      x * b.a01 + y * b.a11 + z * b.a21,
                      x * b.a02 + y * b.a12 + z * b.a22);
    }
    
    inline d3Vec3 d3Vec3::operator*(float k) const
    {
        return d3Vec3(k * x, k * y, k * z);
    }
    
    inline d3Vec3 d3Vec3::cross(const d3Vec3& b) const
    {
        return d3Vec3(y * b.z - z * b.y,
                      z * b.x - x * b.z,
                      x * b.y - y * b.x);
    }
    
    inline d3Vec3 d3Vec3::mul(const d3Vec3& b) const
    {
        return d3Vec3(x * b.x,
                      y * b.y,
                      z * b.z);
    }
    
    inline float d3Vec3::length() const
    {
        return sqrtf(x*x + y*y + z*z);
    }
    
    inline void d3Vec3::normalize()
    {
        float l = length();
        x = x / l;
        y = y / l;
        z = z / l;
    }
    
    inline d3Vec3::operator const float*() const
    {
        return (float*)this;
    }
}

#endif
