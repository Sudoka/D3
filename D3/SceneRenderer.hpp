//
//  SceneRenderer.hpp
//  
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _SceneRenderer_hpp
#define _SceneRenderer_hpp

namespace d3 {
    class Drawable;
    
    //! Abstract scene renderer
    class SceneRenderer {
    public:
        //! Creates scene renderer
        SceneRenderer(Scene * scene);
        
        //! Virtual destructor
        virtual ~SceneRenderer();
        
        //! Binds texture to device
        virtual void useTexture(shared_ptr<Texture> & texture) =0;
        
        //! Binds program to device
        virtual Program * useProgram(String name) =0;
        
        //! @return Currently bound program
        virtual Program & getProgram() =0;
        
        //! Sets depth mask (true to enable writing to depth buffer, false otherwise)
        virtual void setDepthMask(bool value) =0;
        
        //! True to enable blending, false otherwise
        virtual void setBlend(bool value) =0;
        
        //! Sets blending function coefficients
        virtual void setBlendFunc(unsigned c_src, unsigned c_dst) =0;
        
        //! Binds array to device
        virtual void bindArray(shared_ptr<VertexData> & array) =0;
        
        //! Draws currently bound array
        virtual void drawArrays(unsigned primitive_type, unsigned count) =0;
        
        //! Draws elements indicated by index buffer
        virtual void drawElements(unsigned primitive_type, unsigned count, const shared_ptr<VertexData> & ibo) =0;
        
        //! Adds drawable to drawable queue
        virtual void registerDrawable(Drawable * drawable);
        
        //! Removes drawable from drawable queue
        virtual void unregisterDrawable(Drawable * drawable);
        
        //! Inserts light in light map
        virtual void registerLight(Light * light);
        
        //! Removes light from map
        virtual void unregisterLight(Light * light);
        
        //! Renders scene
        virtual void render() =0;
        
    protected:
        /* Scene */
        Scene * scene;
        
        /* Renderables */
        std::list<Drawable *> drawable_list;
        
        /* Lights */
        std::unordered_map<Light *, int> light_map;
    };
}

#endif
