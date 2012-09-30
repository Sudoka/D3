//
//  BillboardParticleEmitter.hpp
//  D3
//
//  Created by Srđan Rašić on 9/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__BillboardParticleEmitter__
#define __D3__BillboardParticleEmitter__

namespace d3 {
    class BillboardParticleEmitter : public SceneNode::Attachment {
    public:
        //! Particle template
        struct ParticleProperties {
            float size;
            float size_delta;
            float time_to_live;
            Vec3 position;
            Vec3 direction;
            Vec4 color;
            Vec4 color_delta;
        };
        
        struct TexColorVertex {
            Vec3 position;
            //Vec4 color;
            //Vec3 texcoord;
        };
        
        struct ParticleData {
            TexColorVertex left_bottom;
            TexColorVertex right_bottom;
            TexColorVertex right_up;
            TexColorVertex left_up;
        };
        
        struct IndexTemplate {
            unsigned short indices[6] = { 3, 3, 0, 2, 1, 1 };
        };
        
    public:
        shared_ptr<ParticleEmitterProperties> properties;
        
        unsigned int max_particle_count;
        unsigned int particle_count;
        
        unsigned int vertex_buffer;
        unsigned int vertex_color_buffer;
        unsigned int vertex_texcoord_buffer;
        unsigned int element_buffer;
        
        ParticleData * data;
        unsigned short * indices;
        ParticleProperties * properties_array;
        
        float emitting_duration;
        
    public:
        BillboardParticleEmitter(shared_ptr<ParticleEmitterProperties> props);
        
        void simulate(float dt);
    };
}

#endif