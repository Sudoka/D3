//
//  d3Node.hpp
//  D3
//
//  Created by Srđan Rašić on 8/12/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Node_hpp
#define D3_d3Node_hpp

#include "d3Types.hpp"

namespace d3 {
    class d3Vec3;
    class d3Quat;
    class d3RenderOperation;
    class d3StateOperation;
    
    //! Scene graph node
    class d3Node {
    public:
        typedef std::list<d3Node*>::const_iterator subnodeIterator;
        
    public:
        //! Is performed on each node while traversing graph
        class VisitOperation {
        public:
            virtual void beginNode(d3Node *node) {};
            virtual void endNode(d3Node *node) {};
        };
        
        //! Represents attachable object
        class Attachment {
        protected:
            d3Node *parent_node_;
            
        public:           
            //! Should override if object is renderable
            virtual bool isVisible() const;
            
            virtual d3RenderOperation * getRenderOperation() { return nullptr; }
            virtual d3StateOperation * getStateOperation() { return nullptr; }
            
            bool isAttached() const;
            
            void setParent(d3Node *parent);
            d3Node * getParent() const;
        };
        
    protected:
        d3Node *parent_;
        
        d3Vec3 position_;
        d3Vec3 scale_;
        d3Quat orientation_;
        
        d3Vec3 derivedPosition_;
        d3Vec3 derivedScale_;
        d3Quat derivedOrientation_;
        
        bool needsUpdate_;
        
        d3String name_;

        std::list<d3Node*> sub_nodes_;
        
        Attachment *attachedObject_;
              
    public:
        //! Creates new named node. To be used internaly.
        d3Node(d3String node_name);
        
        //! Traverse node and subnodes.
        virtual void traverse(VisitOperation *op);

        //! @return Node name
        d3String getName() const;
        
        /*! Updates node's transformations
         *  @param cascade If TRUE, update cascades to all subnodes
         */
        void update(bool cascade = false);
        
        //! Attaches movable object
        void setAttachedObject(Attachment *obj);
        
        //! @return Attached object
        Attachment * getAttachedObject() const;
        
        //! Creates subnode (registers parent-child relationship)
        d3Node * createSubnode(d3String name, Attachment* object = nullptr);
        
        //! Sets parent node
        void setParent(d3Node *parent);
        
        //! @return Parent node
        d3Node * getParent() const;
        
        //! Inserts 'node' as subnode
        void addSubnode(d3Node *node);
        
        //! @return Number of subnodes
        unsigned int numSubnodes() const;
        
        //! @return Subnodes iterator
        subnodeIterator getSubnodeIterator() const;
        
        //! Returns subnode named 'name' or nullptr
        d3Node * getSubnode(d3String name);
        
        //! Removes subnode by pointer
        void removeSubnode(d3Node *node);
        
        //! Removes subnode by name
        void removeSubnode(d3String name);
        
        //! @return True if node's transformation changed
        bool getNeedsUpdate() const;
        
        //! Set if transformations changed
        void setNeedsUpdate(bool needsUpdate = true);
        
        //! Changes position by offset v
        void move(d3Vec3 v);
        
        //! Changes position
        void setPosition(d3Vec3 v);
        
        //! @return Nodes position
        d3Vec3 getPosition() const;
        
        //! @return Nodes derived position
        d3Vec3 getDerivedPosition();
        
        //! Sets scaling factor (in all dims)
        void setScale(d3Vec3 k);
        
        //! @return Nodes scale factor
        d3Vec3 getScale() const;
        
        //! @return Nodes derived scale
        d3Vec3 getDerivedScale();
        
        //! Rotates by an ange in degrees over axies
        void rotate(d3Vec3 axis, float angle);
        
        //! Changes orientation
        void setOrientation(d3Quat q);
        
        //! @return Nodes orientation
        d3Quat getOrientation() const;
        
        //! @return Nodes derived orientation
        d3Quat getDerivedOrientation();
        
        //! Converts world to local position
        d3Vec3 convertWorldToLocalPosition(const d3Vec3 &v);
        
        //! Converts local to world position
        d3Vec3 convertLocalToWorldPosition(const d3Vec3 &v);
        
        //! Converts world to local orientation
        d3Quat convertWorldToLocalOrientation(const d3Quat &v);
        
        //! Converts local to world orientation
        d3Quat convertLocalToWorldOrientation(const d3Quat &v);
    };
}

#endif
