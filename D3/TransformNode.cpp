//
//  TransformNode.cpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "TransformNode.hpp"
#include "OpenGLHeaders.hpp"

namespace d3 {
    TransformNode::TransformNode(String node_name) : name_(node_name)
    {
        // Setup default value
        position_ = Vec3(0.f, 0.f, 0.f);
        orientation_ = Quat(0.f, 0.f, 0.f, 1.f);
        scale_ = Vec3(1.0f, 1.0f, 1.0f);
        
        needsUpdate_ = true;
        
        parent_ = nullptr;
    }
    
    TransformNode::~TransformNode()
    {       
        // Delete subnodes
        for (TransformNode * node : sub_nodes_) {
            delete node;
        }
    }

    String TransformNode::getName() const
    {
        return name_;
    }
    
    void TransformNode::update(bool cascade)
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
    }
    
    TransformNode * TransformNode::createSubnode(String name)
    {
        TransformNode * subnode = new TransformNode(name);
        addSubnode(subnode);
        return subnode;
    }
    
    TransformNode * TransformNode::getParent() const
    {
        return parent_;
    }
    
    void TransformNode::setParent(TransformNode * parent)
    {
        parent_ = parent;
    }
    
    void TransformNode::addSubnode(TransformNode *node)
    {
        sub_nodes_.push_back(node);
        node->setParent(this);
    }
    
    unsigned int TransformNode::numSubnodes() const
    {
        return (unsigned int)sub_nodes_.size();
    }
    
    TransformNode::subnodeIterator TransformNode::getSubnodeIterator() const
    {
        return sub_nodes_.begin();
    }
    
    TransformNode * TransformNode::getSubnode(String name) const
    {
        for (TransformNode *n : sub_nodes_)
            if (n->getName() == name)
                return n;
        return nullptr;
    }
    
    void TransformNode::removeSubnode(TransformNode * node)
    {
        sub_nodes_.remove(node);
        node->setParent(nullptr);
    }
    
    void TransformNode::removeSubnode(String name)
    {
        TransformNode *node = getSubnode(name);
        removeSubnode(node);
    }
    
    void TransformNode::deleteSubnodes()
    {
        for (TransformNode *n : sub_nodes_)
            delete n;
        sub_nodes_.clear();
    }
    
    bool TransformNode::getNeedsUpdate() const
    {
        return needsUpdate_;
    }
    
    void TransformNode::setNeedsUpdate(bool needsUpdate)
    {
        needsUpdate_ = needsUpdate;
        
        if (needsUpdate == true) {  // FIX: slow
            for (TransformNode *n : sub_nodes_)
                n->setNeedsUpdate();
        }
    }
    
    Mat4 & TransformNode::getCachedTransformRef()
    {
        if (getNeedsUpdate())
            update();
        return cached_transform_;
    }
    
    void TransformNode::move(Vec3 v)
    {
        position_ = position_ + v;
        setNeedsUpdate();
    }
    
    TransformNode * TransformNode::setPosition(Vec3 v)
    {
        position_ = v;
        setNeedsUpdate();
        return this;
    }
    
    Vec3 TransformNode::getPosition() const
    {
        return position_;
    }
    
    Vec3 TransformNode::getDerivedPosition()
    {
        if (getNeedsUpdate())
            update();
        return derivedPosition_;
    }
    
    TransformNode * TransformNode::setScale(Vec3 k)
    {
        scale_ = k;
        setNeedsUpdate();
        return this;
    }
    
    Vec3 TransformNode::getScale() const
    {
        return scale_;
    }
    
    Vec3 TransformNode::getDerivedScale()
    {
        if (getNeedsUpdate())
            update();
        return derivedScale_;
    }
    
    void TransformNode::rotate(Vec3 axis, float angle)
    {
        orientation_ = orientation_ * Quat(axis, angle);
        setNeedsUpdate();
    }
    
    TransformNode * TransformNode::setOrientation(Quat q)
    {
        orientation_ = q;
        setNeedsUpdate();
        return this;
    }
    
    Quat TransformNode::getOrientation() const
    {
        return orientation_;
    }
    
    Quat TransformNode::getDerivedOrientation()
    {
        if (getNeedsUpdate())
            update();
        return derivedOrientation_;
    }
    
    Vec3 TransformNode::convertWorldToLocalPosition(const Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            update();
        
        return cached_transform_.inverse() * position_;
    }
    
    Vec3 TransformNode::convertLocalToWorldPosition(const Vec3 &v)
    {
        //FIX?
        if (needsUpdate_)
            update();
        
        return cached_transform_ * position_;
    }
    
    Quat TransformNode::convertWorldToLocalOrientation(const Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            update();
        
        return v * derivedOrientation_;
    }
    
    Quat TransformNode::convertLocalToWorldOrientation(const Quat &v)
    {
        //FIX!
        if (needsUpdate_)
            update();
        
        return v * derivedOrientation_;
    }
}