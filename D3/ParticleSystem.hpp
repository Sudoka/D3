//
//  ParticleSystem.h
//  D3
//
//  Created by Srđan Rašić on 9/23/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__ParticleSystem__
#define __D3__ParticleSystem__

namespace d3 {
    class ParticleSystem {
    public:
        //! Particle template
        struct Particle {
            float size;
            float size_delta;
            float time_to_live;
            Vec3 position;
            Vec3 direction;
            Vec4 color;
            Vec4 color_delta;
        };
        
        //! Emiter properties
        struct Emitter {
            Vec3 position_variance;
            Vec3 direction;
            Vec3 direction_variance;
            Vec4 start_color;
            Vec4 start_color_variance;
            Vec4 finish_color;
            Vec4 finish_color_variance;
            float lifespan;
            float lifespan_variance;
            float speed;
            float speed_variance;
            float start_size;
            float start_size_variance;
            float finish_size;
            float finish_size_variance;
            shared_ptr<Texture> texture;
            float particles_per_second;
            float particles_par_second_variance;
            float emitting_duration;
            
            Particle * particle_array;
            unsigned int particle_count;
        };
        
    protected:
        ParticleSystem() {}
        
        std::map<shared_ptr<Emitter>, Particle *> emitters_map_;
        
    public:
        static ParticleSystem * getInstance();
        
        void insertEmitter(shared_ptr<Emitter> emitter);
        
        void simulate(float dt);
    };
}

#endif