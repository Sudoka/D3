//
//  SceneNode.h
//  D3
//
//  Created by Srđan Rašić on 9/28/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__SceneNode__
#define __D3__SceneNode__

#include "Types.hpp"

namespace d3 {
    class TexturedGeometry;
    class PointLight;
    class BillboardParticleEmitter;
    
    //! Scene graph node
    class SceneNode : public TransformNode {
    public:
        //! Is performed on each node while traversing graph
        class VisitOperation {
        public:
            virtual void beginNode(SceneNode * node) {}
            virtual void endNode(SceneNode * node) {}
        };
        
        //! Represents attachable object
        class Attachment {
        protected:
            SceneNode * parent_node_;
            
        public:
            virtual ~Attachment() {}
            
            bool isAttached() const;
            
            void setParent(SceneNode * parent);
            SceneNode * getParent() const;
        };
        
        //! Listens for actions on Node object
        class Listener {
        public:
            virtual ~Listener() {}
            
            //! Called upon collision
            virtual void onCollision(SceneNode * node) {}
        };
        
        //! Use to store arbitrary data in Node
        class UserData {
        public:
            virtual ~UserData() {}
        };
        
    protected:
        Scene * scene_;
        
        shared_ptr<Attachment> attachedObject_;
        
        Listener * listener_;
        
        Vec3 bounding_box_;
        bool show_bb_;
        
        UserData * user_data_;
        
    public:
        //! Creates new named node. To be used internaly!
        SceneNode(String node_name, Scene * scene);
        
        //! Deletes all subnodes
        virtual ~SceneNode();
        
        SceneNode * createSubnode(String name);
        SceneNode * createSubnode(String name, shared_ptr<Attachment> attachment);
        SceneNode * createSubnode(String name, shared_ptr<Camera> camera);
        SceneNode * createSubnode(String name, shared_ptr<TexturedGeometry> renderable);
        SceneNode * createSubnode(String name, shared_ptr<PointLight> light_source);
        SceneNode * createSubnode(String name, shared_ptr<BillboardParticleEmitter> emitter);
        
        SceneNode * getSubnode(String name) const;
        
        //! Traverse node and subnodes.
        virtual void traverse(shared_ptr<VisitOperation> op);
        
        //! @return Scene manager
        Scene * getScene() const;
        
        //! Manage listener
        SETGET(Listener *, listener_, Listener)
        
        //! Manage User Data
        SETGET(UserData *, user_data_, UserData)
        
        //! Attaches movable object
        void setAttachedObject(shared_ptr<Attachment> obj);
        
        //! @return Attached object
        shared_ptr<Attachment> getAttachedObject() const;
        shared_ptr<BillboardParticleEmitter> getAttachedEmitter() const;
        
        //! Sets bounding box
        void setBoundingBox(Vec3 box);
        
        //! @return Bounding box
        Box getBoundingBox(bool derived_position = false);
        
        //! Pass TRUE to show bounding box
        void setBoundingBoxVisibility(bool visible);
        
        //! @return TRUE is BB is to be shown, FALSE otherwise
        bool getBoundingBoxVisibility() const;
        
    };
}


#endif