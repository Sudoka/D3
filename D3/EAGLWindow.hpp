//
//  UIViewWindow.h
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__EAGLWindow__
#define __D3__EAGLWindow__

namespace d3 {
    /*! iOS OpenGL ES Window and View
     *  implementation.
     */
    class EAGLWindow : public Window {
    protected:
        
    public:
        EAGLWindow(Application * application);
        
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
        
        //! @return Systems' window or view object (wrapped stuff)
        virtual void * getSystemObject();
    };
}

#endif 