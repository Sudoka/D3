//
//  ParticleSystem.cpp
//  D3
//
//  Created by Srđan Rašić on 9/23/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "ParticleSystem.hpp"

namespace d3 {
    
    static ParticleSystem * particle_system_instance_ = nullptr;
    
    ParticleSystem * ParticleSystem::getInstance()
    {
        if (particle_system_instance_ == nullptr)
            particle_system_instance_ = new ParticleSystem();
        return particle_system_instance_;
    }
    
    void ParticleSystem::insertEmitter(shared_ptr<ParticleSystem::Emitter> emitter)
    {
        Emitter & e = * emitter.get();
        
        unsigned int max_particle_count = e.emitting_duration
                                        * (e.lifespan + e.lifespan_variance)
                                        * (e.particles_per_second + e.particles_par_second_variance);
        
        Particle * particles = new Particle[max_particle_count];
        
        e.particle_array = particles;
        emitters_map_[emitter] = particles;
    }
    
    void ParticleSystem::simulate(float dt)
    {
        static float prev_dt = 0.0;
        
        dt /= 1000.0;

        for (auto it : emitters_map_) {
            Emitter & e = * it.first.get();
            Particle * particles = it.second;
            
            /* First update existing particles */
            for (unsigned idx = 0; idx < e.particle_count;) {
                Particle & p = particles[idx];
                
                if (p.time_to_live > 0.0) {
                    p.position = p.position + p.direction * dt * e.speed;
                    p.color = p.color + p.color_delta * dt;
                    p.size = 150;
                    
                    p.time_to_live -= dt;
                    idx++;
                } else {
                    e.particle_count -= 1;
                    if (idx != e.particle_count) {
                        particles[idx] = particles[e.particle_count];
                    }
                }
            }
            
            if (e.emitting_duration < 0.0)
                continue;
            
            /* Then, emit new particles */
            unsigned int particles_to_emit = (prev_dt + dt) * e.particles_per_second;   // dt [ms]
            
            if (particles_to_emit == 0) {
                prev_dt += dt;
            } else {
                prev_dt = 0.0;
            }
            
            for (unsigned i = 0; i < particles_to_emit; i++) {
                /* Get particle ref and increase conuter */
                Particle & p = particles[e.particle_count++];
                
                /* Initialise particle */
                p.time_to_live = e.lifespan + e.lifespan_variance * randf(-1, 1);
                
                p.position = e.position_variance.mul(randv3(-1, 1));
                
                p.direction = e.direction + e.direction_variance.mul(randv3(-1, 1));
                
                p.color = e.start_color + e.start_color_variance.mul(randv4(-1, 1));
                
                Vec4 finish_color_variance = e.finish_color_variance.mul(randv4(-1, 1));
                float one_over_ttl = 1.0 / p.time_to_live;
                p.color_delta = (e.finish_color + finish_color_variance - p.color).mul(Vec4(one_over_ttl, one_over_ttl, one_over_ttl, one_over_ttl));
                
                p.size = e.start_size + e.start_size_variance * randf(-1, 1);
                p.size_delta = (e.finish_size + e.finish_size_variance * randf(-1, 1) - p.size) / p.time_to_live;
            }
            
            /* decrease emiter life */
            e.emitting_duration -= dt;
        }
    }
}