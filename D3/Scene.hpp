//
//  Scene.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _Scene_hpp
#define _Scene_hpp

namespace d3 {
   
#pragma mark Interface
    class Camera;
    class Node;
    
    //! Scene.
    class Scene {
    public:
        //typedef std::map<d3::String, Node *> NodeMap;
        typedef std::unordered_set<Node *> NodeSet;
        
    protected:
        Node *root_node_;
        Camera *camera_;
        
        NodeSet scene_nodes_;

        
    public:
        Scene();
        
        ~Scene();
        
        //! @return Scene camera
        Camera * getCamera() const;
        
        //! @return Root node
        Node * getRoot() const;
        
        NodeSet & getNodeSet();
        
        void registerNode(Node * node);
        
        void unregisterNode(Node * node);
    };
}

#endif
