//
//  Vec4.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Vec4_hpp
#define _Vec4_hpp

#include "Vec3.hpp"
//#include "Mat4.hpp"
#include <cmath>

namespace d3 {
    
#pragma mark Interface
    class Vec4 {
    public:
        union {
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
            struct { float s, t, p, q; };
            float v[4];
        } __attribute__((aligned(16)));
        
    public:
        Vec4();
        
        Vec4(const Vec3 & vec) {
            Vec4(vec.x, vec.y, vec.z, 1.0);
        }
        
        Vec4(float x, float y, float z, float w);
        
        bool operator==(const Vec4& b) const;
        bool operator!=(const Vec4& b) const;
        
        //! Component-wise addition.
        Vec4 operator+(const Vec4& b) const;
        
        //! Component-wise subtraction.
        Vec4 operator-(const Vec4& b) const;
        
        //! Dot product.
        float operator*(const Vec4& b) const;
        
        //! 1x4 vector by 4x4 matrix multiplication.
        //Vec4 operator*(const Mat4& b) const;
        
        //! Scalar multiplication.
        Vec4 operator*(float k) const;
        
        //! Cross product.
        Vec4 cross(const Vec4& b) const;
        
        //! Component-wise multiplication
        Vec4 mul(const Vec4& b) const;
        
        //! Vector length.
        float length() const;
        
        //! Vector normalization.
        void normalize();
        
        //! Convert to const float*.
        operator const float*() const;
        
        //! Convert to Vec3
        operator Vec3() const;
    };
    
#pragma mark Implementation
    inline Vec4::Vec4() : x(0.f), y(0.f), z(0.f), w(1.f) {}
    
    inline Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    
    inline bool Vec4::operator==(const Vec4& b) const {
        return !( *this != b );
    }
    
    inline bool Vec4::operator!=(const Vec4& b) const {
        return x != b.x || y != b.y || z != b.z || w != b.w;
    }
    
    inline Vec4 Vec4::operator+(const Vec4& b) const {
        return Vec4(x + b.x, y + b.y, z + b.z, w + b.w);
    }
    
    inline Vec4 Vec4::operator-(const Vec4& b) const {
        return Vec4(x - b.x, y - b.y, z - b.z, w - b.w);
    }
    
    inline float Vec4::operator*(const Vec4& b) const {
        return x * b.x + y * b.y + z * b.z + w + b.w;
    }
    
//    inline Vec4 Vec4::operator*(const Mat4& b) const {
//        return Vec4(x * b.a00 + y * b.a10 + z * b.a20 + w * b.a30,
//                       x * b.a01 + y * b.a11 + z * b.a21 + w * b.a31,
//                       x * b.a02 + y * b.a12 + z * b.a22 + w * b.a32,
//                       x * b.a03 + y * b.a13 + z * b.a23 + w * b.a33);
//    }
    
    inline Vec4 Vec4::operator*(float k) const {
        return Vec4(k * x, k * y, k * z, k * w);
    }
    
    inline Vec4 Vec4::cross(const Vec4& b) const {
        // TODO: fix homogenus!
        return Vec4(y * b.z - z * b.y,
                       z * b.x - x * b.z,
                       x * b.y - y * b.x,
                       1.0);
    }
    
    inline Vec4 Vec4::mul(const Vec4& b) const
    {
        return Vec4(x * b.x,
                      y * b.y,
                      z * b.z,
                      w * b.w);
    }
    
    inline float Vec4::length() const {
        return sqrtf(x*x + y*y + z*z + w*w);
    }
    
    inline void Vec4::normalize() {
        float l = length();
        x = x / l;
        y = y / l;
        z = z / l;
        w = w / l;
    }
    
    inline Vec4::operator const float*() const {
        return v;
    }
    
    inline Vec4::operator Vec3() const {
        return Vec3(x / w, y / w, z / w);
    }
}

#endif
