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
    class Renderable : public Node::Attachment {
    protected:
        Geometry * geometry_;
        Material * material_;
        Texture * texture_;
        
    public:
        Renderable(Geometry * geometry) : geometry_(geometry), material_(nullptr), texture_(nullptr) {}
                
        SETGET(Geometry *, geometry_, Geometry)
        SETGET(Material *, material_, Material)
        SETGET(Texture *, texture_, Texture)
        
        //! Node::Attachment::isRenderable();
        virtual bool isRenderable() const { return true; }
    };
}

#endif
