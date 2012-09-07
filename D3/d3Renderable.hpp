//
//  d3Renderable.hpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Renderable_hpp
#define D3_d3Renderable_hpp

namespace d3 {
    class d3Renderable : public d3Node::Attachment {
    protected:
        d3Geometry * geometry_;
        d3Material * material_;
        d3Texture * texture_;
        
    public:
        d3Renderable(d3Geometry * geometry) : geometry_(geometry), material_(nullptr), texture_(nullptr) {}
                
        SETGET(d3Geometry *, geometry_, Geometry)
        SETGET(d3Material *, material_, Material)
        SETGET(d3Texture *, texture_, Texture)
        
        //! d3Node::Attachment::isRenderable();
        virtual bool isRenderable() const { return true; }
    };
}

#endif
