//
//  main.cpp
//  D3
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#define D3_COMPILE  // Compile engine
#include "d3.hpp"

#include <stdlib.h>

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace d3;

d3SceneRenderer * renderer;
d3Scene * scene;

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

void idle(void)
{
    glutPostRedisplay();
}

void updateCamera() {
    d3Vec3 pos = d3Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
    scene->getCamera()->getParent()->setPosition(pos);
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
        case 'd' :
            scene->getRoot()->getSubnode("Kocka")->move(d3Vec3(0, 0, -0.5)); break;
        case 'a' :
            scene->getRoot()->getSubnode("Kocka")->move(d3Vec3(0, 0, 0.5)); break;
        case 'w' :
            scene->getRoot()->getSubnode("Kocka")->move(d3Vec3(-0.5, 0, 0)); break;
        case 's' :
            scene->getRoot()->getSubnode("Kocka")->move(d3Vec3(0.5, 0, 0)); break;
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
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);    
        
    (void)glutCreateWindow("GLUT Program");
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    renderer = new d3GLSceneRenderer(640, 480);
    scene = new d3Scene();
    
    d3Node *box = scene->getRoot()->createSubnode("Kocka", new d3Renderable(d3GeometryFactory::createBox()));
    box->setScale(d3Vec3(0.5, 0.5, 0.5))->move(d3Vec3(0, 0.5, 0));
    scene->getCamera()->setTarget(box);
    
    d3Renderable *earthPlane = new d3Renderable(d3GeometryFactory::createPlane());
    earthPlane->setTexture(new d3Texture(new d3Image("/Users/srdan/Desktop/earth.png")));
    scene->getRoot()->createSubnode("Earth", earthPlane)->setScale(d3Vec3(10, 10, 10));
    
    d3SpotLight *sl = new d3SpotLight;
    sl->setCutoff(30);
    sl->setDiffuseColor(d3Vec4(5.0, 5.0, 5.0, 1.0));
    scene->getRoot()->createSubnode("Svjetlo", sl);
    sl->getParent()->setOrientation(d3Quat(d3Vec3(0, 1, 0), -kPiOver2))->setPosition(d3Vec3(0, 4, 0));
    sl->setTarget(box);
    
    updateCamera();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

