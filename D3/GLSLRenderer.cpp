//
//  GLSLRenderer.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLSLRenderer.hpp"
#include "OpenGLHeaders.hpp"
#include "ResourceManager.hpp"

namespace d3 {
    
    static int next_free_light_id;
    
    void GLSLRenderer::GLTurnLightsOperation::beginNode(d3::Node *node)
    {        
        Node::Attachment * attachment = node->getAttachedObject();
        if (attachment) {
            PointLight *light = dynamic_cast<PointLight *>(attachment);
            
            if (light != nullptr) {
                String light_tag = String("light_source[") + next_free_light_id + String("].");
                next_free_light_id++;
                
                /* Get params ref */
                PointLight::LightSourceParameters & param = light->getParametersRef();
                                
                /* Set up shader parameters */
                GLProgram * p = getRenderer()->getProgram();
                
                param.position = getRenderer()->getCamera()->getTransform() * param.position;
                Vec3 half_vector = getRenderer()->getCamera()->getParent()->getDerivedPosition() - param.position;
                
                glUniform4fv(p->getLocation(light_tag + "ambient"), 1, param.ambient);
                glUniform4fv(p->getLocation(light_tag + "diffuse"), 1, param.diffuse);
                glUniform4fv(p->getLocation(light_tag + "specular"), 1, param.specular);
                glUniform4fv(p->getLocation(light_tag + "position"), 1, param.position);
                glUniform3fv(p->getLocation(light_tag + "half_vector"), 1, half_vector);
                glUniform3fv(p->getLocation(light_tag + "spot_direction"), 1, param.spotDirection);
                glUniform1f(p->getLocation(light_tag + "spot_exponent"), param.spotExponent);
                glUniform1f(p->getLocation(light_tag + "spot_cutoff"), param.spotCutoff);
                glUniform1f(p->getLocation(light_tag + "spot_cos_cutoff"), param.spotCosCutoff);
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
            Mat4 model_view = getRenderer()->getCamera()->getTransform() * node->getCachedTransformRef();
            Mat4 model_view_projection = getRenderer()->getCamera()->getProjection() * model_view;
            Mat3 normal_matrix = model_view.inverse().transpose();
            Mat4 texture_matrix;
            
            /* 1. Lighting intensity pass */
            //getRenderer()->useFramebuffer("default");
            GLProgram * p = getRenderer()->useProgram("ff");
            
            p->setParamMat4("model_view_matrix", model_view);
            p->setParamMat4("model_view_projection_matrix", model_view_projection);
            p->setParamMat4("texture_matrix", texture_matrix);
            p->setParamMat3("normal_matrix", normal_matrix);
            
            p->setParamVec4("material.ambient", renderable->getMaterial()->getAmbientColor());
            p->setParamVec4("material.diffuse", renderable->getMaterial()->getDiffuseColor());
            p->setParamVec4("material.specular", renderable->getMaterial()->getSpecularColor());
            p->setParamFloat("material.shininess", renderable->getMaterial()->getShininess());
            
            Vec4 ambient_color(0.1, 0.1, 0.1, 1.0);
            p->setParamVec4("scene_ambient_color", ambient_color);
            
            p->setParamInt("num_of_enabled_lights", next_free_light_id);
            p->setParamBool("need_local_viewer", 1);
            
            p->enableFloatArrayPtr("in_vertex", 3, g->getVertexPointerStride(), g->getVertexArray().get());
            p->enableFloatArrayPtr("in_normal", 3, g->getNormalPointerStride(), g->getNormalArray().get());
            
            if (renderable->getTexture() != nullptr && g->getTexCoordArray()) {
                p->setParamBool("texture_mask", 0);
                p->enableFloatArrayPtr("in_texcoord", 3, g->getTexCoordPointerStride(), g->getTexCoordArray().get());
                
                glEnable(GL_TEXTURE_2D);
                renderable->getTexture()->bind();
            } else {
                p->setParamBool("texture_mask", 1);
            }
            
            if (g->getIndices()) {
                glDrawElements(g->getGeometryType(),
                               g->getSize(),
                               GL_UNSIGNED_INT,
                               g->getIndices().get());
            } else {
                glDrawArrays(g->getGeometryType(), 0, g->getSize());
            }
            
            glDisable(GL_TEXTURE_2D);
            p->disableArrayPtr("in_vertex");
            p->disableArrayPtr("in_normal");
            p->disableArrayPtr("in_texcoord");
        }
        
        ParticleEmitter * emitter = dynamic_cast<ParticleEmitter *>(node->getAttachedObject());
        
        if (emitter != nullptr) {
            /* Calculate necessary transforms */
            Mat4 model_view = getRenderer()->getCamera()->getTransform() * node->getCachedTransformRef();
            Mat4 model_view_projection = getRenderer()->getCamera()->getProjection() * model_view;
            
            ParticleSystem::Emitter * e = emitter->getEmitter().get();
            
            GLProgram * p = getRenderer()->useProgram("ps");
            
            p->setParamMat4("model_view_projection_matrix", model_view_projection);
            p->setParamFloat("point_size_factor", getRenderer()->getScreenHeight() / 512.0f);
                     
            int stride = sizeof(ParticleSystem::Particle);
            p->enableFloatArrayPtr("in_vertex", 3, stride, (e->particle_array->position));
            p->enableFloatArrayPtr("in_color", 4, stride, (e->particle_array->color));
            p->enableFloatArrayPtr("in_point_size", 1, stride, &(e->particle_array->size));
            
#ifndef _IOS_
            glEnable(GL_POINT_SPRITE);
            glEnable(GL_PROGRAM_POINT_SIZE_EXT);
#endif
            glEnable(GL_TEXTURE_2D);
            emitter->getTexture()->bind();
            
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            
            glDrawArrays(GL_POINTS, 0, e->particle_count);
            
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_BLEND);
#ifndef _IOS_
            glDisable(GL_POINT_SPRITE);
            glDisable(GL_PROGRAM_POINT_SIZE_EXT);
#endif
            glDisable(GL_TEXTURE_2D);
            p->disableArrayPtr("in_vertex");
            p->disableArrayPtr("in_color");
            p->disableArrayPtr("in_point_size");
        }
    }
    
