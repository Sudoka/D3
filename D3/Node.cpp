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
    Node::Node(String node_name) : name_(node_name)
    {
        // Setup default value
        position_ = Vec3(0.f, 0.f, 0.f);
        orientation_ = Quat(0.f, 0.f, 0.f, 1.f);
        scale_ = Vec3(1.0f, 1.0f, 1.0f);
        
        needsUpdate_ = true;
        listener = nullptr;
        parent_ = nullptr;
    }
    
    Node::~Node()
    {       
        // Delete subnodes
        for (Node * node : sub_nodes_) {
            delete node;
        }
    }

    String Node::getName() const
    {
        return name_;
    }
    
    void Node::setListener(Listener * listener) {
        this->listener = listener;
    }
    
    Node::Listener * Node::getListener() const
    {
        return this->listener;
    }
    
    void Node::recache()
    {
        if (getParent() == nullptr) {
            cached_transform_ = (getTranslationMat4(position_) * getScalingMat4(scale_)) * orientation_;
            
            derivedScale_ = scale_;
            derivedPosition_ = position_;
            derivedOrientation_ = orientation_;
        } else {
            cached_transform_ = getParent()->getCachedTransformRef() * ((getTranslationMat4(position_) * getScalingMat4(scale_)) * orientation_);
            
            derivedPosition_ = cached_transform_  * position_;
            derivedScale_ = parent_->getDerivedScale().mul(scale_);
            derivedOrientation_ = parent_->getDerivedOrientation() * orientation_; //FIX?
        }
        
        setNeedsUpdate(false);
        
        // Notify listeners
        if (listener)
            listener->onRecache(this);
    }
    
    Node * Node::createSubnode(String name)
    {
        Node * subnode = new Node(name);
        addSubnode(subnode);
        return subnode;
    }
    
    Node * Node::getParent() const
    {
        return parent_;
    }
    
    void Node::setParent(Node * parent)
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
    
    Node & Node::getSubnode(String name) const
    {
        Node * subnode = nullptr;
        for (Node *n : sub_nodes_)
            if (n->getName() == name) {
                subnode = n;
                break;
            }
        assert(subnode);
        return * subnode;
    }
    
    void Node::removeSubnode(Node * node)
    {
        sub_nodes_.remove(node);
        node->setParent(nullptr);
    }
    
    void Node::removeSubnode(String name)
    {
        Node * node = &getSubnode(name);
        removeSubnode(node);
    }
    
    void Node::deleteSubnodes()
    {
        for (Node *n : sub_nodes_)
            delete n;
        sub_nodes_.clear();
    }
    
    bool Node::getNeedsUpdate() const
    {
        return needsUpdate_;
    }
    
    void Node::setNeedsUpdate(bool needsUpdate)
    {
        needsUpdate_ = needsUpdate;
        
        if (needsUpdate == true) {  // FIX: slow
            for (Node *n : sub_nodes_)
                n->setNeedsUpdate();
        }
    }
    
    Mat4 & Node::getCachedTransformRef()
    {
        if (getNeedsUpdate())
            recache();
        return cached_transform_;
    }
    
    void Node::move(Vec3 v)
    {
        position_ = position_ + v;
        setNeedsUpdate();
    }
    
    Node & Node::setPosition(Vec3 v)
    {
        position_ = v;
        setNeedsUpdate();
        return * this;
    }
    
    Vec3 Node::getPosition() const
    {
        return position_;
    }
    
    Vec3 Node::getDerivedPosition()
    {
        if (getNeedsUpdate())
            recache();
        return derivedPosition_;
    }
    
    Node & Node::setScale(Vec3 k)
    {
        scale_ = k;
        setNeedsUpdate();
        return * this;
    }
    
    Vec3 Node::getScale() const
    {
        return scale_;
    }
    
    Vec3 Node::getDerivedScale()
    {
        if (getNeedsUpdate())
            recache();
        return derivedScale_;
    }
    
    void Node::rotate(Vec3 axis, float angle)
    {
        orientation_ = orientation_ * Quat(axis, angle);
        setNeedsUpdate();
    }
    
    Node & Node::setOrientation(Quat q)
    {
        orientation_ = q;
        setNeedsUpdate();
        return * this;
    }
    
    Quat Node::getOrientation() const
    {
        return orientation_;
    }
    
    Quat Node::getDerivedOrientation()
    {
        if (getNeedsUpdate())
            recache();
        return derivedOrientation_;
    }
    
    Vec3 Node::convertWorldToLocalPosition(const Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            recache();
        
        return cached_transform_.inverse() * position_;
    }
    
    Vec3 Node::convertLocalToWorldPosition(const Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            recache();
        
        return cached_transform_ * position_;
    }
    
    Quat Node::convertWorldToLocalOrientation(const Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            recache();
        
        return v * derivedOrientation_;
    }
    
    Quat Node::convertLocalToWorldOrientation(const Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            recache();
        
        return v * derivedOrientation_;
    }
}