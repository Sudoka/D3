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

SceneRenderer * renderer;
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

void idle(void)
{
    glutPostRedisplay();
}

void updateCamera() {
    Vec3 pos = Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
    scene->getCamera()->getParent()->setPosition(pos);
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
    
    renderer = new GLSceneRenderer(640, 480);
    scene = new Scene();
    
    scene->getRoot()->createSubnode("Osi", new Renderable(GeometryFactory::createAxes()));
    
    Node *box = scene->getRoot()->createSubnode("Kocka", new Renderable(GeometryFactory::createBox()));
    box->setScale(Vec3(0.5, 0.5, 0.5))->move(Vec3(0, 0.5, 0));
    scene->getCamera()->setTarget(box);
    
    Renderable *earthPlane = new Renderable(GeometryFactory::createPlane());
    earthPlane->setTexture(new Texture(new Image("Resources/earth.png")));
    scene->getRoot()->createSubnode("Earth", earthPlane)->setScale(Vec3(10, 10, 10));
    
    SpotLight *sl = new SpotLight;
    sl->setCutoff(30);
    sl->setDiffuseColor(Vec4(5.0, 5.0, 5.0, 1.0));
    scene->getRoot()->createSubnode("Svjetlo", sl);
    sl->getParent()->setOrientation(Quat(Vec3(0, 1, 0), -kPiOver2))->setPosition(Vec3(0, 4, 0));
    sl->setTarget(box);
    
    updateCamera();
       
    GLProgram program(shared_ptr<GLShader>(new GLShader(D3_VERTEX_PROGRAM, "D3/Shader.vsh")),
                        shared_ptr<GLShader>(new GLShader(D3_FRAGMENT_PROGRAM, "D3/Shader.fsh")));
    
    program.compile();
    program.link();
    program.printInfoLog();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

