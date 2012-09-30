//
//  BillboardParticleEmitter.cpp
//  D3
//
//  Created by Srđan Rašić on 9/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "BillboardParticleEmitter.hpp"

namespace d3 {
    BillboardParticleEmitter::BillboardParticleEmitter(shared_ptr<ParticleEmitterProperties> props) : properties(props)
    {
        /* Caclulate max size */
        emitting_duration = props->emitting_duration;
        max_particle_count = (props->lifespan + props->lifespan_variance) * (props->particles_per_second + props->particles_par_second_variance);
        particle_count = 0;
        
        properties_array = new ParticleProperties[max_particle_count];
        data = new ParticleData[max_particle_count];
        
        /* Initialize element array buffer */
        indices = new unsigned short[max_particle_count * 6]; // Fill??
        
        IndexTemplate tmp;        
        for (int i = 0; i < max_particle_count * 6; i++)
            indices[i] = (i/6)*4 + tmp.indices[i%6];
        
        /* Initialize vertex array buffer */
        glGenBuffers(1, &vertex_color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_color_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(int) * max_particle_count * 4, NULL, GL_STREAM_DRAW);
        
        Vec3 * texcoords = new Vec3[max_particle_count * 4];
        
        for (int i = 0; i < max_particle_count; i++) {
            texcoords[i*4+0] = Vec3(0, 0, 0);
            texcoords[i*4+1] = Vec3(1, 0, 0);
            texcoords[i*4+2] = Vec3(1, 1, 0);
            texcoords[i*4+3] = Vec3(0, 1, 0);
        }
        
        glGenBuffers(1, &vertex_texcoord_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_texcoord_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * max_particle_count * 4, texcoords, GL_STREAM_DRAW);
        
        glGenBuffers(1, &element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_particle_count * 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);
        
        delete indices;
        delete texcoords;
    }
    
    void BillboardParticleEmitter::simulate(float dt)
    {
        static float prev_dt = 0.0;

        ParticleEmitterProperties & e = * properties.get();

        
        /* First update existing particles */
        for (unsigned idx = 0; idx < particle_count;) {
            ParticleProperties & p = properties_array[idx];
            
            if (p.time_to_live > 0.0) {
                p.position = p.position + p.direction * dt * e.speed;
                p.color = p.color + p.color_delta * dt;
                p.size = p.size + p.size_delta * dt;
                
                p.time_to_live -= dt;
                idx++;
            } else {
                particle_count -= 1;
                if (idx != particle_count) {
                    properties_array[idx] = properties_array[particle_count];
                }
            }
        }
        
        if (emitting_duration < 0.0)
            return;
        
        /* Then, emit new particles */
        unsigned int particles_to_emit = (prev_dt + dt) * e.particles_per_second;   // dt [ms]
        
        if (particles_to_emit == 0) {
            prev_dt += dt;
        } else {
            prev_dt = 0.0;
        }

        for (unsigned i = 0; i < particles_to_emit; i++) {
            /* Get particle ref and increase conuter */
            ParticleProperties & p = properties_array[particle_count++];
            
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
        
        //glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_color_buffer);
        int * color_buffer = (int*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        GLenum error = glGetError();
        
        /* Fill buffer */
         for (unsigned i = 0; i < particle_count; i++){
             data[i].left_bottom.position =  Vec3(-0.5, -0.5, 0.0) * properties_array[i].size + properties_array[i].position;
             data[i].right_bottom.position = Vec3( 0.5, -0.5, 0.0) * properties_array[i].size + properties_array[i].position;
             data[i].right_up.position =     Vec3( 0.5,  0.5, 0.0) * properties_array[i].size + properties_array[i].position;
             data[i].left_up.position =      Vec3(-0.5,  0.5, 0.0) * properties_array[i].size + properties_array[i].position;
             
             int color = to8BitVec4(properties_array[i].color);
             color_buffer[i*4+0] = color;
             color_buffer[i*4+1] = color;
             color_buffer[i*4+2] = color;
             color_buffer[i*4+3] = color;
        }
        
        glUnmapBuffer(GL_ARRAY_BUFFER);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleData) * particle_count, data, GL_STREAM_DRAW);
        
        /* decrease emiter life */
        emitting_duration -= dt;
    }
}
