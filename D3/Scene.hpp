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
    class SceneNode;
    
    //! Scene.
    class Scene {
    public:
        typedef std::unordered_map<String, SceneNode *> NodeMap;
        
        //! Used to listen for Scene changes' notifications
        struct Listener {
            virtual void onNodeInsert(SceneNode * node) {}
            virtual void onNodeRemove(SceneNode * node) {}
        };        

    public:
        //! Default constructor
        Scene();
        
        //! Destructor
        ~Scene();
                
        //! @return Scene camera
        Camera & getCamera() const;
        
        //! @return Root node
        SceneNode & getRoot() const;
        
        //! @return Reference to map with all nodes in scene
        const NodeMap & getNodeMap() const;
        
        //! @return Node named name
        SceneNode & getNode(String name);
        
        //! Registers new listener
        void registerListener(Listener * listener);
        
        //! Removes listener from list
        void unregisterListener(Listener * listener);
        
        //! Called internaly after new node is created
        void _nodeCreated(SceneNode * node);
        
        //! Called internaly upon node deletion
        void _nodeWillBeDeleted(SceneNode * node);
        
    protected:
        SceneNode * root_node;
        shared_ptr<Camera> camera;
        std::list<Listener *> listeners;
        NodeMap node_map;
    };
}

#endif
