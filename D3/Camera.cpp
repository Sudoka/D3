//
//  Camera.cpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Camera.hpp"
#include <iostream>

namespace d3 {
    Camera::Camera()
    {
        // Setup default values
        setUpVector(Vec3(0.f, 1.f, 0.f));
        setDirection(Vec3(0.f, 0.f, -1.f));
        setTarget(nullptr);
        setFovy(60);
    }
    
    void Camera::setTarget(Node *node) { target_node_ = node; }
    
    void Camera::setAspectRatio(float a) { aspect_ratio_ = a; }
    
    void Camera::setDirection(Vec3 dir) { direction_ = dir; }
    
    Vec3 Camera::getDirection() const { return direction_; }

    void Camera::setFovy(float fovy) { fovy_ = fovy; }
    
    float Camera::getFovy() const { return fovy_; }
    
    void Camera::setUpVector(Vec3 up) { up_vector_ = up; }
    
    Frustum Camera::getFrustum() const
    {
        float near = 0.1, far = 200, zoom = 1;
        float half_height = near * tan( fovy_ * 0.5 * k2Pi / 360.f );
        float half_width = half_height * aspect_ratio_;
        
        Frustum frustum = {-half_width * zoom, half_width * zoom, -half_height * zoom, half_height * zoom, near, far};
        
        return frustum;
    }
    
    Mat4 Camera::getTransform() const
    {
        // Look at
        Vec3 position = getParent()->getDerivedPosition();
        
        Vec3 look_at;
        
        if (target_node_ != nullptr) {
            look_at = target_node_->getDerivedPosition();
        } else {
            look_at = getParent()->getPosition() + getParent()->getOrientation() * direction_;
        }
        
        Vec3 forward = look_at - position; forward.normalize();
        Vec3 side = forward.cross(up_vector_); side.normalize();
        Vec3 up = side.cross(forward);
        
        Mat4 matrix(side.x, side.y, side.z, 0,
                      up.x, up.y, up.z, 0,
                      -forward.x, -forward.y, -forward.z, 0,
                      0, 0, 0, 1
                      );
        
        Mat4 translate_back = getTranslationMatrix(getParent()->getPosition() * -1.0);
        
        return (matrix * translate_back).transpose();    // GL uses column-major
    }
}