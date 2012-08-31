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
        up_vector_ = d3Vec3(0.f, 1.f, 0.f);
        target_node_ = nullptr;
        
        fovy_ = 45;
    }
    
    void d3Camera::setTarget(d3Node *node)
    {
        target_node_ = node;
    }
    
    void d3Camera::setScreenSize(float x, float y)
    {
        screen_width_ = x;
        screen_height_ = y;
    }
    
    void d3Camera::setLookAt(d3Vec3 look_at)
    {
        look_at_ = look_at;
    }
    
    void d3Camera::setFovy(float fovy)
    {
        fovy_ = fovy;
    }
    
    float d3Camera::getFovy() const
    {
        return fovy_;
    }
    
    void d3Camera::apply()
    {
        glViewport(0, 0, screen_width_, screen_height_);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        float near = 1.5, far = 200;
        GLdouble half_height = near * tan( fovy_ * 0.5 * k2Pi / 360.f );
        GLdouble half_width = half_height * ( screen_width_ / screen_height_);
        
        float zoom = 1;
        
        glFrustum(-half_width*zoom, half_width*zoom, -half_height*zoom, half_height*zoom, near, far);
                
        // Look at
        d3Vec3 position = getParent()->getDerivedPosition();
        
        if (target_node_ != nullptr) {
            look_at_ = target_node_->getDerivedPosition();
        }
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        d3Vec3 forward = look_at_ - position; forward.normalize();
        d3Vec3 side = forward.cross(up_vector_); side.normalize();
        d3Vec3 up = side.cross(forward);
        
        d3Mat4 matrix(side.x, side.y, side.z, 0,
                      up.x, up.y, up.z, 0,
                      -forward.x, -forward.y, -forward.z, 0,
                      0, 0, 0, 1
                      );
        matrix = matrix.transpose();    // GL uses column-major
        
        glMultMatrixf(matrix);
        glTranslatef(-position.x, -position.y, -position.z);
    }
}