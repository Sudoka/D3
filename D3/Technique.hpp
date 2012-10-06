//
//  Technique.hpp
//  D3
//
//  Created by Srđan Rašić on 10/4/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Technique_hpp
#define D3_Technique_hpp

namespace d3 {
    class Renderable;
    
    /*! Represents rendering technique.
     *  Each Renderable is rendered by a Technique.
     */
    class Technique {
    
    protected:
        Renderable * renderable;
        
        virtual void setupContext() =0;
        virtual void setupVertexData() =0;
        virtual void draw() =0;
        virtual void restoreContext() =0;
        
    public:        
        //! Virtual destructor
        virtual ~Technique() {}
        
        //! @return Curently bound renderable
        Renderable * getRenderable() const { return renderable; }
        
        //! Draw
        virtual void render(Renderable * renderable);
    };
    
#pragma mark Implementation
    inline void Technique::render(Renderable * renderable) {
        this->renderable = renderable;
        
        setupContext();
        setupVertexData();
        draw();
        restoreContext();
    }
}

#endif