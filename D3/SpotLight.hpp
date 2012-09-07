//
//  SpotLight.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _SpotLight_hpp
#define _SpotLight_hpp

#include "PointLight.hpp"

namespace d3 {
    
    class SpotLight : public PointLight {
    protected:
        float spot_cutoff_;      // 0..90 or 180
        float spot_exponent_;    // 0..128
                
        Vec3 direction_;
        
        Node * target_node_;
        
    public:
        SpotLight();
        
        void setCutoff(int v);
        int getCutoff() const;
        
        void setExponent(int v);
        int getExponent() const;
        
        //! Look at target to follow
        void setTarget(Node *target_node);
        
        //! Sets direction (Note: direction is rotated by orientation)
        void setDirection(Vec3 dir);
        
        //! Gets direction
        Vec3 getDirection();
    };
}

#endif
