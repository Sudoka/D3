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
#include "Vec4.hpp"
#include "Mat3.hpp"

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
            float m[16];
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
        operator const float*() const;
        
        //operator float*();
        
        //! Convert to mat3
        operator Mat3();
        
        Vec3 operator*(const Vec3& b) const;
        
        Vec4 operator*(const Vec4& b) const;
    };
    
#pragma mark Implementation
    inline Mat4::Mat4()
    {
        m[0] = 1;
        m[4] = 0;
        m[8] = 0;
        m[12] = 0;
        m[1]= 0;
        m[5] = 1;
        m[9] = 0;
        m[13] = 0;
        m[2] = 0;
        m[6] = 0;
        m[10] = 1;
        m[14] = 0;
        m[3] = 0;
        m[7] = 0;
        m[11] = 0;
        m[15] = 1;
    }
    
    inline Mat4::Mat4(float a00, float a01, float a02, float a03,
                      float a10, float a11, float a12, float a13,
                      float a20, float a21, float a22, float a23,
                      float a30, float a31, float a32, float a33)
    {
        m[0] = a00;
        m[1] = a01;
        m[2] = a02;
        m[3] = a03;
        m[4] = a10;
        m[5] = a11;
        m[6] = a12;
        m[7] = a13;
        m[8] = a20;
        m[9] = a21;
        m[10] = a22;
        m[11] = a23;
        m[12] = a30;
        m[13] = a31;
        m[14] = a32;
        m[15] = a33;
    }
    
    inline bool Mat4::operator==(const Mat4& b) const
    {
        return  !( *this != b );
    }
    
    inline bool Mat4::operator!=(const Mat4& b) const
    {
        return
        m[0] != b.m[0] || m[4] != b.m[4] || m[8] != b.m[8] || m[12] != b.m[12] ||
        m[1] != b.m[1] || m[5] != b.m[5] || m[9] != b.m[9] || m[13] != b.m[13] ||
        m[2] != b.m[2] || m[6] != b.m[6] || m[10] != b.m[10] || m[14] != b.m[14] ||
        m[3] != b.m[3] || m[7] != b.m[7] || m[11] != b.m[11] || m[15] != b.m[15];
    }
    
    inline Mat4 Mat4::operator+(const Mat4& b) const
    {
        return Mat4(m[0] + b.m[0], m[4] + b.m[4], m[8] + b.m[8], m[12] + b.m[12],
                      m[1] + b.m[1], m[5] + b.m[5], m[9] + b.m[9], m[13] + b.m[13],
                      m[2] + b.m[2], m[6] + b.m[6], m[10] + b.m[10], m[14] + b.m[14],
                      m[3] + b.m[3], m[7] + b.m[7], m[11] + b.m[11], m[15] + b.m[15]);
    }
    
    inline Mat4 Mat4::operator-(const Mat4& b) const
    {
        return Mat4(m[0] - b.m[0], m[4] - b.m[4], m[8] - b.m[8], m[12] - b.m[12],
                      m[1] - b.m[1], m[5] - b.m[5], m[9] - b.m[9], m[13] - b.m[13],
                      m[2] - b.m[2], m[6] - b.m[6], m[10] - b.m[10], m[14] - b.m[14],
                      m[3] - b.m[3], m[7] - b.m[7], m[11] - b.m[11], m[15] - b.m[15]);
    }
    
    inline Mat4 Mat4::operator*(const Mat4& b) const
    {
        Mat4 result;
        
        result.m[0]  = m[0] * b.m[0]  + m[4] * b.m[1]  + m[8] * b.m[2]   + m[12] * b.m[3];
        result.m[4]  = m[0] * b.m[4]  + m[4] * b.m[5]  + m[8] * b.m[6]   + m[12] * b.m[7];
        result.m[8]  = m[0] * b.m[8]  + m[4] * b.m[9]  + m[8] * b.m[10]  + m[12] * b.m[11];
        result.m[12] = m[0] * b.m[12] + m[4] * b.m[13] + m[8] * b.m[14]  + m[12] * b.m[15];
        
        result.m[1]  = m[1] * b.m[0]  + m[5] * b.m[1]  + m[9] * b.m[2]   + m[13] * b.m[3];
        result.m[5]  = m[1] * b.m[4]  + m[5] * b.m[5]  + m[9] * b.m[6]   + m[13] * b.m[7];
        result.m[9]  = m[1] * b.m[8]  + m[5] * b.m[9]  + m[9] * b.m[10]  + m[13] * b.m[11];
        result.m[13] = m[1] * b.m[12] + m[5] * b.m[13] + m[9] * b.m[14]  + m[13] * b.m[15];
        
        result.m[2]  = m[2] * b.m[0]  + m[6] * b.m[1]  + m[10] * b.m[2]  + m[14] * b.m[3];
        result.m[6]  = m[2] * b.m[4]  + m[6] * b.m[5]  + m[10] * b.m[6]  + m[14] * b.m[7];
        result.m[10] = m[2] * b.m[8]  + m[6] * b.m[9]  + m[10] * b.m[10] + m[14] * b.m[11];
        result.m[14] = m[2] * b.m[12] + m[6] * b.m[13] + m[10] * b.m[14] + m[14] * b.m[15];
        
        result.m[3]  = m[3] * b.m[0]  + m[7] * b.m[1]  + m[11] * b.m[2]  + m[15] * b.m[3];
        result.m[7]  = m[3] * b.m[4]  + m[7] * b.m[5]  + m[11] * b.m[6]  + m[15] * b.m[7];
        result.m[11] = m[3] * b.m[8]  + m[7] * b.m[9]  + m[11] * b.m[10] + m[15] * b.m[11];
        result.m[15] = m[3] * b.m[12] + m[7] * b.m[13] + m[11] * b.m[14] + m[15] * b.m[15];
        
        return result;
    }
    
    inline Mat4 Mat4::operator*(float f) const
    {
        return Mat4(m[0] * f, m[4] * f, m[8] * f, m[12] * f,
                      m[1] * f, m[5] * f, m[9] * f, m[13] * f,
                      m[2] * f, m[6] * f, m[10] * f, m[14] * f,
                      m[3] * f, m[7] * f, m[11] * f, m[15] * f);
    }
    
    inline Mat4 Mat4::transpose() const
    {
        return Mat4(m[0], m[4], m[8], m[12],
                      m[1], m[5], m[9], m[13],
                      m[2], m[6], m[10], m[14],
                      m[3], m[7], m[11], m[15]);
    }
    
    inline Mat4 Mat4::inverse() const
    {
        Mat4 result;
        
        float det = determinant();
        
        result.m[0] = (m[9]*m[14]*m[7] - m[13]*m[10]*m[7] + m[13]*m[6]*m[11] - m[5]*m[14]*m[11] - m[9]*m[6]*m[15] + m[5]*m[10]*m[15]) / det;
        result.m[4] = (m[12]*m[10]*m[7] - m[8]*m[14]*m[7] - m[12]*m[6]*m[11] + m[4]*m[14]*m[11] + m[8]*m[6]*m[15] - m[4]*m[10]*m[15]) / det;
        result.m[8] = (m[8]*m[13]*m[7] - m[12]*m[9]*m[7] + m[12]*m[5]*m[11] - m[4]*m[13]*m[11] - m[8]*m[5]*m[15] + m[4]*m[9]*m[15]) / det;
        result.m[12] = (m[12]*m[9]*m[6] - m[8]*m[13]*m[6] - m[12]*m[5]*m[10] + m[4]*m[13]*m[10] + m[8]*m[5]*m[14] - m[4]*m[9]*m[14]) / det;
        result.m[1] = (m[13]*m[10]*m[3] - m[9]*m[14]*m[3] - m[13]*m[2]*m[11] + m[1]*m[14]*m[11] + m[9]*m[2]*m[15] - m[1]*m[10]*m[15]) / det;
        result.m[5] = (m[8]*m[14]*m[3] - m[12]*m[10]*m[3] + m[12]*m[2]*m[11] - m[0]*m[14]*m[11] - m[8]*m[2]*m[15] + m[0]*m[10]*m[15]) / det;
        result.m[9] = (m[12]*m[9]*m[3] - m[8]*m[13]*m[3] - m[12]*m[1]*m[11] + m[0]*m[13]*m[11] + m[8]*m[1]*m[15] - m[0]*m[9]*m[15]) / det;
        result.m[13] = (m[8]*m[13]*m[2] - m[12]*m[9]*m[2] + m[12]*m[1]*m[10] - m[0]*m[13]*m[10] - m[8]*m[1]*m[14] + m[0]*m[9]*m[14]) / det;
        result.m[2] = (m[5]*m[14]*m[3] - m[13]*m[6]*m[3] + m[13]*m[2]*m[7] - m[1]*m[14]*m[7] - m[5]*m[2]*m[15] + m[1]*m[6]*m[15]) / det;
        result.m[6] = (m[12]*m[6]*m[3] - m[4]*m[14]*m[3] - m[12]*m[2]*m[7] + m[0]*m[14]*m[7] + m[4]*m[2]*m[15] - m[0]*m[6]*m[15]) / det;
        result.m[10] = (m[4]*m[13]*m[3] - m[12]*m[5]*m[3] + m[12]*m[1]*m[7] - m[0]*m[13]*m[7] - m[4]*m[1]*m[15] + m[0]*m[5]*m[15]) / det;
        result.m[14] = (m[12]*m[5]*m[2] - m[4]*m[13]*m[2] - m[12]*m[1]*m[6] + m[0]*m[13]*m[6] + m[4]*m[1]*m[14] - m[0]*m[5]*m[14]) / det;
        result.m[3] = (m[9]*m[6]*m[3] - m[5]*m[10]*m[3] - m[9]*m[2]*m[7] + m[1]*m[10]*m[7] + m[5]*m[2]*m[11] - m[1]*m[6]*m[11]) / det;
        result.m[7] = (m[4]*m[10]*m[3] - m[8]*m[6]*m[3] + m[8]*m[2]*m[7] - m[0]*m[10]*m[7] - m[4]*m[2]*m[11] + m[0]*m[6]*m[11]) / det;
        result.m[11] = (m[8]*m[5]*m[3] - m[4]*m[9]*m[3] - m[8]*m[1]*m[7] + m[0]*m[9]*m[7] + m[4]*m[1]*m[11] - m[0]*m[5]*m[11]) / det;
        result.m[15] = (m[4]*m[9]*m[2] - m[8]*m[5]*m[2] + m[8]*m[1]*m[6] - m[0]*m[9]*m[6] - m[4]*m[1]*m[10] + m[0]*m[5]*m[10]) / det;
        
        return result;
    }
    
    inline float Mat4::determinant() const
    {
        return
        m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] - m[12] * m[5] * m[10] * m[3] + m[4] * m[13] * m[10] * m[3] +
        m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] - m[12] * m[9] * m[2] * m[7] + m[8] * m[13] * m[2] * m[7] +
        m[12] * m[1] * m[10] * m[7] - m[0] * m[13] * m[10] * m[7] - m[8] * m[1] * m[14] * m[7] + m[0] * m[9] * m[14] * m[7] +
        m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] - m[12] * m[1] * m[6] * m[11] + m[0] * m[13] * m[6] * m[11] +
        m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] - m[8] * m[5] * m[2] * m[15] + m[4] * m[9] * m[2] * m[15] +
        m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] - m[4] * m[1] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
    }
    
    inline Mat4::operator const float*() const
    {
        return (const float*)m;
    }
    
//    inline Mat4::operator float*()
//    {
//        return m;
//    }
    
    inline Mat4::operator Mat3()
    {
        return Mat3(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
    }
    
    inline Vec3 Mat4::operator*(const Vec3 & b) const {
        return Vec3(b.x * m[0] + b.y * m[4] + b.z * m[8] + m[12],
                    b.x * m[1] + b.y * m[5] + b.z * m[9] + m[13],
                    b.x * m[2] + b.y * m[6] + b.z * m[10] + m[14]);
    }
    
    inline Vec4 Mat4::operator*(const Vec4 & b) const {
        return Vec4(b.x * m[0] + b.y * m[4] + b.z * m[8] + b.w * m[12],
                    b.x * m[1] + b.y * m[5] + b.z * m[9] + b.w * m[13],
                    b.x * m[2] + b.y * m[6] + b.z * m[10] + b.w * m[14],
                    b.x * m[3] + b.y * m[7] + b.z * m[11] + b.w * m[15]);
    }
}

#endif
