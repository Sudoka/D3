//
//  ParticleEmitter.h
//  D3
//
//  Created by Srđan Rašić on 9/23/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__ParticleEmitter__
#define __D3__ParticleEmitter__

#include "ParticleSystem.hpp"

namespace d3 {
    
    class ParticleEmitter : public SceneNode::Attachment {
    protected:
        shared_ptr<ParticleSystem::Emitter> emitter_;
        shared_ptr<Texture> texture_;
        
    public:
        ParticleEmitter(shared_ptr<ParticleSystem::Emitter>, shared_ptr<Texture> = shared_ptr<Texture>(nullptr));
        ~ParticleEmitter() { DEBUG_PRINT("die") }
        
        shared_ptr<ParticleSystem::Emitter> getEmitter() const;
        shared_ptr<Texture> getTexture() const;
    };
}

#endif