//
//  Node.cpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Node.hpp"
#include "OpenGLHeaders.hpp"

namespace d3 {
    
    bool Node::Attachment::isAttached() const {
        return parent_node_ != nullptr;
    }
    
    bool Node::Attachment::isRenderable() const
    {
        return false;
    }
        
    void Node::Attachment::setParent(Node *parent)
    {
        parent_node_ = parent;
    }
    
    Node * Node::Attachment::getParent() const
    {
        return parent_node_;
    }
    
    Node::Node(String node_name) : name_(node_name)
    {
        // Setup default value
        position_ = Vec3(0.f, 0.f, 0.f);
        orientation_ = Quat(0.f, 0.f, 0.f, 1.f);
        scale_ = Vec3(1.0f, 1.0f, 1.0f);
        
        attachedObject_ = nullptr;
        
        needsUpdate_ = true;
        
        parent_ = nullptr;
        
        show_bb_ = false;
        bounding_box_ = Vec3(0.1, 0.1, 0.1);
    }
    
    Node::~Node()
    {
        // Delete subnodes
        for (Node *node : sub_nodes_) {
            delete node;
        }
        
        // Delete attached object
        if (getAttachedObject() != nullptr) {
            delete attachedObject_;
        }
    }
    
    void Node::setBoundingBox(Vec3 box)
    {
        bounding_box_ = box;
    }
    
    Box Node::getBoundingBox(bool derived_position)
    {
        if (derived_position)
            return { getDerivedPosition(), bounding_box_ };
        else
            return { getPosition(), bounding_box_ };
    }
    
    void Node::setBoundingBoxVisibility(bool visible)
    {
        show_bb_ = visible;
    }
    
    bool Node::getBoundingBoxVisibility() const
    {
        return show_bb_;
    }
    
    void Node::traverse(shared_ptr<Node::VisitOperation> op)
    {
        // begin this node
        op->beginNode(this);
        
        // travers subnodes
        for (Node *node : sub_nodes_) {
            node->traverse(op);
        }
        
        // end this node
        op->endNode(this);
    }

    String Node::getName() const
    {
        return name_;
    }
    
    void Node::update(bool cascade)
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
    
    void Node::setAttachedObject(Attachment *obj) {
        attachedObject_ = obj;
        if (obj != nullptr)
            obj->setParent(this);
    }
    
    Node::Attachment * Node::getAttachedObject() const
    {
        return attachedObject_;
    }
    
    Node * Node::createSubnode(String name, Attachment* object)
    {
        Node *subnode = new Node(name);
        subnode->setAttachedObject(object);
        addSubnode(subnode);
        return subnode;
    }
    
    Node * Node::getParent() const
    {
        return parent_;
    }
    
    void Node::setParent(Node *parent)
    {
        parent_ = parent;
    }
    
    void Node::addSubnode(Node *node)
    {
        sub_nodes_.push_back(node);
        node->setParent(this);
    }
    
    unsigned int Node::numSubnodes() const
    {
        return (unsigned int)sub_nodes_.size();
    }
    
    Node::subnodeIterator Node::getSubnodeIterator() const
    {
        return sub_nodes_.begin();
    }
    
    Node * Node::getSubnode(String name)
    {
        for (Node *n : sub_nodes_)
            if (n->getName() == name)
                return n;
        return nullptr;
    }
    
    void Node::removeSubnode(Node *node)
    {
        sub_nodes_.remove(node);
        node->setParent(nullptr);
    }
    
    void Node::removeSubnode(String name)
    {
        Node *node = getSubnode(name);
        removeSubnode(node);
    }
    
    bool Node::getNeedsUpdate() const
    {
        return needsUpdate_;
    }
    
    void Node::setNeedsUpdate(bool needsUpdate)
    {
        needsUpdate_ = needsUpdate;
        for (Node *n : sub_nodes_)
            n->setNeedsUpdate();
    }
    
    void Node::move(Vec3 v)
    {
        position_ = position_ + v;
        setNeedsUpdate();
    }
    
    Node * Node::setPosition(Vec3 v)
    {
        position_ = v;
        setNeedsUpdate();
        return this;
    }
    
    Vec3 Node::getPosition() const
    {
        return position_;
    }
    
    Vec3 Node::getDerivedPosition()
    {
        if (getNeedsUpdate())
            update();
        return derivedPosition_;
    }
    
    Node * Node::setScale(Vec3 k)
    {
        scale_ = k;
        setNeedsUpdate();
        return this;
    }
    
    Vec3 Node::getScale() const
    {
        return scale_;
    }
    
    Vec3 Node::getDerivedScale()
    {
        if (getNeedsUpdate())
            update();
        return derivedScale_;
    }
    
    void Node::rotate(Vec3 axis, float angle)
    {
        orientation_ = orientation_ * Quat(axis, angle);
        setNeedsUpdate();
    }
    
    Node * Node::setOrientation(Quat q)
    {
        orientation_ = q;
        setNeedsUpdate();
        return this;
    }
    
    Quat Node::getOrientation() const
    {
        return orientation_;
    }
    
    Quat Node::getDerivedOrientation()
    {
        if (getNeedsUpdate())
            update();
        return derivedOrientation_;
    }
    
    Vec3 Node::convertWorldToLocalPosition(const Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            update();
        
        return v - derivedPosition_;
    }
    
    Vec3 Node::convertLocalToWorldPosition(const Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            update();
        
        return v + derivedPosition_;
    }
    
    Quat Node::convertWorldToLocalOrientation(const Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            update();
        
        return v * derivedOrientation_;
    }
    
    Quat Node::convertLocalToWorldOrientation(const Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            update();
        
        return v * derivedOrientation_;
    }
}