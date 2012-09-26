//
//  Engine.h
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__Engine__
#define __D3__Engine__

namespace d3 {
    /*! Engine class is responsible for engine and subsystems
     *  initialization, management of them and it functions as 
     *  application's connection to different engine components.
     */
    class Engine {
    private:        
        /* Main subsystems */
        shared_ptr<ResourceManager> resource_manager;
        shared_ptr<SceneRenderer> renderer;
        shared_ptr<SceneSimulator> simulator;
        
        /* Main window */
        Window * window;
        
        /* Scenes */
        std::unordered_map<String, shared_ptr<Scene>> scene_map;
        
    private:
        /* Singleton constructor */
        Engine(String main_package_path, Window * window);
        
    public:        
        /*! @param main_package_path Path to main resource package
         *  @param window Window (view) for rendering
         */
        static Engine * initialize(String main_package_path, Window * window);
        
        //! @return Singleton
        static Engine * get();
        static Engine & getRef();
        
        //! Renders scene
        void renderScene(String name = "DefaultScene");
        
        //! Simulate scene (updates physics)
        void simulateScene(String name = "DefaultScene");
        
        //! @return Reference to main resource manager
        ResourceManager & getResourceManagerRef() const;
        
        //! @return Reference to main renderer
        SceneRenderer & getRendererRef() const;
        
        //! @return Reference to main simlator
        SceneSimulator & getSimulatorRef() const;
        
        //! @return Reference to main window
        Window & getWindowRef() const;
        
        //! @return Reference to scene
        Scene & getSceneRef(String scene_name = "DefaultScene") const;
        
        //! Creates new named scene
        shared_ptr<Scene> createScene(String name);
        
        //! Sets new renderer
        void setRenderer(shared_ptr<SceneRenderer> renderer);
    };
}

#endif