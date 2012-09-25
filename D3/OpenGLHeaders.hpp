//
//  gl.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _OpenGLHeaders_hpp
#define _OpenGLHeaders_hpp

#ifdef _IOS_
#include <OpenGLES/ES2/gl.h>

inline void glFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearVal, GLfloat farVal)
{
    glFrustumf(left, right, bottom, top, nearVal, farVal);
}


#else
#include <OpenGL/gl.h>
#endif

#endif
