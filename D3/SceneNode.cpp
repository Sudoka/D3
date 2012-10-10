//
//  SceneNode.cpp
//  D3
//
//  Created by Srđan Rašić on 9/28/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "SceneNode.hpp"

namespace d3 {
    SceneNode::SceneNode(String node_name, Scene & scene)
    : Node(node_name), scene(scene)
    {
        show_bb = false;
        bounding_box = Vec3(1, 1, 1);
        user_data = nullptr;
        
        scene._nodeCreated(this);
    }
    
    SceneNode::~SceneNode()
    {
        getScene()._nodeWillBeDeleted(this);
        Node::~Node();
    }
        
    SceneNode & SceneNode::createSubnode(String name)
    {
        SceneNode * node = new SceneNode(name, getScene());
        addSubnode(node);
        return * node;
    }
    
    SceneNode & SceneNode::getSubnode(String name) const
    {
        return (SceneNode &)Node::getSubnode(name);
    }
    
    void SceneNode::traverse(shared_ptr<SceneNode::VisitOperation> op)
    {
        // begin this node
        op->beginNode(this);
        
        // travers subnodes
        for (Node * node : sub_nodes_) {
            ((SceneNode*)node)->traverse(op);
        }
        
        // end this node
        op->endNode(this);
    }
    
    void SceneNode::setBoundingBox(Vec3 box)
    {
        bounding_box = box;
    }
    
    Box SceneNode::getBoundingBox(bool derived_position)
    {
        if (derived_position)
            return { getDerivedPosition(), bounding_box };
        else
            return { getPosition(), bounding_box };
    }
    
    void SceneNode::setBoundingBoxVisibility(bool visible)
    {
        show_bb = visible;
    }
    
    bool SceneNode::getBoundingBoxVisibility() const
    {
        return show_bb;
    }
    
    Scene & SceneNode::getScene() const
    {
        return scene;
    }
    
    void SceneNode::setUserData(UserData * user_data)
    {
        this->user_data = user_data;
    }
    
    SceneNode::UserData * SceneNode::getUserData() const
    {
        return this->user_data;
    }
}