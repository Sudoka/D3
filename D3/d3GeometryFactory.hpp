//
//  d3GeometryFactory.hpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__d3GeometryFactory__
#define __D3__d3GeometryFactory__

namespace d3 {
    class d3GeometryFactory {
    public:
        static d3Geometry * createPlane();
        static d3Geometry * createBox();
        static d3Geometry * createCylinder();
        static d3Geometry * createAxes();
    };
}
#endif
