//
//  Modeler.h
//  D3
//
//  Created by Srđan Rašić on 9/7/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__Modeler__
#define __D3__Modeler__

namespace d3 {
    class Modeler {
    protected:
        
    public:
        Modeler();
        
        void start();
        
        void insertPoint(Vec3 point);
        
        Geometry * getGeometry();
    };
}
#endif