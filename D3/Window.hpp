//
//  Window.hpp
//  D3
//
//  Created by Srđan Rašić on 9/26/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Window_hpp
#define D3_Window_hpp

namespace d3 {
    /*! Abstract class.
     *  It's main function is to hide platfrom
     *  specific window and context setup and their management.
     */
    class Window {
    protected:
        
    public:
        //! Setup Rendering System's (OpenGL) context
        virtual void setupContext() =0;
        
        //! @return Active window's (view's) width
        virtual unsigned getWidth() =0;
        
        //! @return Active window's (view's) width
        virtual unsigned getHeight() =0;
    };
}

#endif
