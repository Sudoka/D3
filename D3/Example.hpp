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
            SceneNode *box = getScene()->getRoot()->createSubnode("Kocka", shared_ptr<Renderable>(new Renderable(GeometryFactory::createBox())));
            box->setPosition(d3::Vec3(0,0,2))->setScale(d3::Vec3(1,1,1));
            
            /* Draw BB :) */
            //box->setBoundingBox(d3::Vec3(2,2,2));
            //box->setBoundingBoxVisibility(true);
            
            /* Set camera to always look at the box */
            getScene()->getCamera()->getParent()->setPosition(d3::Vec3(0,0,2));
            SceneNode * camera_target = getScene()->getRoot()->createSubnode("CameraTarget");
            camera_target->setPosition(Vec3(0,2,0));
            getScene()->getCamera()->setTarget(camera_target);
            
            /* Create plane */
            shared_ptr<Renderable> earthPlane(new Renderable(GeometryFactory::createPlane()));
            earthPlane->setTexture(getResourceManager()->getTexture("road.png"));
            //earthPlane->getMaterial()->setShininess(40);
            getScene()->getRoot()->createSubnode("Plane1", earthPlane)->setScale(Vec3(5, 5, 5));
            getScene()->getRoot()->createSubnode("Plane2", earthPlane)->setPosition(d3::Vec3(-10,0,0))->setScale(Vec3(5, 5, 5));
            
            /* Create light */
            shared_ptr<PointLight> dl(new PointLight);
            getScene()->getRoot()->createSubnode("Svjetlo1", dl)->setPosition(d3::Vec3(3,1,0));
            getScene()->getRoot()->getSubnode("Svjetlo1")->createSubnode("KCK", shared_ptr<Renderable>(new Renderable(GeometryFactory::createBox())));
            dl->setDiffuseColor(d3::Vec4(4,1,8,1));
            dl->setAttenuation(d3::Vec3(1,1,0));
            
            /* Create light */
            shared_ptr<SpotLight> sl(new SpotLight);
            getScene()->getRoot()->createSubnode("Svjetlo2", (shared_ptr<PointLight>)sl)->setPosition(d3::Vec3(3,2,0));
            //sl->setTarget(getScene()->getRoot()->getSubnode("Plane2"));
            sl->setDirection(d3::Vec3(-1,-1,0));
            sl->setDiffuseColor(d3::Vec4(4,1,8,1));
            sl->setAttenuation(d3::Vec3(1,0,0));
            
            shared_ptr<ParticleEmitterProperties> props = getResourceManager()->getParticleEmitterProperties("fire.xml");
            
            shared_ptr<BillboardParticleEmitter> emitter(new BillboardParticleEmitter(props));
            
            scene->getRoot()->createSubnode("Cestice", emitter);
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
