//
//  Math.cpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Math.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"

namespace d3 {
    Mat4 getTranslationMatrix(Vec3 v) {
        Mat4 m;
        m.a03 = v.x;
        m.a13 = v.y;
        m.a23 = v.z;
        
        return m;
    }
}