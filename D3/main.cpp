//
//  main.cpp
//  
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define D3_COMPILE  // Compile engine
#include "d3.hpp"

#include <stdlib.h>

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace d3;

shared_ptr<ParticleSystem::Emitter> emitter;
SceneRenderer * renderer;
d3::Simulator * simulator;
Scene * scene;

float cam_radius = 15.0;
float cam_rotation = 0.0;
float cam_y = 8;

void display(void)
{
    renderer->render(scene);    // render scene
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    renderer->setScreenSize(width, height);   // set screen size
}

void update(int value) {
    simulator->simulate(scene);
    ParticleSystem::getInstance()->simulate(1000.0/60);
    //game->update(0.05);
    glutTimerFunc( 1000.0/60, update, 0);
}

void idle(void)
{
    glutPostRedisplay();
}

void updateCamera() {
    Vec3 pos = Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
    scene->getCamera()->getParent()->setPosition(pos);
    
    std::cout << pos << std::endl;
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
        case 'd' :
            scene->getRoot()->getSubnode("Kocka")->move(Vec3(0, 0, -0.5)); break;
        case 'a' :
            scene->getRoot()->getSubnode("Kocka")->move(Vec3(0, 0, 0.5)); break;
        case 'w' :
            scene->getRoot()->getSubnode("Kocka")->move(Vec3(-0.5, 0, 0)); break;
        case 's' :
            scene->getRoot()->getSubnode("Kocka")->move(Vec3(0.5, 0, 0)); break;
        case 'b' :
            emitter->emitting_duration = 0.2; break;
	}
}

void processSpecialKeys(int key, int x, int y) {
    
	switch(key) {
		case GLUT_KEY_UP :
            cam_y -= 0.5f; break;
		case GLUT_KEY_DOWN :
            cam_y += 0.5f; break;
        case GLUT_KEY_LEFT :
            cam_rotation += kPi/6.0; break;
		case GLUT_KEY_RIGHT :
            cam_rotation -= kPi/6.0; break; break;
	}
    
    updateCamera();
}

int main(int argc, char** argv)
{
    srand((unsigned)time(0));
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(640, 480);    
        
    (void)glutCreateWindow("GLUT Program");
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    renderer = new GLSLRenderer(640, 480);
    scene = new Scene();
    
    //scene->getRoot()->createSubnode("Osi", new Renderable(GeometryFactory::createAxes()));
    
    Node *box = scene->getRoot()->createSubnode("Kocka", new Renderable(GeometryFactory::createBox()));
    box->setScale(d3::Vec3(3,3,3));
    box->setBoundingBox(d3::Vec3(2,2,2));
    box->setBoundingBoxVisibility(true);
    scene->getCamera()->setTarget(scene->getRoot());
    
    Renderable *earthPlane = new Renderable(GeometryFactory::createPlane());
    earthPlane->setTexture(shared_ptr<Texture>(new Texture(new Image("/Users/srdan/Desktop/road.png"))));
    scene->getRoot()->createSubnode("Plane", earthPlane)->setScale(Vec3(10, 10, 10));
    
//    SpotLight *sl = new SpotLight;
//    sl->setCutoff(60);
//    sl->setDiffuseColor(Vec4(5.0, 5.0, 5.0, 1.0));
//    scene->getRoot()->createSubnode("Svjetlo", sl);
//    sl->getParent()->setPosition(Vec3(0, 4, 0));
//    sl->setTarget(box);
    
    PointLight *dl = new PointLight;
    scene->getRoot()->createSubnode("SvjetloDir", dl)->setPosition(d3::Vec3(0,3,0));
    dl->setDiffuseColor(d3::Vec4(4,2,2,1));
    dl->setAttenuation(d3::Vec3(1,1,0));
    
    updateCamera();
    
//    /* Particle System test */
//    ParticleSystem::Emitter & e = * new ParticleSystem::Emitter();
//    
//    e.position_variance = Vec3(0, 0, 0);
//    e.direction = Vec3(0, 1, 0);
//    e.direction_variance = Vec3(0.3, 0, 0.3);
//    e.start_color = Vec4(0.5, 0.5, 0.5, 0.5);
//    e.start_color_variance = Vec4(0, 0, 0, 0);
//    e.finish_color = Vec4(0, 0, 0, 0);
//    e.finish_color_variance = Vec4(0, 0, 0, 0);
//    e.lifespan = 3;
//    e.lifespan_variance = 0;
//    e.speed = 1.0;
//    e.speed_variance = 1.0;
//    e.start_size = 110.0;
//    e.start_size_variance = 0.0;
//    e.finish_size = 110.0;
//    e.finish_size_variance = 0.0;
//    //shared_ptr<Texture> texture;
//    e.particle_count = 0;
//    e.particles_per_second = 30;
//    e.particles_par_second_variance = 10;
//    e.emitting_duration = 10;
//    
//    
//    emitter = shared_ptr<ParticleSystem::Emitter>(&e);
//    
//    ParticleSystem::getInstance()->insertEmitter(emitter);
//    
//    shared_ptr<Texture> particle_texture(new Texture(new Image("/Users/srdan/Development/D3/Resources/smoke.png")));
//    
//    scene->getRoot()->createSubnode("Cestice", new ParticleEmitter(emitter, particle_texture));
    
    update(0);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

