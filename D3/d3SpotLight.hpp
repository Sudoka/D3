//
//  d3SpotLight.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3SpotLight_hpp
#define D3_d3SpotLight_hpp

#include "d3PointLight.hpp"

namespace d3 {
    
    class d3SpotLight : public d3PointLight {
    protected:
        float spot_cutoff_;      // 0..90 or 180
        float spot_exponent_;    // 0..128
                
        d3Vec3 direction_;
        
        d3Node * target_node_;
        
    public:
        d3SpotLight();
        
        void setCutoff(int v);
        int getCutoff() const;
        
        void setExponent(int v);
        int getExponent() const;
        
        //! Look at target to follow
        void setTarget(d3Node *target_node);
        
        //! Sets direction (Note: direction is rotated by orientation)
        void setDirection(d3Vec3 dir);
        
        //! Gets direction
        d3Vec3 getDirection();
    };
}

#endif
