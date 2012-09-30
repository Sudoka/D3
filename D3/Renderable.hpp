//
//  Renderable.hpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Renderable_hpp
#define _Renderable_hpp

namespace d3 {
    class Renderable : public SceneNode::Attachment {
    protected:
        shared_ptr<Geometry> geometry_;
        shared_ptr<Material> material_;
        shared_ptr<Texture> texture_;
        
    public:
        Renderable() : geometry_(nullptr), material_(nullptr), texture_(nullptr) {}
        
        Renderable(shared_ptr<Geometry> geometry) : geometry_(geometry), material_(new Material()), texture_(nullptr) {}
        
        virtual ~Renderable() {}
                
        SETGET(shared_ptr<Geometry>, geometry_, Geometry)
        SETGET(shared_ptr<Material>, material_, Material)
        SETGET(shared_ptr<Texture>, texture_, Texture)
    };
}

#endif
