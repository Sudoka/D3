//
//  d3Scene.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Scene_hpp
#define D3_d3Scene_hpp

namespace d3 {
   
#pragma mark Interface
    class d3Camera;
    class d3Node;
    
    //! Scene.
    class d3Scene {
        d3Node *root_node_;
        d3Camera *camera_;
        
    public:
        d3Scene();
        
        //! @return Scene camera
        d3Camera * getCamera() const;
        
        //! @return Root node
        d3Node * getRootNode() const;
    };
}

#endif
