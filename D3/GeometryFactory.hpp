//
//  GeometryFactory.hpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GeometryFactory__
#define ____GeometryFactory__

namespace d3 {
    class GeometryFactory {
    public:
        static Geometry * createPlane();
        static Geometry * createBox();
        static Geometry * createCylinder();
        static Geometry * createAxes();
        static Geometry * createArrow(Vec3);
    };
}
#endif
