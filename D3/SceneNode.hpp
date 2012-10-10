//
//  SceneNode.hpp
//  D3
//
//  Created by Srđan Rašić on 9/28/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__SceneNode__
#define __D3__SceneNode__

#include "Types.hpp"

namespace d3 {
    class Renderable;
    class TexturedGeometry;
    class PointLight;
    class BillboardParticleEmitter;
    
    //! Scene graph node
    class SceneNode : public Node {
    public:
        //! Is performed on each node while traversing graph
        class VisitOperation {
        public:
            virtual void beginNode(SceneNode * node) {}
            virtual void endNode(SceneNode * node) {}
        };
        
        //! Use to store arbitrary data in Node
        class UserData {
        public:
            virtual ~UserData() {}
        };
        
    public:
        //! Creates new named node. To be used internaly!
        SceneNode(String node_name, Scene & scene);
        
        //! Deletes all subnodes
        virtual ~SceneNode();
        
        //! Creates and returns new subnode
        SceneNode & createSubnode(String name);
        
        //! @return Subnode named name or nullptr
        SceneNode & getSubnode(String name) const;
        
        //! Traverse node and subnodes.
        virtual void traverse(shared_ptr<VisitOperation> op);
        
        //! @return Scene manager
        Scene & getScene() const;
        
        //! Attaches renderable
        void setUserData(UserData * user_data);
        
        //! @return Attached Renderable or nullptr
        UserData * getUserData() const;
        
        //! Sets bounding box
        void setBoundingBox(Vec3 box);
        
        //! @return Bounding box
        Box getBoundingBox(bool derived_position = false);
        
        //! Pass TRUE to show bounding box
        void setBoundingBoxVisibility(bool visible);
        
        //! @return TRUE is BB is to be shown, FALSE otherwise
        bool getBoundingBoxVisibility() const;
        
    protected:
        Scene & scene;
        Vec3 bounding_box;
        bool show_bb;
        UserData * user_data;
    };
}


#endif