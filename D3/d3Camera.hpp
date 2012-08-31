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
        d3Vec3 look_at_;
        d3Vec3 up_vector_;
        
        float fovy_;
        
        float screen_width_;
        float screen_height_;
        
    public:
        d3Camera();
        
        //! Look at target to follow
        void setTarget(d3Node *target_node);
        
        //! Look at vector (used if no 'target' is set)
        void setLookAt(d3Vec3 look_at);
        
        //! Sets fovy in degrees
        void setFovy(float fovy);
        
        //! @return fovy in degrees
        float getFovy() const;
    
        //! Sets screen size
        void setScreenSize(float x, float y);
        
        //! Apply to GL context
        void apply();
    };
}

#endif
