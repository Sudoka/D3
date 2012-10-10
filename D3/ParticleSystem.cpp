//
//  ParticleSystem.cpp
//  D3
//
//  Created by Srđan Rašić on 9/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "ParticleSystem.hpp"

#include <tinyxml/tinyxml.h>

// Compile tinyxml (bad, I know)
#include <tinyxml/tinyxml.cpp>
#include <tinyxml/tinystr.cpp>
#include <tinyxml/tinyxmlerror.cpp>
#include <tinyxml/tinyxmlparser.cpp>

namespace d3 {
    double _readValueFromElement(TiXmlElement* element) {
		return atof(element->Attribute("value"));
	}
	
	Vec3 _readPoint3fFromElement(TiXmlElement* element) {
		Vec3 p;
		p.x = atof(element->Attribute("x"));
		p.y = atof(element->Attribute("y"));
		p.z = atof(element->Attribute("z"));
		return p;
	}
	
	Vec4 _readColor4fFromElement(TiXmlElement* element) {
		Vec4 c;
		c.r = atof(element->Attribute("r"));
		c.g = atof(element->Attribute("g"));
		c.b = atof(element->Attribute("b"));
		c.a = atof(element->Attribute("a"));
		return c;
	}
    
    ParticleSystem::Properties::Properties(String path)
    {
        TiXmlDocument doc(path.c_str());
        doc.LoadFile();
        
        TiXmlElement* config = doc.RootElement();
        
        const char* texture_name = config->FirstChildElement("texture")->Attribute("name");
        texture = Application::get().getResourceManager().getTexture(texture_name);
        
        position_variance = _readPoint3fFromElement(config->FirstChildElement("positionVariance"));
        lifespan = _readValueFromElement(config->FirstChildElement("particleLifeSpan"));
        lifespan_variance = _readValueFromElement(config->FirstChildElement("particleLifeSpanVariance"));
        speed = _readValueFromElement(config->FirstChildElement("speed"));
        speed_variance = _readValueFromElement(config->FirstChildElement("speedVariance"));
        direction = _readPoint3fFromElement(config->FirstChildElement("emittingDirection"));
        direction_variance = _readPoint3fFromElement(config->FirstChildElement("emittingDirectionVariance"));
        start_color = _readColor4fFromElement(config->FirstChildElement("startColor"));
        start_color_variance = _readColor4fFromElement(config->FirstChildElement("startColorVariance"));
        finish_color = _readColor4fFromElement(config->FirstChildElement("finishColor"));
        finish_color_variance = _readColor4fFromElement(config->FirstChildElement("finishColorVariance"));
        start_size = _readValueFromElement(config->FirstChildElement("startParticleSize"));
        start_size_variance = _readValueFromElement(config->FirstChildElement("startParticleSizeVariance"));
        finish_size = _readValueFromElement(config->FirstChildElement("finishParticleSize"));
        finish_size_variance = _readValueFromElement(config->FirstChildElement("finishParticleSizeVariance"));
        particles_per_second = _readValueFromElement(config->FirstChildElement("particlesPerSecond"));
        particles_par_second_variance = _readValueFromElement(config->FirstChildElement("particlesPerSecondVariance"));
        emitting_duration = _readValueFromElement(config->FirstChildElement("emittingDuration"));
    }
    
    ParticleSystem::ParticleSystem(shared_ptr<ParticleSystem::Properties> props) : properties(props)
    {
        /* Caclulate max size */
        emitting_duration = props->emitting_duration;
        max_particle_count = (props->lifespan + props->lifespan_variance) * (props->particles_per_second + props->particles_par_second_variance);
        particle_count = 0;
        
        properties_array = new ParticleProperties[max_particle_count];
    }
    
    void ParticleSystem::update(float dt)
    {
        static float prev_dt = 0.0;

        Properties & e = * properties.get();

        
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
        
        if (emitting_duration < 0.0 && emitting_duration != -1.0)
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
            
            p.direction = (e.direction + e.direction_variance.mul(randv3(-1, 1)));
            
            p.color = e.start_color + e.start_color_variance.mul(randv4(0, 1));
            
            Vec4 finish_color_variance = e.finish_color_variance.mul(randv4(0, 1));
            float one_over_ttl = 1.0 / p.time_to_live;
            p.color_delta = (e.finish_color - finish_color_variance - p.color).mul(Vec4(one_over_ttl, one_over_ttl, one_over_ttl, one_over_ttl));
            
            p.size = e.start_size + e.start_size_variance * randf(-1, 1);
            p.size_delta = (e.finish_size + e.finish_size_variance * randf(-1, 1) - p.size) / p.time_to_live;
        }
        
        /* decrease emiter life if not set to infinity (-1.0) */
        if (emitting_duration != -1.0)
            emitting_duration -= dt;
    }
}
