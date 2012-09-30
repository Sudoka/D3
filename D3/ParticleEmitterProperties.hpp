//
//  ParticleEmitterProperties.hpp
//  D3
//
//  Created by Srđan Rašić on 9/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_ParticleEmitterProperties_hpp
#define D3_ParticleEmitterProperties_hpp

namespace d3 {
    //! Emiter properties
    struct ParticleEmitterProperties {
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
        
        ParticleEmitterProperties(String path);
    };
}

#endif
