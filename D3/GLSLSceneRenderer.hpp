//
//  GLSLSceneRenderer.h
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef _GLSLSceneRenderer_h_
#define _GLSLSceneRenderer_h_

namespace d3 {
    class ResourceManager;
    
    // Renderer with shader support (TBD)
    class GLSLSceneRenderer : public SceneRenderer {        
    public:
        //! Constructor
        GLSLSceneRenderer(ResourceManager * resource_manager, Scene * scene);
        
        //! SceneRenderer:: Draws scene
        virtual void render();
        
        //! SceneRenderer:: Binds texture to device
        virtual void useTexture(shared_ptr<Texture> & texture);
        
        //! SceneRenderer:: Binds program to device
        virtual Program * useProgram(String name);
        
        //! SceneRenderer:: @return Currently bound program
        virtual Program & getProgram();
        
        //! SceneRenderer:: Sets depth mask (true to enable writing to depth buffer, false otherwise)
        virtual void setDepthMask(bool value);
        
        //! SceneRenderer:: True to enable blending, false otherwise
        virtual void setBlend(bool value);
        
        //! SceneRenderer:: Sets blending function coefficients
        virtual void setBlendFunc(unsigned c_src, unsigned c_dst);
        
        //! SceneRenderer:: Binds array to device
        virtual void bindArray(shared_ptr<VertexData> & array);
        
        //! SceneRenderer:: Draws currently bound array
        virtual void drawArrays(unsigned primitive_type, unsigned count);
        
        //! SceneRenderer:: Draws elements indicated by index buffer
        virtual void drawElements(unsigned primitive_type, unsigned count, const shared_ptr<VertexData> & ibo);
        
    protected:
        //! Inserts new program
        void registerProgram(GLSLProgram * program);
        
    protected:
        /* Shader programs */
        GLSLProgram * current_program_;
        std::unordered_map<String, GLSLProgram *> program_map_;
    };
}

#endif