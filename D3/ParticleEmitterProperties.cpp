//
//  ParticleEmitterProperties.cpp
//  D3
//
//  Created by Srđan Rašić on 9/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "ParticleEmitterProperties.hpp"

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

    ParticleEmitterProperties::ParticleEmitterProperties(String path)
    {
        TiXmlDocument doc(path.c_str());
        doc.LoadFile();
        
        TiXmlElement* config = doc.RootElement();
        
        const char* texture_name = config->FirstChildElement("texture")->Attribute("name");        
        texture = Application::get()->getResourceManager()->getTexture(texture_name);
        
        position_variance = _readPoint3fFromElement(config->FirstChildElement("positionVariance"));
        lifespan = _readValueFromElement(config->FirstChildElement("particleLifeSpan"));
        lifespan_variance = _readValueFromElement(config->FirstChildElement("particleLifeSpanVariance"));
        speed = _readValueFromElement(config->FirstChildElement("speed"));
        speed_variance = _readValueFromElement(config->FirstChildElement("speedVariance"));
        direction = _readPoint3fFromElement(config->FirstChildElement("emittingDirection"));
        direction_variance = _readPoint3fFromElement(config->FirstChildElement("emittingDirectionVariance"));
        //_gravity = _readPoint3fFromElement(config->FirstChildElement("gravity"));
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

}