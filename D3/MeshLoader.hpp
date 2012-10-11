//
//  MeshLoader.hpp
//  D3
//
//  Created by Srđan Rašić on 10/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_MeshLoader_hpp
#define D3_MeshLoader_hpp

namespace d3 {
    class MeshLoader {
    public:
        static shared_ptr<TexturedMesh> loadOBJ(String path);
    };
}

#endif
