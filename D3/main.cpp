//
//  main.cpp
//  
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//
//  Eaxample of simple scene and per-pixel lightning
//  Usage: arrows to move camera, 'wasd' to move box
//

#define D3_COMPILE  // Compile engine (include all cpps to avoid libraries for now)
#include "d3.hpp"

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace d3;

void display(void)
{
    Engine::getRef().renderScene();
    glutSwapBuffers();
}

void update(int value) {
    Engine::getRef().simulateScene();
    glutTimerFunc( 1000.0/60, update, 0);
}

void idle(void)
{
    glutPostRedisplay();
}

// Move Box accordinaly
void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
        case 'd' :
            Engine::getRef().getSceneRef().getRoot()->getSubnode("Kocka")->move(Vec3(0, 0, -0.5)); break;
        case 'a' :
            Engine::getRef().getSceneRef().getRoot()->getSubnode("Kocka")->move(Vec3(0, 0, 0.5)); break;
        case 'w' :
            Engine::getRef().getSceneRef().getRoot()->getSubnode("Kocka")->move(Vec3(-0.5, 0, 0)); break;
        case 's' :
            Engine::getRef().getSceneRef().getRoot()->getSubnode("Kocka")->move(Vec3(0.5, 0, 0)); break;
	}
}

// We just manage camera position here
void processSpecialKeys(int key, int x, int y)
{
    static float cam_radius = 15.0;
    static float cam_rotation = 0.0;
    static float cam_y = 8;
    
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
    
    Vec3 pos = Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
    Engine::getRef().getSceneRef().getCamera()->getParent()->setPosition(pos);
}

int main(int argc, char** argv)
{
    /* Initialize */
    Window * main_window = new GLUTWindow(&argc, argv, "Prozor", 640, 480);
    Engine::initialize("Resources", main_window);   // Change first arg to reflect your main resource package path (Resources dir full path)

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    /* Setup scene */
    Node * root = Engine::getRef().getSceneRef().getRoot();
    
    /* Create box */
    Node *box = root->createSubnode("Kocka", new Renderable(GeometryFactory::createBox()));
    box->setScale(d3::Vec3(3,3,3));
    
    /* Draw BB :) */
    box->setBoundingBox(d3::Vec3(2,2,2));
    box->setBoundingBoxVisibility(true);
    
    /* Set camera to always look at the box */
    Engine::getRef().getSceneRef().getCamera()->setTarget(box);
    
    /* Create plane */
    Renderable *earthPlane = new Renderable(GeometryFactory::createPlane());
    earthPlane->setTexture(Engine::get()->getResourceManagerRef().loadTexture("road.png", "road.png"));
    root->createSubnode("Plane", earthPlane)->setScale(Vec3(10, 10, 10));
    
    /* Create light */
    PointLight *dl = new PointLight;
    root->createSubnode("SvjetloDir", dl)->setPosition(d3::Vec3(0,3,0));
    dl->setDiffuseColor(d3::Vec4(4,2,2,1));
    dl->setAttenuation(d3::Vec3(1,1,0));
        
    // Bahh
    update(0);
    processSpecialKeys(0, 0, 0);
    
    // Engage
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

