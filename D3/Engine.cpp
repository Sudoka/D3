//
//  Engine.cpp
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Engine.hpp"

namespace d3 {
    static Engine * engine_instance = nullptr;
    
    Engine::Engine(String main_package_path, Window * window) : window(window)
    {
        /* Setup singleton */
        engine_instance = this;
        
        this->resource_manager = shared_ptr<ResourceManager>(new ResourceManager(main_package_path));
        this->renderer = shared_ptr<SceneRenderer>(new GLSLRenderer(window->getWidth(), window->getHeight()));
        this->simulator = shared_ptr<SceneSimulator>(new SceneSimulator());
        
        scene_map["DefaultScene"] = shared_ptr<Scene>(new Scene());
        
        /* Other initialization staff */
        srand((unsigned)time(0));
    }
    
    Engine * Engine::initialize(String main_package_path, Window * window)
    {
        /* Just create object of this */
        return new Engine(main_package_path, window);
    }
    
    Engine * Engine::get()
    {
        assert(engine_instance);
        return engine_instance;
    }
    
    Engine & Engine::getRef()
    {
        return * get();
    }
    
    void Engine::renderScene(String name)
    {
        renderer->render(scene_map.find(name)->second);
    }
    
    void Engine::simulateScene(String name)
    {
        simulator->simulate(scene_map.find(name)->second);
    }
    
    ResourceManager & Engine::getResourceManagerRef() const
    {
        return * resource_manager.get();
    }
    
    SceneRenderer & Engine::getRendererRef() const
    {
        return * renderer.get();
    }
    
    SceneSimulator & Engine::getSimulatorRef() const
    {
        return * simulator.get();
    }
    
    Window &  Engine::getWindowRef() const
    {
        return * window;
    }
    
    Scene &  Engine::getSceneRef(String scene_name) const
    {
        return * (scene_map.find(scene_name)->second).get();
    }
    
    shared_ptr<Scene> Engine::createScene(String name)
    {
        shared_ptr<Scene> scene(new Scene());
        scene_map[name] = scene;
        return scene;
    }
    
    void Engine::setRenderer(shared_ptr<SceneRenderer> renderer)
    {
        this->renderer = renderer;
    }
}