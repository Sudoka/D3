//
//  d3Camera.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Camera_hpp
#define D3_d3Camera_hpp

namespace d3 {
    class d3Camera : public d3Node::Attachment {
    protected:
        d3Node *target_node_;
        d3Vec3 direction_;
        d3Vec3 up_vector_;
        
        float fovy_;
        
        float aspect_ratio_;
        
    public:
        d3Camera();
        
        //! Look at target to follow
        void setTarget(d3Node *target_node);
        
        //! Direction (Note: direction is rotated by orientation)
        void setDirection(d3Vec3 dir);
        
        //! @return Direction vector
        d3Vec3 getDirection() const;
        
        //! Sets fovy in degrees
        void setFovy(float fovy);
        
        //! @return fovy in degrees
        float getFovy() const;
        
        void setUpVector(d3Vec3 up);
    
        //! Sets screen size
        void setAspectRatio(float a);
        
        //! @return View frustum
        d3Frustum getFrustum() const;
        
        //! @return Inverse camera transform
        d3Mat4 getTransform() const;
    };
}

#endif
