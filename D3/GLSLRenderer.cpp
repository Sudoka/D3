//
//  GLSLRenderer.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLSLRenderer.hpp"
#include "OpenGLHeaders.hpp"

namespace d3 {
    
    static int next_free_light_id;
    
    void GLSLRenderer::GLTurnLightsOperation::beginNode(d3::Node *node)
    {        
        Node::Attachment * attachment = node->getAttachedObject();
        if (attachment) {
            PointLight *light = dynamic_cast<PointLight *>(attachment);
            
            if (light != nullptr) {
                String light_tag = String("lightSource[") + next_free_light_id + String("].");
                next_free_light_id++;
                
                /* Get params ref */
                PointLight::LightSourceParameters & param = light->getParametersRef();
                                
                /* Set up shader parameters */
                GLProgram * p = getRenderer()->getProgram();
                
                Vec3 half_vector = getRenderer()->getCamera()->getParent()->getDerivedPosition() - param.position;
                
                glUniform4fv(p->getLocation(light_tag + "ambient"), 1, param.ambient);
                glUniform4fv(p->getLocation(light_tag + "diffuse"), 1, param.diffuse);
                glUniform4fv(p->getLocation(light_tag + "specular"), 1, param.specular);
                glUniform4fv(p->getLocation(light_tag + "position"), 1, param.position);
                glUniform3fv(p->getLocation(light_tag + "halfVector"), 1, half_vector);
                glUniform3fv(p->getLocation(light_tag + "attenuation"), 1, param.attenuation);
            }
        }
    }
    
    void GLSLRenderer::GLTurnLightsOperation::endNode(d3::Node *node)
    {
    }
        
