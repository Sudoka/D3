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
    
    shared_ptr<GLShader> ResourceManager::loadShader(String resource_name, String filename, ShaderType type)
    {
        shared_ptr<GLShader> shader(new GLShader(type, package_path + shaders_group + delimiter + filename));
        shader_map[resource_name] = shader;
        
        DEBUG_PRINT("File loaded: " << shaders_group << delimiter << filename);
        return shader;
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
    
    shared_ptr<ParticleEmitterProperties> ResourceManager::getParticleEmitterProperties(String resource_name)
    {
        /* Get existing if exists */
        auto it = particle_emitter_map.find(resource_name);
        if (it != particle_emitter_map.end())
            return it->second;
        
        /* Otherwise load new */
        shared_ptr<ParticleEmitterProperties> properties(new ParticleEmitterProperties(package_path + emitters_group + delimiter + resource_name));
        particle_emitter_map[resource_name] = properties;
        
        DEBUG_PRINT("File loaded: " << emitters_group << delimiter << resource_name);
        return properties;
    }
    
    shared_ptr<GLShader> ResourceManager::getShader(String name)
    {
        auto iter = shader_map.find(name);
        
        if (iter == shader_map.end()) {
            return nullptr;
        } else {
            return iter->second;
        }
    }
}