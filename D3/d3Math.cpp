//
//  d3Math.cpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Math.hpp"
#include "d3Mat4.hpp"
#include "d3Vec3.hpp"

namespace d3 {
    d3Mat4 getTranslationMatrix(d3Vec3 v) {
        d3Mat4 m;
        m.a03 = v.x;
        m.a13 = v.y;
        m.a23 = v.z;
        
        return m;
    }
}