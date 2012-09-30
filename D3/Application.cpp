//
//  Application.cpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Application.hpp"

namespace d3 {
    static Application * application_instance__ = nullptr;
    
    Application::Application(String name, String main_resources_package_path) : name(name)
    {
        //! Singleton!
        assert(application_instance__ == nullptr);
        application_instance__ = this;
        
#ifdef GLUT
        this->window = new GLUTWindow(name, 640, 480, this);
#elif defined _IOS_
        this->window = new EAGLWindow(this);
#endif
        this->resource_manager = new ResourceManager(main_resources_package_path);
        //this->renderer = new GLSLRenderer(resource_manager, window->getWidth(), window->getHeight());
        this->renderer = new GL13Renderer(window->getWidth(), window->getHeight());
        this->simulator = new SceneSimulator();
        this->scene = new Scene();
    }
    
    Application * Application::get()
    {
        assert(application_instance__);
        return application_instance__;
    }
    
    void Application::render()
    {
        /* Calc FPS */
        static int num_of_frames = 0;
        static float duration = 0.0;
        static float last_call_time = window->getTimerValue();
        static float fps = 0;
        
        duration += window->getTimerValue() - last_call_time;
        if (duration > 1.0) {
            fps = num_of_frames / duration;
            duration = 0.0;
            num_of_frames = 0;
                    DEBUG_PRINT("FPS: " << fps)
        }
        
        last_call_time = window->getTimerValue();
        num_of_frames++;
        

        renderer->render(scene);
    }
    
    void Application::idle()
    {
        static float previous_time = window->getTimerValue();
        float current_time = window->getTimerValue();
        float delta_time = current_time - previous_time;
        previous_time = current_time;
        
        update(delta_time);
        simulator->simulate(scene, delta_time);
    }
    
    void Application::run()
    {
        window->runLoop();
    }
    
    ResourceManager * Application::getResourceManager() const
    {
        return resource_manager;
    }
    
    SceneRenderer * Application::getRenderer() const
    {
        return renderer;
    }
    
    SceneSimulator * Application::getSimulator() const
    {
        return simulator;
    }
    
    Window & Application::getWindowRef() const
    {
        return * window;
    }
    
    Window * Application::getWindow() const
    {
        return window;
    }
    
    Scene * Application::getScene() const
    {
        return scene;
    }
}