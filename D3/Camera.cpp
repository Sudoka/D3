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
    Camera::Camera(SceneNode & mover) : Movable(mover)
    {
        // Setup default values
        setUpVector(Vec3(0.f, 1.f, 0.f));
        setDirection(Vec3(-1.f, -1.f, -1.f));
        setTarget(nullptr);
        setFovy(60);
        setAspectRatio(4/3.f);
        
        // register as listener
        getMover().setListener(this);
    }
    
    void Camera::onRecache(Node * node)
    {
        transform_dirty = true;
    }
    
    void Camera::setTarget(SceneNode *node)
    {
        target_node_ = node;
        transform_dirty = true;
    }
    
    void Camera::setAspectRatio(float a)
    {
        aspect_ratio_ = a;
        projection_dirty = true;
    }
    
    void Camera::setDirection(Vec3 dir)
    {
        direction_ = dir;
        transform_dirty = true;
    }
    
    Vec3 Camera::getDirection() const
    {
        return direction_;
    }

    void Camera::setFovy(float fovy)
    {
        fovy_ = fovy;
        projection_dirty = true;
    }
    
    float Camera::getFovy() const
    {
        return fovy_;
    }
    
    void Camera::setUpVector(Vec3 up)
    { up_vector_ = up; }
    
    //! @return Projection matrix
    Mat4 Camera::getProjection()
    {
        // Recalcuate if not cached already
        if (projection_dirty) {
            projection_cache = getPerspective(fovy_ * kPiOver180, aspect_ratio_, 0.1, 100);
            projection_dirty = false;
        }
        
        return projection_cache;
    }
    
    //! @return Inverse camera transform
    Mat4 Camera::getTransform()
    {
        // Recalcuate if not cached already
        if (transform_dirty) {
            Vec3 eye = getMover().getDerivedPosition();
            
            Vec3 center;
            if (target_node_ != nullptr)
                center = target_node_->getDerivedPosition();
            else
                center = getMover().getDerivedPosition() + getMover().getDerivedOrientation() * direction_;
            
            Vec3 forward = eye - center; forward.normalize();
            Vec3 side = up_vector_.cross(forward); side.normalize();
            Vec3 up = forward.cross(side);
            
            transform_cache = Mat4(side.x, up.x, forward.x, 0,
                                   side.y, up.y, forward.y, 0,
                                   side.z, up.z, forward.z, 0,
                                   (side * -1) * eye, (up * -1) * eye, (forward * -1) * eye, 1.0);
            
            transform_dirty = false;
        }
        
        return transform_cache;
    }
}