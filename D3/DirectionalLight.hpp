//
//  DirectionalLight.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _DirectionalLight_hpp
#define _DirectionalLight_hpp

#include "PointLight.hpp"

namespace d3 {
    class Vec4;
    
#pragma mark Interface
    //! Direction is inherited through nodes orientation.
    class DirectionalLight : public PointLight {
    protected:
        Vec3 direction_;
        
    public:
        DirectionalLight();
        
        //! Sets direction (Note: direction is rotated by orientation)
        void setDirection(Vec3 dir);
        
        //! Gets direction
        Vec3 getDirection();
    };
}

#endif
