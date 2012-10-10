//
//  Application.h
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__Application__
#define __D3__Application__

namespace d3 {
    /*! This class is an interface to the engine.
     *  Inherit it and override methods to implement
     *  you application.
     */
    class Application {
    public:
        //! Creates new app
        Application(String name, String main_resources_package_path);
        
        //! Destructs all subsystems
        virtual ~Application();
        
        //! Gets instance to singleton
        static Application & get();
        
        //! @return Reference to main resource manager
        ResourceManager & getResourceManager() const;
        
        //! @return Reference to main renderer
        SceneRenderer & getRenderer() const;
        
        //! @return Reference to main simlator
        SceneSimulator & getSimulator() const;
        
        //! @return Reference to main window
        Window & getWindow() const;
        
        //! @return Current scene
        Scene & getScene() const;
        
        //! Runs main loop
        void run();
        
        //! Renders scene callback
        void render();
        
        //! Idle callback
        void idle();
        
        //! Called before rendering
        virtual void update(float dt) {}
        
        //! Called upon key down
        virtual void onKeyDown(int key) {}
        
        //! Called upon key up
        virtual void onKeyUp(int key) {}
        
    protected:
        /* Basic app info */
        String name;
        
        /* Main subsystems */
        ResourceManager * resource_manager;
        SceneRenderer * renderer;
        SceneSimulator * simulator;
        
        /* Main window */
        Window * window;
        
        /* Scene */
        Scene * scene;
    };
}

#endif