//
//  TexturedMesh.hpp
//  D3
//
//  Created by Srđan Rašić on 10/8/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_TexturedMesh_hpp
#define D3_TexturedMesh_hpp

namespace d3 {
    class TexturedMesh : public Drawable {
    public:
        //! Default constructor
        TexturedMesh(shared_ptr<VertexData> index_array,    //!> Index array
                     shared_ptr<VertexData> vertex_array,   //!> Interleaved vertex array
                     unsigned int primitive_type,           //!> Primitive type
                     unsigned int element_count,            //!> Number of elements to draw
                     shared_ptr<Texture> texture = nullptr);//!> Optional texture
        
        //! Virtual destructor
        virtual ~TexturedMesh() {DEBUG_PRINT("Ode mesh")}
        
        //! Sets texture
        void setTexture(shared_ptr<Texture> texture);
        
        //! Sets material
        void setMaterial(shared_ptr<Material> material);
        
    protected:
        //! Drawable:: Called upon drawing
        virtual void preDraw(SceneRenderer & renderer);
        
        //! Drawable:: Draw one occurrance
        virtual void drawOccurrence(SceneRenderer & renderer, SceneNode & node);
        
        //! Drawable:: Called after drawing
        virtual void postDraw(SceneRenderer & renderer);
        
    protected:
        shared_ptr<VertexData> index_array;
        shared_ptr<VertexData> vertex_array;
        shared_ptr<Texture> texture;
        shared_ptr<Material> material;
        
        unsigned int primitive_type;
        unsigned int element_count;
    };
}

#endif
