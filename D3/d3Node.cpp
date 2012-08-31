//
//  d3Node.cpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Node.hpp"
#include "d3gl.hpp"

namespace d3 {
    
    bool d3Node::Attachment::isAttached() const {
        return parent_node_ != nullptr;
    }
    
    bool d3Node::Attachment::isVisible() const
    {
        return false;
    }
    
    void d3Node::Attachment::setParent(d3Node *parent)
    {
        parent_node_ = parent;
    }
    
    d3Node * d3Node::Attachment::getParent() const
    {
        return parent_node_;
    }
    
    d3Node::d3Node(d3String node_name) : name_(node_name)
    {
        // Setup default value
        position_ = d3Vec3(0.f, 0.f, 0.f);
        orientation_ = d3Quat(0.f, 0.f, 0.f, 1.f);
        scale_ = d3Vec3(1.0f, 1.0f, 1.0f);
        
        attachedObject_ = nullptr;
        
        needsUpdate_ = true;
        
        parent_ = nullptr;
    }
    
    void d3Node::traverse(d3::d3Node::VisitOperation *op)
    {
        // begin this node
        op->beginNode(this);
        
        // travers subnodes
        for (d3Node *node : sub_nodes_) {
            node->traverse(op);
        }
        
        // end this node
        op->endNode(this);
    }

    d3String d3Node::getName() const
    {
        return name_;
    }
    
    void d3Node::update(bool cascade)
    {
        // TODO: cascade
        if (getParent() == nullptr) {
            derivedScale_ = scale_;
            derivedPosition_ = position_;
            derivedOrientation_ = orientation_;
        } else {
            derivedPosition_ = parent_->getDerivedPosition() + position_;
            derivedScale_ = parent_->getDerivedScale().mul(scale_);
            derivedOrientation_ = parent_->getDerivedOrientation() * orientation_; //FIX?
        }
        
        setNeedsUpdate(false);
    }
    
    void d3Node::setAttachedObject(Attachment *obj) {
        attachedObject_ = obj;
        if (obj != nullptr)
            obj->setParent(this);
    }
    
    d3Node::Attachment * d3Node::getAttachedObject() const
    {
        return attachedObject_;
    }
    
    d3Node * d3Node::createSubnode(d3String name, Attachment* object)
    {
        d3Node *subnode = new d3Node(name);
        subnode->setAttachedObject(object);
        addSubnode(subnode);
        return subnode;
    }
    
    d3Node * d3Node::getParent() const
    {
        return parent_;
    }
    
    void d3Node::setParent(d3Node *parent)
    {
        parent_ = parent;
    }
    
    void d3Node::addSubnode(d3Node *node)
    {
        sub_nodes_.push_back(node);
        node->setParent(this);
    }
    
    unsigned int d3Node::numSubnodes() const
    {
        return (unsigned int)sub_nodes_.size();
    }
    
    d3Node::subnodeIterator d3Node::getSubnodeIterator() const
    {
        return sub_nodes_.begin();
    }
    
    d3Node * d3Node::getSubnode(d3String name)
    {
        for (d3Node *n : sub_nodes_)
            if (n->getName() == name)
                return n;
        return nullptr;
    }
    
    void d3Node::removeSubnode(d3Node *node)
    {
        sub_nodes_.remove(node);
        node->setParent(nullptr);
    }
    
    void d3Node::removeSubnode(d3String name)
    {
        d3Node *node = getSubnode(name);
        removeSubnode(node);
    }
    
    bool d3Node::getNeedsUpdate() const
    {
        return needsUpdate_;
    }
    
    void d3Node::setNeedsUpdate(bool needsUpdate)
    {
        needsUpdate_ = needsUpdate;
    }
    
    void d3Node::move(d3Vec3 v)
    {
        position_ = position_ + v;
        setNeedsUpdate();
    }
    
    void d3Node::setPosition(d3Vec3 v)
    {
        position_ = v;
        setNeedsUpdate();
    }
    
    d3Vec3 d3Node::getPosition() const
    {
        return position_;
    }
    
    d3Vec3 d3Node::getDerivedPosition()
    {
        if (getNeedsUpdate())
            update();
        return derivedPosition_;
    }
    
    void d3Node::setScale(d3Vec3 k)
    {
        scale_ = k;
        setNeedsUpdate();
    }
    
    d3Vec3 d3Node::getScale() const
    {
        return scale_;
    }
    
    d3Vec3 d3Node::getDerivedScale()
    {
        if (getNeedsUpdate())
            update();
        return derivedScale_;
    }
    
    void d3Node::rotate(d3Vec3 axis, float angle)
    {
        //TODO
        setNeedsUpdate();
    }
    
    void d3Node::setOrientation(d3Quat q)
    {
        orientation_ = q;
        setNeedsUpdate();
    }
    
    d3Quat d3Node::getOrientation() const
    {
        return orientation_;
    }
    
    d3Quat d3Node::getDerivedOrientation()
    {
        if (getNeedsUpdate())
            update();
        return derivedOrientation_;
    }
    
    d3Vec3 d3Node::convertWorldToLocalPosition(const d3Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            update();
        
        return v - derivedPosition_;
    }
    
    d3Vec3 d3Node::convertLocalToWorldPosition(const d3Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            update();
        
        return v + derivedPosition_;
    }
    
    d3Quat d3Node::convertWorldToLocalOrientation(const d3Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            update();
        
        return v * derivedOrientation_;
    }
    
    d3Quat d3Node::convertLocalToWorldOrientation(const d3Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            update();
        
        return v * derivedOrientation_;
    }
}