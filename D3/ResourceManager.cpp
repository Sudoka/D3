//
//  ResourceManager.cpp
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "ResourceManager.hpp"
#include <algorithm>

namespace d3 {
    ResourceManager::ResourceManager(String package_path) : package_path(package_path)
    {
        /* Check if ends with delimiter */
        if (package_path[package_path.size()-1] != delimiter[0]) {
            this->package_path += delimiter;
            DEBUG_PRINT("Initialized at: " << package_path);
        }
    }
    
    shared_ptr<Texture> ResourceManager::getTexture(String resource_name)
    {
        /* Get existing if exists */
        auto it = texture_map.find(resource_name);
        if (it != texture_map.end())
            return it->second;
        
        /* Otherwise load new */
        Image * image = new Image(package_path + textures_group + delimiter + resource_name);
        shared_ptr<Texture> texture(new Texture(image));
        texture_map[resource_name] = texture;
        delete image;
        
        DEBUG_PRINT("File loaded: " << textures_group << delimiter << resource_name);
        return texture;
    }
    
    shared_ptr<ParticleSystem> ResourceManager::getParticleSystem(String resource_name)
    {
        /* Get existing if exists */
        auto it = particle_system_map.find(resource_name);
        if (it != particle_system_map.end())
            return it->second;
        
        /* Otherwise load new */
        shared_ptr<ParticleSystem::Properties> properties(new ParticleSystem::Properties(package_path + emitters_group + delimiter + resource_name));
        shared_ptr<ParticleSystem> particle_system(new ParticleSystem(properties));
        particle_system_map[resource_name] = particle_system;
        
        DEBUG_PRINT("File loaded: " << emitters_group << delimiter << resource_name);
        return particle_system;
    }
    
    shared_ptr<Program> ResourceManager::getProgram(String resource_name)
    {
        /* Get existing if exists */
        auto it = program_map.find(resource_name);
        if (it != program_map.end())
            return it->second;
        
        /* Otherwise load new */
        shared_ptr<Program> program(new GLSLProgram(resource_name, package_path + programs_group + delimiter + resource_name, true));
        program_map[resource_name] = program;
        
        DEBUG_PRINT("File loaded: " << programs_group << delimiter << resource_name);
        return program;
    }
}