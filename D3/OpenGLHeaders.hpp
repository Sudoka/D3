//
//  gl.hpp
//  
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _OpenGLHeaders_hpp
#define _OpenGLHeaders_hpp

#ifdef _IOS_    // OpenGL ES 2.0
#import <OpenGLES/ES2/gl.h>
#define glMapBuffer glMapBufferOES
#define glUnmapBuffer glUnmapBufferOES
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
#else           // OpenGL >2.0
#include <OpenGL/gl.h>
#endif

#endif
