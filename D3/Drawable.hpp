//
//  Drawable.hpp
//  D3
//
//  Created by Srđan Rašić on 10/8/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Drawable_hpp
#define D3_Drawable_hpp

namespace d3 {
    //! Represents Drawable object
    class Drawable : public Occurable {
    public:
        //! Default constructor. Registers drawable to Renderer.
        Drawable();
        
        //! Virtual destructor. Unregisters drawable from Renderer.
        virtual ~Drawable();
        
        //! Draws all occurances
        virtual void _drawOccurrences(SceneRenderer & renderer);
        
    protected:
        //! Called upon drawing
        virtual void preDraw(SceneRenderer & renderer) {}
        
        //! Draw one occurrance
        virtual void drawOccurrence(SceneRenderer & renderer, SceneNode & node) =0;
        
        //! Called after drawing
        virtual void postDraw(SceneRenderer & renderer) {}
    };
}

#endif