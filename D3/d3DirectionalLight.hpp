//
//  d3DirectionalLight.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3DirectionalLight_hpp
#define D3_d3DirectionalLight_hpp

#include "d3PointLight.hpp"

namespace d3 {
    class d3Vec4;
    
#pragma mark Interface
    //! Direction is inherited through nodes orientation.
    class d3DirectionalLight : public d3PointLight {
    protected:
        d3Vec3 direction_;
        
    public:
        d3DirectionalLight();
        
        //! Sets direction (Note: direction is rotated by orientation)
        void setDirection(d3Vec3 dir);
        
        //! Gets direction
        d3Vec3 getDirection();
    };
}

#endif
