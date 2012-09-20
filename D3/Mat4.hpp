//
//  Mat4.hpp
//  
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Mat4_hpp
#define _Mat4_hpp

#include "Vec3.hpp"

namespace d3 {
    
#pragma mark Interface
    class Mat4 {
    public:
        union {
            struct {
                float a00, a01, a02, a03;
                float a10, a11, a12, a13;
                float a20, a21, a22, a23;
                float a30, a31, a32, a33;
            };
            float v[16];
        } __attribute__((aligned(16)));
        
    public:
        /*! Default constructor.
         *  Creates identity matrix.
         */
        Mat4();
        
        Mat4(float a00, float a01, float a02, float a03,
               float a10, float a11, float a12, float a13,
               float a20, float a21, float a22, float a23,
               float a30, float a31, float a32, float a33);
        
        bool operator==(const Mat4& b) const;
        bool operator!=(const Mat4& b) const;
        
        //! Component-wise addition.
        Mat4 operator+(const Mat4& b) const;
        
        //! Component-wise subtraction.
        Mat4 operator-(const Mat4& b) const;
        
        //! Matrix multiplication.
        Mat4 operator*(const Mat4& b) const;
        
        //! Scalar multiplication.
        Mat4 operator*(float f) const;
        
        //! Matrix transpose.
        Mat4 transpose() const;
        
        //! Matrix inverse.
        Mat4 inverse() const;
        
        //! Matrix determinant.
        float determinant() const;
        
        //! Convert to const float*
        operator float*();
        
        Vec3 operator*(const Vec3& b) const;
    };
    
#pragma mark Implementation
    inline Mat4::Mat4()
    :
    a00(1.f), a01(0.f), a02(0.f), a03(0.f),
    a10(0.f), a11(1.f), a12(0.f), a13(0.f),
    a20(0.f), a21(0.f), a22(1.f), a23(0.f),
    a30(0.f), a31(0.f), a32(0.f), a33(1.f)
    {
    }
    
    inline Mat4::Mat4(float a00, float a01, float a02, float a03,
                          float a10, float a11, float a12, float a13,
                          float a20, float a21, float a22, float a23,
                          float a30, float a31, float a32, float a33)
    :
    a00(a00), a01(a01), a02(a02), a03(a03),
    a10(a10), a11(a11), a12(a12), a13(a13),
    a20(a20), a21(a21), a22(a22), a23(a23),
    a30(a30), a31(a31), a32(a32), a33(a33)
    {
    }
    
    inline bool Mat4::operator==(const Mat4& b) const
    {
        return  !( *this != b );
    }
    
    inline bool Mat4::operator!=(const Mat4& b) const
    {
        return
        a00 != b.a00 || a01 != b.a01 || a02 != b.a02 || a03 != b.a03 ||
        a10 != b.a10 || a11 != b.a11 || a12 != b.a12 || a13 != b.a13 ||
        a20 != b.a20 || a21 != b.a21 || a22 != b.a22 || a23 != b.a23 ||
        a30 != b.a30 || a31 != b.a31 || a32 != b.a32 || a33 != b.a33;
    }
    
    inline Mat4 Mat4::operator+(const Mat4& b) const
    {
        return Mat4(a00 + b.a00, a01 + b.a01, a02 + b.a02, a03 + b.a03,
                      a10 + b.a10, a11 + b.a11, a12 + b.a12, a13 + b.a13,
                      a20 + b.a20, a21 + b.a21, a22 + b.a22, a23 + b.a23,
                      a30 + b.a30, a31 + b.a31, a32 + b.a32, a33 + b.a33);
    }
    
    inline Mat4 Mat4::operator-(const Mat4& b) const
    {
        return Mat4(a00 - b.a00, a01 - b.a01, a02 - b.a02, a03 - b.a03,
                      a10 - b.a10, a11 - b.a11, a12 - b.a12, a13 - b.a13,
                      a20 - b.a20, a21 - b.a21, a22 - b.a22, a23 - b.a23,
                      a30 - b.a30, a31 - b.a31, a32 - b.a32, a33 - b.a33);
    }
    
    inline Mat4 Mat4::operator*(const Mat4& b) const
    {
        return Mat4(a00 * b.a00 + a01 * b.a10 + a02 * b.a20 + a03 * b.a30,
                      a00 * b.a01 + a01 * b.a11 + a02 * b.a21 + a03 * b.a31,
                      a00 * b.a02 + a01 * b.a12 + a02 * b.a22 + a03 * b.a32,
                      a00 * b.a03 + a01 * b.a13 + a02 * b.a23 + a03 * b.a33,
                         
                      a10 * b.a00 + a11 * b.a10 + a12 * b.a20 + a13 * b.a30,
                      a10 * b.a01 + a11 * b.a11 + a12 * b.a21 + a13 * b.a31,
                      a10 * b.a02 + a11 * b.a12 + a12 * b.a22 + a13 * b.a32,
                      a10 * b.a03 + a11 * b.a13 + a12 * b.a23 + a13 * b.a33,
                         
                      a20 * b.a00 + a21 * b.a10 + a22 * b.a20 + a23 * b.a30,
                      a20 * b.a01 + a21 * b.a11 + a22 * b.a21 + a23 * b.a31,
                      a20 * b.a02 + a21 * b.a12 + a22 * b.a22 + a23 * b.a32,
                      a20 * b.a03 + a21 * b.a13 + a22 * b.a23 + a23 * b.a33,
                         
                      a30 * b.a00 + a31 * b.a10 + a32 * b.a20 + a33 * b.a30,
                      a30 * b.a01 + a31 * b.a11 + a32 * b.a21 + a33 * b.a31,
                      a30 * b.a02 + a31 * b.a12 + a32 * b.a22 + a33 * b.a32,
                      a30 * b.a03 + a31 * b.a13 + a32 * b.a23 + a33 * b.a33);
    }
    
