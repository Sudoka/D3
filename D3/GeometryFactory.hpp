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
    class TexturedMesh;
    
    //! Creates primitive meshes.
    class GeometryFactory {
    private:
        static std::unordered_map<String, shared_ptr<TexturedMesh>> primitive_map;
        
    private:
        static shared_ptr<TexturedMesh> createBoundingBox();
        static shared_ptr<TexturedMesh> createPlane();
        static shared_ptr<TexturedMesh> createBox();
        
    public:
        static shared_ptr<TexturedMesh> getPrimitive(String name);
    };
}
#endif
