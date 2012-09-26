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
    class GLUTWindow : public Window {
    protected:
        
    public:
        GLUTWindow(int *argcp, char **argv, const char * title, unsigned width, unsigned height);
        
        //! Setup Rendering System's (OpenGL) context
        virtual void setupContext();
        
        //! @return Active window's (view's) width
        virtual unsigned getWidth();
        
        //! @return Active window's (view's) width
        virtual unsigned getHeight();
    };
}

#endif
