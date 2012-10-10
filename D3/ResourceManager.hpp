//
//  ResourceManager.h
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__ResourceManager__
#define __D3__ResourceManager__

namespace d3 {
    /*! Resource manager class.
     *  Manages "Resource Package".
     *  Resource Package is an organized directory which contains
     *  resources organized into groups (folders) by their type.
     */
    class ResourceManager {
    private:
        /* Groups' definitions */
        const String delimiter = "/";
        const String programs_group = "shaders";
        const String textures_group = "textures";
        const String emitters_group = "emitters";
        
        /* Maps */
        std::unordered_map<String, shared_ptr<Program>> program_map;
        std::unordered_map<String, shared_ptr<Texture>> texture_map;
        std::unordered_map<String, shared_ptr<ParticleSystem>> particle_system_map;
        
        /* Package info */
        String package_path;
        
    public:
        //! @param path Path to resource package
        ResourceManager(String package_path);
        
        /* Loads resource (if not already loaded) and returns pointer to it */
        shared_ptr<Texture> getTexture(String resource_name);
        shared_ptr<ParticleSystem> getParticleSystem(String resource_name);
        shared_ptr<Program> getProgram(String resource_name);
    };
}

#endif