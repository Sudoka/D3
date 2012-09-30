//
//  GLSLRenderer.h
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef ____GLSLRenderer__
#define ____GLSLRenderer__

namespace d3 {
    class ResourceManager;
    
    // Renderer with shader support (TBD)
    class GLSLRenderer : public SceneRenderer {
    protected:              
    public:
        /* Shader programs */
        GLProgram * current_program_;
        std::unordered_map<String, GLProgram *> program_map_;
        
        /* Framebuffers */
        std::unordered_map<String, GLuint> framebuffer_map_;
        
    protected:        
        //! Sets program 'program' as current and binds it (and returns it)
         GLProgram * useProgram(String name);
        
        //! Inserts new program
        void registerProgram(GLProgram * program);
        
        //! @return Reference to currently active program
        GLProgram * getProgram() const { return current_program_; }

        //! Binds framebuffer
        void useFramebuffer(String name);
        
        //! Inserts new framebuffer (id)
        void registerFramebuffer(String name, GLuint id);
        
    public:
        //! Constructor
        GLSLRenderer(ResourceManager * resource_manager, int width, int height);
        
        //! Draws scene
        virtual void render(Scene * scene);
    };
}

#endif