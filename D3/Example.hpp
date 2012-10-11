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
            /* Create scene graph tree */
            getScene().getRoot().createSubnode("Box");
            getScene().getRoot().createSubnode("Plane").setScale(Vec3(10, 10, 10));
            getScene().getRoot().createSubnode("Light").setPosition(d3::Vec3(4,2,4));
            getScene().getRoot().createSubnode("Emitter").setPosition(Vec3(4,2,4)).setOrientation(Quat(Vec3(1,0,0), kPi/4));
            getScene().getRoot().createSubnode("CameraTarget").setPosition(Vec3(0,1,0)).setScale(Vec3(5,5,5));
            
            /* Create drawable objects */
            shared_ptr<TexturedMesh> box_object = GeometryFactory::getPrimitive("box");
            shared_ptr<TexturedMesh> plane_object = GeometryFactory::getPrimitive("plane");
            
            /* Setup Drawables */
            box_object->addPointOfOrigin(getScene().getNode("Box"));
            plane_object->addPointOfOrigin(getScene().getNode("Plane"));
            plane_object->setTexture(getResourceManager().getTexture("road.png"));
            
            /* Setup Camera (always to look at the some target node) */
            getScene().getCamera().getMover().setPosition(d3::Vec3(0,0,2));
            getScene().getCamera().setTarget(&getScene().getRoot());
            
            /* Setup light */
            Light * dl = new Light(getScene().getNode("Light"));
            dl->setDiffuseColor(d3::Vec4(5,3,1,1));
            dl->setAttenuation(d3::Vec3(1,0,0.5));

            /* Load ParticleSystem and create BillboardParticles drawable to draw it */
            shared_ptr<ParticleSystem> particle_system = getResourceManager().getParticleSystem("fire.xml");
            BillboardParticles * billboard_particles = new BillboardParticles(particle_system);
            billboard_particles->addPointOfOrigin(getScene().getNode("Emitter"));
            
            static shared_ptr<TexturedMesh> mesh = MeshLoader::loadOBJ(resources_path + "/meshes/747.obj");
            mesh->addPointOfOrigin(getScene().getNode("CameraTarget"));
        }
        
        virtual void update(float dt)
        {
            /* Create simple camera rotation */
            static float cam_radius = 4.0;
            static float cam_rotation = 0.0;
            static float cam_y = 3;
            
            cam_rotation += dt;
            
            Vec3 pos = Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
            getScene().getCamera().getMover().setPosition(pos);
        }
    };
}

#endif
