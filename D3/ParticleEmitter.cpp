//
//  ParticleEmitter.cpp
//  D3
//
//  Created by Srđan Rašić on 9/23/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "ParticleEmitter.hpp"

namespace d3 {    
    ParticleEmitter::ParticleEmitter(shared_ptr<ParticleSystem::Emitter> emitter, shared_ptr<Texture> texture) : emitter_(emitter), texture_(texture)
    {
    }
    
    shared_ptr<ParticleSystem::Emitter> ParticleEmitter::getEmitter() const
    {
        return emitter_;
    }
    
    shared_ptr<Texture> ParticleEmitter::getTexture() const
    {
        return texture_;
    }
}