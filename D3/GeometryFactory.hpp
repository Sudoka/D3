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
        static shared_ptr<Geometry> createPlane();
        static shared_ptr<Geometry> createBox();
        static shared_ptr<Geometry> createCylinder();
        static shared_ptr<Geometry> createAxes();
        static shared_ptr<Geometry> createArrow(Vec3);
    };
}
#endif
