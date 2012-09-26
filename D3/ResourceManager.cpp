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
    
    shared_ptr<Texture> ResourceManager::loadTexture(String resource_name, String filename)
    {
        Image * image = new Image(package_path + textures_group + delimiter + filename);
        shared_ptr<Texture> texture(new Texture(image));
        texture_map[resource_name] = texture;
        delete image;
        
        DEBUG_PRINT("File loaded: " << textures_group << delimiter << filename);
        return texture;
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