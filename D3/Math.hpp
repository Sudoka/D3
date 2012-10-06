//
//  math.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _math_hpp
#define _math_hpp

#include <ostream>
#include <cmath>
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"

namespace d3 {
    class Mat3;
    class Mat4;
    class Quat;
    
    // Commonly used constants
    const float kPi = 3.14159265f;
    const float k2Pi = 2.0f * kPi;
    const float kPiOver2 = kPi / 2.0f;
    const float kPiOver180 = kPi / 180.0f;
    const float k1OverPi = 1.0f / kPi;
    const float k1Over2Pi = 1.0f / k2Pi;
    
    //! Wraps an angle in range -pi,pi
    float wrapPi(float theta);
    
    //! Same as acos(x) but if x is out of range, it is clamped
    //! to the nearest valid value.
    float safeAcos(float x);
    
    struct Frustum {
        float left, right;
        float down, up;
        float near, far;
    };
    
    //! Origin is assumed to be in the center of volume
    struct Box {
        Vec3 origin;
        Vec3 size;
    };
    
    float clamp(float min, float max, float value);
    
    //! Axis-aligned bounding box test
    bool aabbTest(Box b1, Box b2);
    
    //! Transform matrices
    Mat4 getTranslationMat4(Vec3 v);
    
    Mat4 getScalingMat4(Vec3 v);
    
    Mat4 getRotationMat4(Vec3 axis, float angle);
    
    Mat4 getPerspective(float fovy, float aspect, float zNear, float zFar);
    
    Mat4 getFrustumMat4(float left, float right, float bottom, float top, float zNear, float zFar);
    
    //Mat3 getRotationMatrix(Vec3 axis, float angle);
    
    Vec3 lerp(Vec3 v0, Vec3 v1, float t);
    
    //! Linear Quaternion interpolation
    Quat lerp(Quat q0, Quat q1, float t);
    
    //! Spherical Quaternion interpolation
    Quat slerp(Quat q0, Quat q1, float t);
    
    float randf();
    
    float randf(float min, float max);
    
    Vec3 randv3(float min, float max);
    
    Vec4 randv4(float min, float max);
    
    int randi(int min, int max);
    
    float absf(float a);
    
    /*! Convert Vec4 to 8-bit vector 4.
     *  Valid component range [0.0, 1.0]
     */
    inline int to8BitVec4(Vec4 v) {
        int f = 0;
        f = (((int)(v.a * 255.0) << 24) & 0xFF000000) | (((int)(v.z * 255.0) << 16) & 0x00FF0000) | (((int)(v.y * 255.0) << 8) & 0x0000FF00) | (((int)(v.x * 255.0) << 0) & 0x000000FF);
        return f;
    }
    
    // ostream
    inline std::ostream& operator<< (std::ostream& os, const Vec3& v) {
        os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    }
    
    inline std::ostream& operator<< (std::ostream& os, const Vec4& v) {
        os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
        return os;
    }
    
    inline std::ostream& operator<< (std::ostream& os, const Mat3& m) {
        os << "|" << m.a00 << ", " << m.a01 << ", " << m.a02 << "|" << std::endl;
        os << "|" << m.a10 << ", " << m.a11 << ", " << m.a12 << "|" << std::endl;
        os << "|" << m.a20 << ", " << m.a21 << ", " << m.a22 << "|" << std::endl;
        return os;
    }
    
    inline std::ostream& operator<< (std::ostream& os, const Mat4& m) {
        os << "|" << m.a00 << ", " << m.a01 << ", " << m.a02 << ", " << m.a03 << "|" << std::endl;
        os << "|" << m.a10 << ", " << m.a11 << ", " << m.a12 << ", " << m.a13 << "|" << std::endl;
        os << "|" << m.a20 << ", " << m.a21 << ", " << m.a22 << ", " << m.a23 << "|" << std::endl;
        os << "|" << m.a30 << ", " << m.a31 << ", " << m.a32 << ", " << m.a33 << "|" << std::endl;
        return os;
    }
    
    
#pragma mark Implementation
    inline float clamp(float min, float max, float value) {
        return (value < min) ? min : ( value > max ? max : value );
    }
    
    inline float wrapPi(float theta) {
        theta += kPi;
        theta -= floor(theta * k1Over2Pi) * k2Pi;
        theta -= kPi;
        return theta;
    }
    
    inline float safeAcos(float x) {
        if (x <= -1.0f) {
            return kPi;
        } else if (x >= 1.0f) {
            return 0.0f;
        }
        
        return acosf(x);
    }
    
    inline float randf() {
        return (float)(rand() % 65000) / 65000.0;
    }
    
    inline float randf(float min, float max) {
        return randf() * (max - min) + min;
    }
    
    inline Vec3 randv3(float min, float max) {
        return Vec3(randf(-1, 1), randf(-1, 1), randf(-1, 1));
    }
    
    inline Vec4 randv4(float min, float max) {
        return Vec4(randf(-1, 1), randf(-1, 1), randf(-1, 1), randf(-1, 1));
    }
    
    inline int randi(int min, int max) {
        return rand() % (-min + max) + min; // fix?
    }
    
    inline float absf(float a) {
        return a < 0 ? -a : a;
    }
}

#endif
