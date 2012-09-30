//
//  SceneNode.cpp
//  D3
//
//  Created by Srđan Rašić on 9/28/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SceneNode.hpp"


namespace d3 {
    
    bool SceneNode::Attachment::isAttached() const {
        return parent_node_ != nullptr;
    }
    
    void SceneNode::Attachment::setParent(SceneNode *parent)
    {
        parent_node_ = parent;
    }
    
    SceneNode * SceneNode::Attachment::getParent() const
    {
        return parent_node_;
    }
    
    SceneNode::SceneNode(String node_name, Scene * scene) : TransformNode(node_name), scene_(scene)
    {       
        attachedObject_ = nullptr;
        
        show_bb_ = false;
        bounding_box_ = Vec3(1, 1, 1);
        
        listener_ = nullptr;
        user_data_ = nullptr;
        DEBUG_PRINT("New node " << node_name)
    }
    
    SceneNode::~SceneNode()
    {
        getScene()->getRenderablesRef().erase(this);
        getScene()->getEmittersRef().erase(this);

        DEBUG_PRINT_2(name_)
        TransformNode::~TransformNode();
    }
    
    SceneNode * SceneNode::createSubnode(String name)
    {
        SceneNode * node = new SceneNode(name, getScene());
        node->setAttachedObject(nullptr);
        addSubnode(node);
        return node;
    }
    
    SceneNode * SceneNode::createSubnode(String name, shared_ptr<Attachment> attachment)
    {
        SceneNode * node = new SceneNode(name, getScene());
        node->setAttachedObject(attachment);
        addSubnode(node);
        return node;
    }
    
    SceneNode * SceneNode::createSubnode(String name, shared_ptr<Camera> camera)
    {
        DEBUG_PRINT_2("New camera node named " << name)
        SceneNode * node = createSubnode(name, (shared_ptr<Attachment>)camera);
        return node;
    }
    
    SceneNode * SceneNode::createSubnode(String name, shared_ptr<Renderable> renderable)
    {
        DEBUG_PRINT_2("New renderable node named " << name)
        SceneNode * node = createSubnode(name, (shared_ptr<Attachment>)renderable);
        getScene()->getRenderablesRef().insert(node);
        return node;
    }
    
    SceneNode * SceneNode::createSubnode(String name, shared_ptr<PointLight> light_source)
    {
        DEBUG_PRINT_2("New light source node named " << name)
        SceneNode * node = createSubnode(name, (shared_ptr<Attachment>)light_source);
        getScene()->getLightSourcesRef().insert(node);
        return node;
    }
    
    SceneNode * SceneNode::createSubnode(String name, shared_ptr<BillboardParticleEmitter> emitter)
    {
        DEBUG_PRINT_2("New emitter node named " << name)
        SceneNode * node = createSubnode(name, (shared_ptr<Attachment>)emitter);
        getScene()->getEmittersRef().insert(node);
        return node;
    }
    
    SceneNode * SceneNode::getSubnode(String name) const
    {
        return (SceneNode *)TransformNode::getSubnode(name);
    }
    
    void SceneNode::traverse(shared_ptr<SceneNode::VisitOperation> op)
    {
        // begin this node
        op->beginNode(this);
        
        // travers subnodes
        for (TransformNode * node : sub_nodes_) {
            ((SceneNode*)node)->traverse(op);
        }
        
        // end this node
        op->endNode(this);
    }
    
    void SceneNode::setBoundingBox(Vec3 box)
    {
        bounding_box_ = box;
    }
    
    Box SceneNode::getBoundingBox(bool derived_position)
    {
        if (derived_position)
            return { getDerivedPosition(), bounding_box_ };
        else
            return { getPosition(), bounding_box_ };
    }
    
    void SceneNode::setBoundingBoxVisibility(bool visible)
    {
        show_bb_ = visible;
    }
    
    bool SceneNode::getBoundingBoxVisibility() const
    {
        return show_bb_;
    }
    
    Scene * SceneNode::getScene() const
    {
        return scene_;
    }
        
    void SceneNode::setAttachedObject(shared_ptr<Attachment> obj) {
        attachedObject_ = obj;
        if (obj != nullptr)
            obj->setParent(this);
    }
    
    shared_ptr<SceneNode::Attachment> SceneNode::getAttachedObject() const
    {
        return attachedObject_;
    }
    
    shared_ptr<BillboardParticleEmitter> SceneNode::getAttachedEmitter() const
    {
        return std::dynamic_pointer_cast<BillboardParticleEmitter>(attachedObject_);
    }
}