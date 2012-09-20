//
//  Node.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Node_hpp
#define _Node_hpp

#include "Types.hpp"

namespace d3 {
    class Vec3;
    class Quat;
    class RenderOperation;
    class StateOperation;
    
    //! Scene graph node
    class Node {
    public:
        typedef std::list<Node*>::const_iterator subnodeIterator;
        
    public:
        //! Is performed on each node while traversing graph
        class VisitOperation {
        public:
            virtual void beginNode(Node *node) {}
            virtual void endNode(Node *node) {}
        };
        
        //! Represents attachable object
        class Attachment {
        protected:
            Node *parent_node_;
            
        public:
            virtual ~Attachment() {}
            
            //! Should override if object is renderable
            virtual bool isRenderable() const;
            
            bool isAttached() const;
            
            void setParent(Node *parent);
            Node * getParent() const;
        };
        
        //! Listens for actions on Node object
        class Listener {
        public:
            virtual ~Listener() {}
            
            //! Called upon collision
            virtual void onCollision(Node * node) {}
        };
        
        //! Use to store arbitrary data in Node
        class UserData {
        public:
            virtual ~UserData() {}
        };
        
    protected:
        Scene * scene_;
        Node * parent_;
        
        Vec3 position_;
        Vec3 scale_;
        Quat orientation_;
        
        Mat4 cached_transform_;
        
        Vec3 derivedPosition_;
        Vec3 derivedScale_;
        Quat derivedOrientation_;
        
        bool needsUpdate_;
        
        String name_;

        std::list<Node*> sub_nodes_;
        
        Attachment * attachedObject_;
        
        Listener * listener_;
        
        Vec3 bounding_box_;
        bool show_bb_;
        
        UserData * user_data_;
              
    public:
        //! Creates new named node. To be used internaly!
        Node(String node_name, Scene * scene);
        
        //! Deletes all subnodes
        ~Node();
        
        //! Traverse node and subnodes.
        virtual void traverse(shared_ptr<VisitOperation> op);

        //! @return Node name
        String getName() const;
        
        //! @return Scene manager
        Scene * getScene() const;
        
        /*! Updates node's transformations
         *  @param cascade If TRUE, update cascades to all subnodes
         */
        void update(bool cascade = false);
        
        //! Manage listener
        SETGET(Listener *, listener_, Listener)
        
        //! Manage User Data
        SETGET(UserData *, user_data_, UserData)
        
        //! Attaches movable object
        void setAttachedObject(Attachment *obj);
        
        //! @return Attached object
        Attachment * getAttachedObject() const;
        
        //! Sets bounding box
        void setBoundingBox(Vec3 box);
        
        //! @return Bounding box
        Box getBoundingBox(bool derived_position = false);
        
        //! Pass TRUE to show bounding box
        void setBoundingBoxVisibility(bool visible);
        
        //! @return TRUE is BB is to be shown, FALSE otherwise
        bool getBoundingBoxVisibility() const;
        
        //! Creates subnode (registers parent-child relationship)
        Node * createSubnode(String name, Attachment* object = nullptr);
        
        //! Sets parent node
        void setParent(Node *parent);
        
        //! @return Parent node
        Node * getParent() const;
        
        //! Inserts 'node' as subnode
        void addSubnode(Node *node);
        
        //! @return Number of subnodes
        unsigned int numSubnodes() const;
        
        //! @return Subnodes iterator
        subnodeIterator getSubnodeIterator() const;
        
        //! Returns subnode named 'name' or nullptr
        Node * getSubnode(String name);
        
        //! Removes subnode by pointer
        void removeSubnode(Node *node);
        
        //! Removes subnode by name
        void removeSubnode(String name);
        
        //! Deletes all subnodes
        void deleteSubnodes();
        
        //! @return True if node's transformation changed
        bool getNeedsUpdate() const;
        
        //! Set if transformations changed
        void setNeedsUpdate(bool needsUpdate = true);
        
        //! @return Derived transform matrix
        Mat4 & getCachedTransformRef();
        
        //! Changes position by offset v
        void move(Vec3 v);
        
        //! Changes position
        Node * setPosition(Vec3 v);
        
        //! @return Nodes position
        Vec3 getPosition() const;
        
        //! @return Nodes derived position
        Vec3 getDerivedPosition();
        
        //! Sets scaling factor (in all dims)
        Node * setScale(Vec3 k);
        
        //! @return Nodes scale factor
        Vec3 getScale() const;
        
        //! @return Nodes derived scale
        Vec3 getDerivedScale();
        
        //! Rotates by an ange in degrees over axies
        void rotate(Vec3 axis, float angle);
        
        //! Changes orientation
        Node * setOrientation(Quat q);
        
        //! @return Nodes orientation
        Quat getOrientation() const;
        
        //! @return Nodes derived orientation
        Quat getDerivedOrientation();
        
        //! Converts world to local position
        Vec3 convertWorldToLocalPosition(const Vec3 &v);
        
        //! Converts local to world position
        Vec3 convertLocalToWorldPosition(const Vec3 &v);
        
        //! Converts world to local orientation
        Quat convertWorldToLocalOrientation(const Quat &v);
        
        //! Converts local to world orientation
        Quat convertLocalToWorldOrientation(const Quat &v);
    };
}

#endif
