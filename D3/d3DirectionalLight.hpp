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
        
    public:
        
        //! Gets direction
        d3Vec3 getDirection();
        
        //! d3StateOperation: applies state
        void apply();
    };
}

#endif
