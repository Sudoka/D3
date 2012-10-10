//
//  GLUTWindow.cpp
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "GLUTWindow.hpp"

namespace d3 {
    static GLUTWindow * glut_window_instance = nullptr;
    
    void GLUTWindow::glut_display_callback(void)
    {
        glut_window_instance->application->render();
        glutSwapBuffers();
    }
    
    void GLUTWindow::glut_idle_callback(void)
    {
    }
    
    void GLUTWindow::glut_timer_callback(int value)
    {
        glut_window_instance->application->idle();
        glutTimerFunc(1000.0/60, GLUTWindow::glut_timer_callback, 0);
        glutPostRedisplay();
    }
    
    void GLUTWindow::glut_reshape_callback(int width, int height)
    {
        //glut_window_instance->application->getRenderer().setScreenSize(width, height);
    }
    
    void GLUTWindow::glut_keydown_callback(unsigned char key, int x, int y)
    {
        glut_window_instance->application->onKeyDown(key);
    }
    
    void GLUTWindow::glut_special_keydown_callback(int key, int x, int y)
    {
        glut_window_instance->application->onKeyDown(key + 1000);
    }
    
    void GLUTWindow::glut_special_keyup_callback(int key, int x, int y)
    {
        glut_window_instance->application->onKeyUp(key + 1000);
    }
    
    GLUTWindow::GLUTWindow(String title, unsigned width, unsigned height,  Application * application) : Window(application)
    {
        assert(glut_window_instance == nullptr);
        glut_window_instance = this;
        
        int null = 0;
        glutInit(&null, NULL);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(width, height);
        glutCreateWindow(title.c_str());
        
        glutDisplayFunc(GLUTWindow::glut_display_callback);
        glutIdleFunc(GLUTWindow::glut_idle_callback);
        glutReshapeFunc(GLUTWindow::glut_reshape_callback);
        
        glutKeyboardFunc(GLUTWindow::glut_keydown_callback);
        glutSpecialFunc(GLUTWindow::glut_special_keydown_callback);
        glutSpecialUpFunc(GLUTWindow::glut_special_keyup_callback);
    }
    
    void GLUTWindow::setupContext()
    {
    }
    
    unsigned GLUTWindow::getWidth()
    {
        return glutGet(GLUT_WINDOW_WIDTH);
    }
    
    unsigned GLUTWindow::getHeight()
    {
        return glutGet(GLUT_WINDOW_HEIGHT);
    }
    
    float GLUTWindow::getTimerValue()
    {
        return glutGet(GLUT_ELAPSED_TIME) / 1000.f;
    }
    
    void GLUTWindow::runLoop()
    {
        GLUTWindow::glut_timer_callback(0);
        glutMainLoop();
    }
}