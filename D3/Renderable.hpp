//
//  Renderable.hpp
//  D3
//
//  Created by Srđan Rašić on 10/4/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_Renderable_hpp
#define D3_Renderable_hpp

namespace d3 {
    /*! Represents any renderable entity.
     *  Each renderable is rendered by Technique.
     */
    class Renderable {
    public:
        
    public:       
        //! Virtual destructor
        virtual ~Renderable() {}
        
        //! Vertex data
        virtual std::list<VertexData *> getVertexData() =0;
        
        //! Index data
        virtual VertexData * getIndexData() { return nullptr; };
        
        //! Number of elements
        virtual unsigned getElementCount() =0;
        
        //! Primitive type
        virtual unsigned getPrimitiveType() =0;
        
        //! Who renders me?
        virtual Technique * getTechnique() =0;
        
        //! Renders object
        virtual void render() { getTechnique()->render(this); }
    };
}

#endif
