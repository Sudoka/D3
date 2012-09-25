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
    // Renderer with shader support (TBD)
    class GLSLRenderer : public SceneRenderer {
    protected:
        //! Enable lights operation
        class GLTurnLightsOperation : public Node::VisitOperation {
            GLSLRenderer * renderer_;
            
        public:
            GLTurnLightsOperation(GLSLRenderer * renderer) : renderer_(renderer) {}
            
            GLSLRenderer * getRenderer() const { return renderer_; }

            virtual void beginNode(Node *node);
            virtual void endNode(Node *node);
        };
        
        //! Rendering operation
        class GLNodeDrawOperation : public Node::VisitOperation {
            GLSLRenderer * renderer_;
            
        public:
            GLNodeDrawOperation(GLSLRenderer * renderer) : renderer_(renderer) {}
            
            GLSLRenderer * getRenderer() const { return renderer_; }
            
            virtual void beginNode(Node *node);
            virtual void endNode(Node *node);
        };
        
    public:
        /* Viewing camera */
        Camera * camera_;
        GLuint buffer_[2];
        /* Shader programs */
        GLProgram * current_program_;
        std::unordered_map<String, GLProgram *> program_map_;
        
        /* Framebuffers */
        std::unordered_map<String, GLuint> framebuffer_map_;
        
    protected:
        //! @return reference to current camera
        SETGET(Camera *, camera_, Camera)
        
        //! Sets program 'program' as current and binds it (and returns it)
         GLProgram *  useProgram(String name);
        
        //! @return Reference to currently active program
        GLProgram * getProgram() const { return current_program_; }

        //! Binds framebuffer
        void useFramebuffer(String name);
        
        //! Inserts new program
        void registerProgram(String name, GLProgram * program);
        
        //! Inserts new framebuffer (id)
        void registerFramebuffer(String name, GLuint id);
        
        //! SceneRenderer derived: reinitialise framebuffers
        virtual void setScreenSize(int width, int height);

        
    public:
        GLSLRenderer(int width, int height);
        
        virtual void render(Scene * scene);
    };
}

#endif