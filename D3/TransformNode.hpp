//
//  TransformNode.hpp
//  
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _TransformNode_hpp
#define _TransformNode_hpp

#include "Types.hpp"

namespace d3 {
    class Vec3;
    class Quat;
    
    //! Scene graph node
    class TransformNode {
    public:
        typedef std::list<TransformNode *>::const_iterator subnodeIterator;
        
    public:        
    protected:
        TransformNode * parent_;
        
        Vec3 position_;
        Vec3 scale_;
        Quat orientation_;
        
        Mat4 cached_transform_;
        
        Vec3 derivedPosition_;
        Vec3 derivedScale_;
        Quat derivedOrientation_;
        
        bool needsUpdate_;
        
        String name_;

        std::list<TransformNode *> sub_nodes_;
              
    public:
        //! Creates new named node. To be used internaly!
        TransformNode(String node_name);
        
        //! Deletes all subnodes
        virtual ~TransformNode();

        //! @return Node name
        virtual String getName() const;

        /*! Updates node's transformations
         *  @param cascade If TRUE, update cascades to all subnodes
         */
        void update(bool cascade = false);
        
        //! Creates subnode (registers parent-child relationship)
        TransformNode * createSubnode(String name);
        
        //! Sets parent node
        void setParent(TransformNode * parent);
        
        //! @return Parent node
        TransformNode * getParent() const;
        
        //! Inserts 'node' as subnode
        void addSubnode(TransformNode * node);
        
        //! @return Number of subnodes
        unsigned int numSubnodes() const;
        
        //! @return Subnodes iterator
        subnodeIterator getSubnodeIterator() const;
        
        //! Returns subnode named 'name' or nullptr
        TransformNode * getSubnode(String name) const;
        
        //! Removes subnode by pointer
        void removeSubnode(TransformNode * node);
        
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
        TransformNode * setPosition(Vec3 v);
        
        //! @return Nodes position
        Vec3 getPosition() const;
        
        //! @return Nodes derived position
        Vec3 getDerivedPosition();
        
        //! Sets scaling factor (in all dims)
        TransformNode * setScale(Vec3 k);
        
        //! @return Nodes scale factor
        Vec3 getScale() const;
        
        //! @return Nodes derived scale
        Vec3 getDerivedScale();
        
        //! Rotates by an ange in degrees over axies
        void rotate(Vec3 axis, float angle);
        
        //! Changes orientation
        TransformNode * setOrientation(Quat q);
        
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
