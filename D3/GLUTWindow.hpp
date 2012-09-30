//
//  GLUTWindow.h
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__GLUTWindow__
#define __D3__GLUTWindow__

namespace d3 {
    /* GLUT Window implementation 
     */
    class GLUTWindow : public Window {
    protected:
        /* GLUT callbacks */
        static void glut_display_callback();
        static void glut_idle_callback();
        static void glut_timer_callback(int value);
        static void glut_reshape_callback(int width, int height);
        static void glut_keydown_callback(unsigned char key, int x, int y);
        static void glut_special_keydown_callback(int key, int x, int y);
        static void glut_special_keyup_callback(int key, int x, int y);
        
    public:
        GLUTWindow(String title, unsigned width, unsigned height, Application * application);
        
        //! Setup Rendering System's (OpenGL) context
        virtual void setupContext();
        
        //! @return Active window's (view's) width
        virtual unsigned getWidth();
        
        //! @return Active window's (view's) width
        virtual unsigned getHeight();
        
        //! @return Time in [s] since window creation
        virtual float getTimerValue();
        
        //! Start main loop
        virtual void runLoop();
    };
}

#endif
