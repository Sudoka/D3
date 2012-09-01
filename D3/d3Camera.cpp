//
//  d3Camera.cpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Camera.hpp"
#include <iostream>
#include <GLUT/glut.h>

namespace d3 {
    d3Camera::d3Camera()
    {
        // Setup default values
        setUpVector(d3Vec3(0.f, 1.f, 0.f));
        setDirection(d3Vec3(0.f, 0.f, -1.f));
        setTarget(nullptr);
        setFovy(60);
    }
    
    void d3Camera::setTarget(d3Node *node) { target_node_ = node; }
    
    void d3Camera::setAspectRatio(float a) { aspect_ratio_ = a; }
    
    void d3Camera::setDirection(d3Vec3 dir) { direction_ = dir; }
    
    d3Vec3 d3Camera::getDirection() const { return direction_; }

    void d3Camera::setFovy(float fovy) { fovy_ = fovy; }
    
    float d3Camera::getFovy() const { return fovy_; }
    
    void d3Camera::setUpVector(d3Vec3 up) { up_vector_ = up; }
    
    d3Frustum d3Camera::getFrustum() const
    {
        float near = 0.1, far = 200, zoom = 1;
        float half_height = near * tan( fovy_ * 0.5 * k2Pi / 360.f );
        float half_width = half_height * aspect_ratio_;
        
        d3Frustum frustum = {-half_width * zoom, half_width * zoom, -half_height * zoom, half_height * zoom, near, far};
        
        return frustum;
    }
    
    d3Mat4 d3Camera::getTransform() const
    {
        // Look at
        d3Vec3 position = getParent()->getDerivedPosition();
        
        d3Vec3 look_at;
        
        if (target_node_ != nullptr) {
            look_at = target_node_->getDerivedPosition();
        } else {
            look_at = getParent()->getPosition() + getParent()->getOrientation() * direction_;
        }
        
        d3Vec3 forward = look_at - position; forward.normalize();
        d3Vec3 side = forward.cross(up_vector_); side.normalize();
        d3Vec3 up = side.cross(forward);
        
        d3Mat4 matrix(side.x, side.y, side.z, 0,
                      up.x, up.y, up.z, 0,
                      -forward.x, -forward.y, -forward.z, 0,
                      0, 0, 0, 1
                      );
        
        d3Mat4 translate_back = getTranslationMatrix(getParent()->getPosition() * -1.0);
        
        return (matrix * translate_back).transpose();    // GL uses column-major
    }
}