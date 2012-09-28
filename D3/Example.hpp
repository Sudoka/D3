//
//  Example.hpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Example_hpp
#define D3_Example_hpp

namespace d3 {    
    class Example : public Application {
    public:
        Example(String resources_path) : Application("Example App", resources_path)
        {
            /* Create box */
            Node *box = getScene()->getRoot()->createSubnode("Kocka", new Renderable(GeometryFactory::createBox()));
            box->setPosition(d3::Vec3(0,0,2))->setScale(d3::Vec3(1,1,1));
            
            /* Draw BB :) */
            //box->setBoundingBox(d3::Vec3(2,2,2));
            //box->setBoundingBoxVisibility(true);
            
            /* Set camera to always look at the box */
            getScene()->getCamera()->getParent()->setPosition(d3::Vec3(0,0,2));
            getScene()->getCamera()->setTarget(getScene()->getRoot());
            
            /* Create plane */
            Renderable *earthPlane = new Renderable(GeometryFactory::createPlane());
            earthPlane->setTexture(getResourceManager()->loadTexture("road.png", "road.png"));
            earthPlane->getMaterial()->setShininess(40);
            getScene()->getRoot()->createSubnode("Plane", earthPlane)->setScale(Vec3(5, 5, 5));
            
            /* Create light */
            PointLight *dl = new PointLight;
            getScene()->getRoot()->createSubnode("Svjetlo", dl)->setPosition(d3::Vec3(3,1,0));
            dl->setDiffuseColor(d3::Vec4(4,1,8,1));
            dl->setAttenuation(d3::Vec3(1,1,0));
            
            /* Particle System test */
            ParticleSystem::Emitter & e = * new ParticleSystem::Emitter();
            
            e.position_variance = Vec3(0, 0, 0);
            e.direction = Vec3(0, 1, 0);
            e.direction_variance = Vec3(0.3, 0, 0.3);
            e.start_color = Vec4(0.6, 0.6, 0.6, 1.0);
            e.start_color_variance = Vec4(0, 0, 0, 0);
            e.finish_color = Vec4(0.9, 0.5, 0.5, 0.0);
            e.finish_color_variance = Vec4(0, 0, 0, 0);
            e.lifespan = 1.5;
            e.lifespan_variance = 0;
            e.speed = 2;
            e.speed_variance = 0.5;
            e.start_size = 0;
            e.start_size_variance = 0.0;
            e.finish_size = 64;
            e.finish_size_variance = 0.0;
            e.particle_count = 0;
            e.particles_per_second = 50;
            e.particles_par_second_variance = 10;
            e.emitting_duration = 30;
            
            shared_ptr<ParticleSystem::Emitter> emitter = shared_ptr<ParticleSystem::Emitter>(&e);
            
            ParticleSystem::getInstance()->insertEmitter(emitter);
            
            shared_ptr<Texture> particle_texture(getResourceManager()->loadTexture("smoke", "particle01.png"));
            
            scene->getRoot()->createSubnode("Cestice", new ParticleEmitter(emitter, particle_texture));
        }
        
        virtual void update(float dt)
        {
            static float cam_radius = 7.0;
            static float cam_rotation = 0.0;
            static float cam_y = 2;
            
            cam_rotation += dt;
            
            Vec3 pos = Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
            getScene()->getCamera()->getParent()->setPosition(pos);
        }
    };
}

#endif
