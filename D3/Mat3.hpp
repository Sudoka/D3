//
//  Mat3.hpp
//  
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Mat3_hpp
#define _Mat3_hpp

namespace d3 {
    
#pragma mark Interface
    class Mat3 {
    public:
        union {
            struct {
                float a00, a01, a02;
                float a10, a11, a12;
                float a20, a21, a22;
            };
            float m[9];
        } __attribute__((aligned(16)));
        
    public:
        /*! Default constructor.
         *  Creates identity matrix.
         */
        Mat3();
        
        Mat3(float a00, float a01, float a02,
             float a10, float a11, float a12,
             float a20, float a21, float a22);
        
        bool operator==(const Mat3& b) const;
        bool operator!=(const Mat3& b) const;
        
        //! Component-wise addition.
        Mat3 operator+(const Mat3& b) const;
        
        //! Component-wise subtraction.
        Mat3 operator-(const Mat3& b) const;
        
        //! Matrix multiplication.
        Mat3 operator*(const Mat3& b) const;
        
        //! Scalar multiplication.
        Mat3 operator*(float f) const;
        
        //! Matrix transpose.
        Mat3 transpose() const;
        
        //! Matrix inverse.
        Mat3 inverse() const;
        
        //! Matrix determinant.
        float determinant() const;
        
        //! Convert to const float*.
        operator const float*() const;
        
        operator float*();
    };
    
#pragma marko Implementation
    inline Mat3::Mat3()
    :
    a00(1.f), a01(0.f), a02(0.f),
    a10(0.f), a11(1.f), a12(0.f),
    a20(0.f), a21(0.f), a22(1.f)
    {
    }
    
    inline Mat3::Mat3(float a00, float a01, float a02,
                      float a10, float a11, float a12,
                      float a20, float a21, float a22)
    {
        m[0] = a00;
        m[1] = a01;
        m[2] = a02;
        m[3] = a10;
        m[4] = a11;
        m[5] = a12;
        m[6] = a20;
        m[7] = a21;
        m[8] = a22;
    }
    
    inline bool Mat3::operator==(const Mat3& b) const
    {
        return  !( *this != b );
    }
    
    inline bool Mat3::operator!=(const Mat3& b) const
    {
        return
        a00 != b.a00 || a01 != b.a01 || a02 != b.a02 ||
        a10 != b.a10 || a11 != b.a11 || a12 != b.a12 ||
        a20 != b.a20 || a21 != b.a21 || a22 != b.a22;
    }
    
    inline Mat3 Mat3::operator+(const Mat3& b) const
    {
        return Mat3(a00 + b.a00, a01 + b.a01, a02 + b.a02,
                      a10 + b.a10, a11 + b.a11, a12 + b.a12,
                      a20 + b.a20, a21 + b.a21, a22 + b.a22);
    }
    
    inline Mat3 Mat3::operator-(const Mat3& b) const
    {
        return Mat3(a00 - b.a00, a01 - b.a01, a02 - b.a02,
                      a10 - b.a10, a11 - b.a11, a12 - b.a12,
                      a20 - b.a20, a21 - b.a21, a22 - b.a22);
    }
    
    inline Mat3 Mat3::operator*(const Mat3& b) const
    {
        Mat3 result;
        
        result.m[0] = m[0] * b.m[0] + m[3] * b.m[1] + m[6] * b.m[2];
        result.m[3] = m[0] * b.m[3] + m[3] * b.m[4] + m[6] * b.m[5];
        result.m[6] = m[0] * b.m[6] + m[3] * b.m[7] + m[6] * b.m[8];
        
        result.m[1] = m[1] * b.m[0] + m[4] * b.m[1] + m[7] * b.m[2];
        result.m[4] = m[1] * b.m[3] + m[4] * b.m[4] + m[7] * b.m[5];
        result.m[7] = m[1] * b.m[6] + m[4] * b.m[7] + m[7] * b.m[8];
        
        result.m[2] = m[2] * b.m[0] + m[5] * b.m[1] + m[8] * b.m[2];
        result.m[5] = m[2] * b.m[3] + m[5] * b.m[4] + m[8] * b.m[5];
        result.m[8] = m[2] * b.m[6] + m[5] * b.m[7] + m[8] * b.m[8];
        
        return result;
    }
    
    inline Mat3 Mat3::operator*(float f) const
    {
        return Mat3(a00 * f, a01 * f, a02 * f,
                      a10 * f, a11 * f, a12 * f,
                      a20 * f, a21 * f, a22 * f);
    }
    
    inline Mat3 Mat3::transpose() const
    {
        return Mat3(a00, a10, a20,
                      a01, a11, a21,
                      a02, a12, a22);
    }
    
    inline Mat3 Mat3::inverse() const
    {
        Mat3 result;
        
        float det = 1.0f / determinant();
        
        result.m[0] = (a11 * a22 - a12 * a21) * det;
        result.m[1] = (a02 * a21 - a01 * a22) * det;
        result.m[2] = (a01 * a12 - a02 * a11) * det;
        result.m[3] = (a12 * a20 - a10 * a22) * det;
        result.m[4] = (a00 * a22 - a02 * a20) * det;
        result.m[5] = (a02 * a10 - a00 * a12) * det;
        result.m[6] = (a10 * a21 - a11 * a20) * det;
        result.m[7] = (a20 * a01 - a00 * a21) * det;
        result.m[8] = (a00 * a11 - a01 * a10) * det;
        
        return result;
    }
    
    inline float Mat3::determinant() const
    {
        return
        a00 * a11 * a22 +
        a01 * a12 * a20 +
        a02 * a10 * a21 -
        a02 * a11 * a20 -
        a01 * a10 * a22 -
        a00 * a12 * a21;
    }
    
    inline Mat3::operator float*()
    {
        return m;
    }
    
    inline Mat3::operator const float*() const
    {
        return (const float*)m;
    }
    
}

#endif