    void GLSLRenderer::GLNodeDrawOperation::endNode(Node *node)
    {
    }
    
    GLSLRenderer::GLSLRenderer(ResourceManager * resource_manager, int width, int height) : SceneRenderer(width, height)
    {
        /* Setup OpenGL initial settings */
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        
        registerProgram(new GLProgram("ff", resource_manager->loadShader("ff_shader.vsh", "ff_shader.vsh", D3_VERTEX_PROGRAM),
                                            resource_manager->loadShader("ff_shader.fsh", "ff_shader.fsh", D3_FRAGMENT_PROGRAM),
                                            YES));
        
        registerProgram(new GLProgram("ps", resource_manager->loadShader("particle_system.vsh", "particle_system.vsh", D3_VERTEX_PROGRAM),
                                            resource_manager->loadShader("particle_system.fsh", "particle_system.fsh", D3_FRAGMENT_PROGRAM),
                                            YES));
    }
    
    void GLSLRenderer::render(Scene * scene)
    {        
        // Clear framebuffer
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        
        //glDepthMask(GL_TRUE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // Setup viewport
        glViewport(0, 0, getScreenWidth(), getScreenHeight());
        
        // Get and update camera if window has been resized
        camera_ = scene->getCamera();
        getCamera()->setAspectRatio(getScreenWidth() / (float) getScreenHeight());
        
        // Setup lights
        useProgram("ff");
        next_free_light_id = 0;
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new GLTurnLightsOperation(this)));
        
        // Render scene
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new GLNodeDrawOperation(this)));
    }
    
    GLProgram *  GLSLRenderer::useProgram(String name)
    {
        current_program_ = program_map_[name];
        current_program_->bind();
        
        return current_program_;
    }
    
    void GLSLRenderer::useFramebuffer(String name)
    {
        //glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_map_[name]);
    }
    
    void GLSLRenderer::registerProgram(GLProgram * program)
    {
        program_map_[program->getName()] = program;
    }
    
    void GLSLRenderer::registerFramebuffer(String name, GLuint id)
    {
        framebuffer_map_[name] = id;
    }
}