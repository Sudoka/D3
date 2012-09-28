//
//  Application.cpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Application.hpp"

namespace d3 {
    Application::Application(String name, String main_resources_package_path) : name(name)
    {
#ifdef GLUT
        this->window = new GLUTWindow(name, 640, 480, this);
#elif defined _IOS_
        this->window = new EAGLWindow(this);
#endif
        this->resource_manager = new ResourceManager(main_resources_package_path);
        this->renderer = new GLSLRenderer(resource_manager, window->getWidth(), window->getHeight());
        this->simulator = new SceneSimulator();
        this->scene = new Scene();
    }
    
    void Application::render()
    {
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