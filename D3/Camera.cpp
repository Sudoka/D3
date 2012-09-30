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
        setDirection(Vec3(-1.f, -1.f, -1.f));
        setTarget(nullptr);
        setFovy(60);
        setAspectRatio(4/3.f);
    }
    
    void Camera::setTarget(SceneNode *node) { target_node_ = node; }
    
    void Camera::setAspectRatio(float a) { aspect_ratio_ = a; }
    
    void Camera::setDirection(Vec3 dir) { direction_ = dir; }
    
    Vec3 Camera::getDirection() const { return direction_; }

    void Camera::setFovy(float fovy) { fovy_ = fovy; }
    
    float Camera::getFovy() const { return fovy_; }
    
    void Camera::setUpVector(Vec3 up) { up_vector_ = up; }
    
    Frustum Camera::getFrustum() const
    {
        float near = 1, far = 100, zoom = 1;
        float half_height = near * tan( fovy_ * 0.5 * k2Pi / 360.f );
        float half_width = half_height * aspect_ratio_;
        
        Frustum frustum = {-half_width * zoom, half_width * zoom, -half_height * zoom, half_height * zoom, near, far};
        
        return frustum;
    }
    
    Mat4 Camera::getProjection() const
    {
        return getPerspective(fovy_ * kPiOver180, aspect_ratio_, 0.1, 100);
        
        ///Frustum f = getFrustum();
        
        //return getFrustumMat4(f.left, f.right, f.down, f.up, f.near, f.far);
    }
    
    Mat4 Camera::getTransform() const
    {
        // Look at
        Vec3 eye = getParent()->getDerivedPosition();
        
        Vec3 center;
        
        if (target_node_ != nullptr) {
            center = target_node_->getDerivedPosition();
        } else {
            center = getParent()->getDerivedPosition() + getParent()->getDerivedOrientation() * direction_;
        }
        
        Vec3 forward = eye - center; forward.normalize();
        Vec3 side = up_vector_.cross(forward); side.normalize();
        Vec3 up = forward.cross(side);
        
        Mat4 lookat(side.x, up.x, forward.x, 0,
                    side.y, up.y, forward.y, 0,
                    side.z, up.z, forward.z, 0,
                    (side * -1) * eye, (up * -1) * eye, (forward * -1) * eye, 1.0);
        
        return lookat;
    }
}