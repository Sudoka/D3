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
        typedef std::unordered_set<SceneNode *> RenderableSet;
        typedef std::unordered_set<SceneNode *> EmittersSet;
        typedef std::unordered_set<SceneNode *> LightSourceSet;
        
    protected:
        SceneNode * root_node;
        shared_ptr<Camera> camera;
        
        /* Set of with all nodes in scene that cointains renderable attachment */
        RenderableSet renderable_nodes;
        
        /* Set of with all nodes in scene that cointains light source attachment */
        LightSourceSet light_sources;
        
        EmittersSet emitter_nodes;

    public:
        //! Default constructor
        Scene();
        
        //! Destructor
        ~Scene();
                
        //! @return Scene camera
        shared_ptr<Camera> getCamera() const { return camera; }
        
        //! @return Root node
        SceneNode * getRoot() const { return root_node; };
        
        //! @return Reference to light sources set
        LightSourceSet & getLightSourcesRef() { return light_sources; }
        
        //! @return Reference to renderable nodes set
        RenderableSet & getRenderablesRef() { return renderable_nodes; }
        
        //! @return Reference to emitter nodes set
        RenderableSet & getEmittersRef() { return emitter_nodes; }
    };
}

#endif
