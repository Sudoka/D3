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
    
    //! Transformation node
    class Node {
    public:
        typedef std::list<Node *>::const_iterator subnodeIterator;
        
        //! Listens for actions on Node object
        class Listener {
        public:
            virtual ~Listener() {}
            
            //! Called upon collision
            virtual void onCollision(SceneNode * node) {}
            
            //! Called after recaching
            virtual void onRecache(Node * node) {}
        };
              
    public:
        //! Creates new named node. To be used internaly!
        Node(String node_name);
        
        //! Deletes all subnodes
        virtual ~Node();

        //! @return Node name
        virtual String getName() const;
        
        //! Attaches movable object
        void setListener(Listener * listener);
        
        //! @return Attached object
        Listener * getListener() const;
        
        //! Creates subnode (registers parent-child relationship)
        Node * createSubnode(String name);
        
        //! Sets parent node
        void setParent(Node * parent);
        
        //! @return Parent node
        Node * getParent() const;
        
        //! Inserts 'node' as subnode
        void addSubnode(Node * node);
        
        //! @return Number of subnodes
        unsigned int numSubnodes() const;
        
        //! @return Subnodes iterator
        subnodeIterator getSubnodeIterator() const;
        
        //! Returns subnode named 'name' or nullptr
        Node & getSubnode(String name) const;
        
        //! Removes subnode by pointer
        void removeSubnode(Node * node);
        
        //! Removes subnode by name
        void removeSubnode(String name);
        
        //! Deletes all subnodes
        virtual void deleteSubnodes();
        
        //! @return True if node's transformation changed
        bool getNeedsUpdate() const;
        
        //! Set if transformations changed
        void setNeedsUpdate(bool needsUpdate = true);
        
        //! @return Derived transform matrix
        Mat4 & getCachedTransformRef();
        
        //! Changes position by offset v
        void move(Vec3 v);
        
        //! Changes position
        virtual Node & setPosition(Vec3 v);
        
        //! @return Nodes position
        Vec3 getPosition() const;
        
        //! @return Nodes derived position
        Vec3 getDerivedPosition();
        
        //! Sets scaling factor (in all dims)
        Node & setScale(Vec3 k);
        
        //! @return Nodes scale factor
        Vec3 getScale() const;
        
        //! @return Nodes derived scale
        Vec3 getDerivedScale();
        
        //! Rotates by an ange in degrees over axies
        void rotate(Vec3 axis, float angle);
        
        //! Changes orientation
        Node & setOrientation(Quat q);
        
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
        
    protected:
        //! Updates node's transformations
        void recache();
        
    protected:
        String name_;
        Listener * listener;
        Node * parent_;
        
        Vec3 position_;
        Vec3 scale_;
        Quat orientation_;
        
        Mat4 cached_transform_;
        
        Vec3 derivedPosition_;
        Vec3 derivedScale_;
        Quat derivedOrientation_;
        
        bool needsUpdate_;
        
        std::list<Node *> sub_nodes_;
    };
}

#endif