    inline Mat4 Mat4::operator*(float f) const
    {
        return Mat4(a00 * f, a01 * f, a02 * f, a03 * f,
                      a10 * f, a11 * f, a12 * f, a13 * f,
                      a20 * f, a21 * f, a22 * f, a23 * f,
                      a30 * f, a31 * f, a32 * f, a33 * f);
    }
    
    inline Mat4 Mat4::transpose() const
    {
        return Mat4(a00, a10, a20, a30,
                      a01, a11, a21, a31,
                      a02, a12, a22, a32,
                      a03, a13, a23, a33);
    }
    
    inline Mat4 Mat4::inverse() const
    {
        return Mat4(a12*a23*a31 - a13*a22*a31 + a13*a21*a32 - a11*a23*a32 - a12*a21*a33 + a11*a22*a33,
                      a03*a22*a31 - a02*a23*a31 - a03*a21*a32 + a01*a23*a32 + a02*a21*a33 - a01*a22*a33,
                      a02*a13*a31 - a03*a12*a31 + a03*a11*a32 - a01*a13*a32 - a02*a11*a33 + a01*a12*a33,
                      a03*a12*a21 - a02*a13*a21 - a03*a11*a22 + a01*a13*a22 + a02*a11*a23 - a01*a12*a23,
                      a13*a22*a30 - a12*a23*a30 - a13*a20*a32 + a10*a23*a32 + a12*a20*a33 - a10*a22*a33,
                      a02*a23*a30 - a03*a22*a30 + a03*a20*a32 - a00*a23*a32 - a02*a20*a33 + a00*a22*a33,
                      a03*a12*a30 - a02*a13*a30 - a03*a10*a32 + a00*a13*a32 + a02*a10*a33 - a00*a12*a33,
                      a02*a13*a20 - a03*a12*a20 + a03*a10*a22 - a00*a13*a22 - a02*a10*a23 + a00*a12*a23,
                      a11*a23*a30 - a13*a21*a30 + a13*a20*a31 - a10*a23*a31 - a11*a20*a33 + a10*a21*a33,
                      a03*a21*a30 - a01*a23*a30 - a03*a20*a31 + a00*a23*a31 + a01*a20*a33 - a00*a21*a33,
                      a01*a13*a30 - a03*a11*a30 + a03*a10*a31 - a00*a13*a31 - a01*a10*a33 + a00*a11*a33,
                      a03*a11*a20 - a01*a13*a20 - a03*a10*a21 + a00*a13*a21 + a01*a10*a23 - a00*a11*a23,
                      a12*a21*a30 - a11*a22*a30 - a12*a20*a31 + a10*a22*a31 + a11*a20*a32 - a10*a21*a32,
                      a01*a22*a30 - a02*a21*a30 + a02*a20*a31 - a00*a22*a31 - a01*a20*a32 + a00*a21*a32,
                      a02*a11*a30 - a01*a12*a30 - a02*a10*a31 + a00*a12*a31 + a01*a10*a32 - a00*a11*a32,
                      a01*a12*a20 - a02*a11*a20 + a02*a10*a21 - a00*a12*a21 - a01*a10*a22 + a00*a11*a22)
        * (1.0f/determinant());
    }
    
    inline float Mat4::determinant() const
    {
        return
        a03 * a12 * a21 * a30 - a02 * a13 * a21 * a30 - a03 * a11 * a22 * a30 + a01 * a13 * a22 * a30 +
        a02 * a11 * a23 * a30 - a01 * a12 * a23 * a30 - a03 * a12 * a20 * a31 + a02 * a13 * a20 * a31 +
        a03 * a10 * a22 * a31 - a00 * a13 * a22 * a31 - a02 * a10 * a23 * a31 + a00 * a12 * a23 * a31 +
        a03 * a11 * a20 * a32 - a01 * a13 * a20 * a32 - a03 * a10 * a21 * a32 + a00 * a13 * a21 * a32 +
        a01 * a10 * a23 * a32 - a00 * a11 * a23 * a32 - a02 * a11 * a20 * a33 + a01 * a12 * a20 * a33 +
        a02 * a10 * a21 * a33 - a00 * a12 * a21 * a33 - a01 * a10 * a22 * a33 + a00 * a11 * a22 * a33;
    }
    
    inline Mat4::operator float*()
    {
        return v;
    }
    
    inline Vec3 Mat4::operator*(const Vec3 & b) const {
        return Vec3(b.x * a00 + b.y * a01 + b.z * a02 + a03,
                    b.x * a10 + b.y * a11 + b.z * a12 + a13,
                    b.x * a20 + b.y * a21 + b.z * a22 + a23);
    }
}

#endif
