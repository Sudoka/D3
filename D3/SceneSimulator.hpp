//
//  SceneSimulator.h
//  D3
//
//  Created by Srđan Rašić on 9/16/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__Simulator__
#define __D3__Simulator__

namespace d3 {
    class SceneSimulator  {
    public:
        //! Inherit to subscribe for per-frame updates
        struct Updatable {
            Updatable();
            virtual ~Updatable();
            
            virtual void update(float dt) {}
        };
        
        typedef std::list<SceneNode *> NodeList;
        
    protected:
        //! Rendering operation
        class NodeGatherOperation : public SceneNode::VisitOperation {
            NodeList & list;
            
        public:
            NodeGatherOperation(NodeList & list);
            virtual void beginNode(SceneNode *node);
        };
        
    protected:
        /* Scene */
        Scene * scene;
        
        /* Updatables */
        std::list<Updatable *> updatable_list;
        
    public:
        //! Scene simulator
        SceneSimulator(Scene * scene);
        
        //! Simulate scene animables nad updatables
        void simulate(float dt);
        
        //! Check for collisions between node and part of scene graph
        void checkForCollisions(SceneNode * root_node, SceneNode * node);
        
        //! Registers updatable
        void registerUpdatable(Updatable * updatable);
        
        //! Unregisters updatable
        void unregisterUpdatable(Updatable * updatable);
    };
}

#endif
