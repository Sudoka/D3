//
//  TexturedGeometry.hpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _TexturedGeometry_hpp
#define _TexturedGeometry_hpp

namespace d3 {
    class TexturedGeometry : public SceneNode::Attachment {
    protected:
        shared_ptr<Geometry> geometry_;
        shared_ptr<Material> material_;
        shared_ptr<Texture> texture_;
        
    public:
        TexturedGeometry() : geometry_(nullptr), material_(nullptr), texture_(nullptr) {}
        
        TexturedGeometry(shared_ptr<Geometry> geometry) : geometry_(geometry), material_(new Material()), texture_(nullptr) {}
        
        virtual ~TexturedGeometry() {}
                
        SETGET(shared_ptr<Geometry>, geometry_, Geometry)
        SETGET(shared_ptr<Material>, material_, Material)
        SETGET(shared_ptr<Texture>, texture_, Texture)
    };
}

#endif
