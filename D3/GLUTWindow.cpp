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
    
    GLUTWindow::GLUTWindow(int *argcp, char **argv, const char * title, unsigned width, unsigned height)
    {
        assert(glut_window_instance == nullptr);
        glut_window_instance = this;
        
        glutInit(argcp, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH );
        glutInitWindowSize(width, height);
        glutCreateWindow(title);
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
}