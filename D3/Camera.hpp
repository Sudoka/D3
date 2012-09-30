//
//  Camera.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Camera_hpp
#define _Camera_hpp

namespace d3 {
    class Camera : public SceneNode::Attachment {
    protected:
        SceneNode * target_node_;
        Vec3 direction_;
        Vec3 up_vector_;
        
        float fovy_;
        
        float aspect_ratio_;
        
    public:
        Camera();
        
        //! Look at target to follow
        void setTarget(SceneNode *target_node);
        
        //! Direction (Note: direction is rotated by orientation)
        void setDirection(Vec3 dir);
        
        //! @return Direction vector
        Vec3 getDirection() const;
        
        //! Sets fovy in degrees
        void setFovy(float fovy);
        
        //! @return fovy in degrees
        float getFovy() const;
        
        void setUpVector(Vec3 up);
    
        //! Sets screen size
        void setAspectRatio(float a);
        
        //! @return View frustum
        Frustum getFrustum() const;
        
        //! @return Projection matrix
        Mat4 getProjection() const; //FIX: slow
        
        //! @return Inverse camera transform
        Mat4 getTransform() const; //FIX: slow
    };
}

#endif
