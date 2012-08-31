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

d3GLSceneGraphRenderer *renderer;
d3Scene *scene;

void display(void)
{
    renderer->render(scene);    // render scene
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    scene->getCamera()->setScreenSize(width, height);   // set screen size
}

void idle(void)
{
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
    
	switch(key) {
        case '-' :
            scene->getCamera()->setFovy(scene->getCamera()->getFovy() - 1.0); break;
        case '+' :
            scene->getCamera()->setFovy(scene->getCamera()->getFovy() + 1.0); break;
        case 'i' :
            scene->getRootNode()->getSubnode("Svjetlo1")->move(d3Vec3(0, -0.2, 0)); break;
		case 'o' :
            scene->getRootNode()->getSubnode("Svjetlo1")->move(d3Vec3(0, 0.2, 0)); break;
	}
}

void processSpecialKeys(int key, int x, int y) {
    
	switch(key) {
		case GLUT_KEY_UP :
            scene->getRootNode()->getSubnode("Kocka")->move(d3Vec3(-1, 0, 0)); break;
		case GLUT_KEY_DOWN :
            scene->getRootNode()->getSubnode("Kocka")->move(d3Vec3(1, 0, 0)); break;
        case GLUT_KEY_LEFT :
            scene->getRootNode()->getSubnode("Kocka")->move(d3Vec3(0, 0, 1)); break;
		case GLUT_KEY_RIGHT :
            scene->getRootNode()->getSubnode("Kocka")->move(d3Vec3(0, 0, -1)); break;
	}
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
    
    scene = new d3::d3Scene();
    renderer = new d3GLSceneGraphRenderer();
    
    scene->getRootNode()->createSubnode("Svjetlo1", new d3PointLight())->setPosition(d3Vec3(-0.5, 2, -0.5));
    scene->getRootNode()->createSubnode("Kocka", new d3Box())->setPosition(d3Vec3(0, 0, 0));
    scene->getRootNode()->getSubnode("Kocka")->setScale(d3Vec3(0.1, 0.1, 0.1));
    scene->getRootNode()->createSubnode("Osi", new d3Axes());
    scene->getRootNode()->createSubnode("Ravnina", new d3Plane())->setScale(d3Vec3(3,3,3));
    scene->getCamera()->setTarget(scene->getRootNode()->getSubnode("Kocka"));
    scene->getCamera()->getParent()->setPosition(d3Vec3(5, 5, 5));
    
    // Texture test
    d3Image *slk = new d3Image("/Users/srdan/Desktop/earth.png");
    scene->getRootNode()->getSubnode("Ravnina")->getAttachedObject()->getRenderOperation()->setTexture(new d3Texture(slk));
      
    // Material test
    d3Material *m = new d3Material();
    m->setAmbientAndDiffuseColor(d3Vec4(0.9, 0.9, 0.9, 1.0));
    m->setSpecularColor(d3Vec4(1.0, 1.0, 1.0, 1.0));
    m->setShininess(10);
    scene->getRootNode()->getSubnode("Ravnina")->getAttachedObject()->getRenderOperation()->setMaterial(m);
    
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