    void GLSLRenderer::GLNodeDrawOperation::beginNode(Node *node)
    {
        if (node->getName() == "Plane")
            glFrontFace(GL_CW);
        else
            glFrontFace(GL_CCW);
        
        glDisable(GL_BLEND);

        /* Draw if there is anythin to draw */
        Renderable * renderable = dynamic_cast<Renderable *>(node->getAttachedObject());
        
        if (renderable != nullptr) {
            /* Get and check geometry */
            const Geometry * g = renderable->getGeometry().get();
            if (g->getVertexArray() == nullptr) return;

            /* Calculate necessary transforms */
            Mat4& model_view = node->getCachedTransformRef();
            Mat3 normal_transform = model_view.inverse().transpose();
            Mat4 camera_transform = getRenderer()->getCamera()->getProjection() * getRenderer()->getCamera()->getTransform();
            
            /* 1. Lighting intensity pass */
            getRenderer()->useFramebuffer("default");
            GLProgram * p = getRenderer()->useProgram("light");
            
            /* Set uniforms */
            glUniformMatrix4fv(p->getLocation("camera_transform"), 1, 1, camera_transform);
            glUniformMatrix4fv(p->getLocation("model_view"), 1, 1, model_view);
            glUniformMatrix3fv(p->getLocation("normal_transform"), 1, 1, normal_transform);
            
            glUniform4fv(p->getLocation("material.ambient"), 1, renderable->getMaterial()->getAmbientColor());
            glUniform4fv(p->getLocation("material.diffuse"), 1, renderable->getMaterial()->getDiffuseColor());
            glUniform4fv(p->getLocation("material.specular"), 1, renderable->getMaterial()->getSpecularColor());
            glUniform1f(p->getLocation("material.shininess"), renderable->getMaterial()->getShininess());
            
            /* Set vertices data */
            glEnableVertexAttribArray(p->getLocation("position"));
            glVertexAttribPointer(p->getLocation("position"), 3, GL_FLOAT, GL_FALSE, g->getVertexPointerStride(), g->getVertexArray().get());
            
            /* Set normal data */
            glEnableVertexAttribArray(p->getLocation("normal"));
            glVertexAttribPointer(p->getLocation("normal"), 3, GL_FLOAT, GL_FALSE, g->getNormalPointerStride(), g->getNormalArray().get());
            
            /* Draw pass */
            if (g->getIndices()) {
                glDrawElements(g->getGeometryType(),
                               g->getSize(),
                               GL_UNSIGNED_INT,
                               g->getIndices().get());
            } else {
                glDrawArrays(g->getGeometryType(), 0, g->getSize());
            }
            
            glDisableVertexAttribArray(p->getLocation("normal"));
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_DST_COLOR, GL_ZERO);

            /* 2. Texture pass */
            if (renderable->getTexture() != nullptr && g->getTexCoordArray()) {
                GLProgram * p = getRenderer()->useProgram("ambient");
                
                /* Set uniforms */
                glUniformMatrix4fv(p->getLocation("camera_transform"), 1, 1, camera_transform);
                glUniformMatrix4fv(p->getLocation("model_view"), 1, 1, model_view);
                
                glEnable(GL_TEXTURE_2D);
                glActiveTexture(GL_TEXTURE0);
                renderable->getTexture()->bind();
                glUniform1i(p->getLocation("texture_sampler"), 0);
                
                /* Set vertices data */
                glEnableVertexAttribArray(p->getLocation("position"));
                glVertexAttribPointer(p->getLocation("position"), 3, GL_FLOAT, GL_FALSE, g->getVertexPointerStride(), g->getVertexArray().get());

                /* Set texture data */
                glEnableVertexAttribArray(p->getLocation("tex_coord"));
                glVertexAttribPointer(p->getLocation("tex_coord"), 2, GL_FLOAT, GL_FALSE, g->getTexCoordPointerStride(),  g->getTexCoordArray().get());
                
                /* Draw  pass */
                if (g->getIndices()) {
                    glDrawElements(g->getGeometryType(),
                                   g->getSize(),
                                   GL_UNSIGNED_INT,
                                   g->getIndices().get());
                } else {
                    glDrawArrays(g->getGeometryType(), 0, g->getSize());
                }
                
                glDisableVertexAttribArray(p->getLocation("tex_coord"));
                glDisable(GL_TEXTURE_2D);
            }
            
            glDisable(GL_BLEND);
        }
    }
    
    void GLSLRenderer::GLNodeDrawOperation::endNode(Node *node)
    {
    }
    
    GLSLRenderer::GLSLRenderer(int width, int height) : SceneRenderer(width, height)
    {
        /* Setup OpenGL initial settings */
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        
        /* Initialize shaders */
        registerProgram("light", new GLProgram("/Users/srdan/Development/D3/D3/light.vsh", "/Users/srdan/Development/D3/D3/light.fsh", YES));
        registerProgram("texture", new GLProgram("/Users/srdan/Development/D3/D3/texture.vsh", "/Users/srdan/Development/D3/D3/texture.fsh", YES));
        registerProgram("ambient", new GLProgram("/Users/srdan/Development/D3/D3/ambient.vsh", "/Users/srdan/Development/D3/D3/ambient.fsh", YES));
        
        /* Initialise framebuffers */
        registerFramebuffer("default", 0);
        
        GLuint fbo; glGenFramebuffers(1, &fbo);
        registerFramebuffer("auxiliary", fbo);
        
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenTextures(1, &buffer_[0]);
        glBindTexture(GL_TEXTURE_2D, buffer_[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer_[0], 0);
        
        glGenRenderbuffers(1, &buffer_[1]);
        glBindRenderbuffer(GL_RENDERBUFFER, buffer_[1]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer_[1]);
        
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        assert(status == GL_FRAMEBUFFER_COMPLETE);
    }
    
    void GLSLRenderer::render(Scene *scene)
    {        
        // Clear framebuffer
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        
        glDepthMask(GL_TRUE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //glBindFramebuffer(GL_FRAMEBUFFER, 1);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Setup viewport
        #ifndef _IOS_
        glViewport(0, 0, getScreenWidth(), getScreenHeight()); // comment this line for iOS
        #endif
        
        // Get and update camera if window has been resized
        camera_ = scene->getCamera();
        getCamera()->setAspectRatio(getScreenWidth()/(float)getScreenHeight());
        
        // Setup lights
        useProgram("light");
        next_free_light_id = 0;
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new GLTurnLightsOperation(this)));
        // TODO: setun number of lights
        
        // Render scene
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new GLNodeDrawOperation(this)));
        
        // Finish
        glFinish();
    }
    
     GLProgram *  GLSLRenderer::useProgram(String name)
    {
        current_program_ = program_map_[name];
        current_program_->bind();
        return current_program_;
    }
    
    void GLSLRenderer::useFramebuffer(String name)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_map_[name]);
    }
    
    void GLSLRenderer::registerProgram(String name, GLProgram * program)
    {
        program_map_[name] = program;
    }
    
    void GLSLRenderer::registerFramebuffer(String name, GLuint id)
    {
        framebuffer_map_[name] = id;
    }
    
    void GLSLRenderer::setScreenSize(int width, int height) {
        screen_width_ = width;
        screen_height_ = height;
    }
}