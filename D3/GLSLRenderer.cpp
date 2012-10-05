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
#include "SceneNode.hpp"

namespace d3 {
    
    static int next_free_light_id;
    
    GLSLRenderer::GLSLRenderer(ResourceManager * resource_manager, int width, int height) : SceneRenderer(width, height)
    {
        /* Setup OpenGL initial settings */
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        
        /* Load programs */
        registerProgram(new GLProgram("BlinnPhongShader",
                                      resource_manager->loadShader("BlinnPhongShader.vsh", "BlinnPhongShader.vsh", D3_VERTEX_PROGRAM),
                                      resource_manager->loadShader("BlinnPhongShader.fsh", "BlinnPhongShader.fsh", D3_FRAGMENT_PROGRAM),
                                      YES));
        
        registerProgram(new GLProgram("ParticleShader",
                                      resource_manager->loadShader("ParticleShader.vsh", "ParticleShader.vsh", D3_VERTEX_PROGRAM),
                                      resource_manager->loadShader("ParticleShader.fsh", "ParticleShader.fsh", D3_FRAGMENT_PROGRAM),
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
        scene->getCamera()->setAspectRatio(getScreenWidth() / (float) getScreenHeight());
        
        // Setup lights
        GLProgram * p = useProgram("BlinnPhongShader");
        next_free_light_id = 0;

        for (SceneNode * node : scene->getLightSourcesRef()) {
            PointLight *light = dynamic_cast<PointLight *>(node->getAttachedObject().get());
            assert (light != nullptr);
            
            String light_tag = String("light_source[") + next_free_light_id + String("].");
            next_free_light_id++;
            
            /* Get params ref */
            PointLight::LightSourceParameters & param = light->getParametersRef();
            
            /* Set up shader parameters */
            Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();
            Mat4 normal_matrix = model_view.inverse().transpose();
            
            Vec4 position = model_view * param.position;
            Vec3 spotDirection = normal_matrix * param.spotDirection;
            
            Vec3 half_vector = node->getScene()->getCamera()->getParent()->getDerivedPosition() - param.position;
            
            p->setParamVec4(light_tag + "ambient", param.ambient);
            p->setParamVec4(light_tag + "diffuse", param.diffuse);
            p->setParamVec4(light_tag + "specular", param.specular);
            p->setParamVec4(light_tag + "position", position);
            p->setParamVec3(light_tag + "half_vector", half_vector);
            p->setParamVec3(light_tag + "spot_direction", spotDirection);
            p->setParamFloat(light_tag + "spot_exponent", param.spotExponent);
            p->setParamFloat(light_tag + "spot_cutoff", param.spotCutoff);
            p->setParamFloat(light_tag + "spot_cos_cutoff", param.spotCosCutoff);
            p->setParamVec3(light_tag + "attenuation", param.attenuation);
        }
        
        // Render scene
        for (SceneNode * node : scene->getRenderablesRef()) {
            if (node->getName() == "Plane")
                glFrontFace(GL_CW);
            else
                glFrontFace(GL_CCW);
            
            glDisable(GL_BLEND);
            
            /* Draw renderable */
            TexturedGeometry * renderable = dynamic_cast<TexturedGeometry *>(node->getAttachedObject().get());
            if (renderable != nullptr) {
                /* Get and check geometry */
                const Geometry * g = renderable->getGeometry().get();
                if (g->getVertexArray() == nullptr) return;
                
                /* Calculate necessary transforms */
                Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();
                Mat4 model_view_projection = node->getScene()->getCamera()->getProjection() * model_view;
                Mat3 normal_matrix = model_view.inverse().transpose();
                Mat4 texture_matrix;
                
                GLProgram * p = useProgram("BlinnPhongShader");
                
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
        }
        
        /* Draw Particle Emitters */
//        for (SceneNode * node : scene->getEmittersRef()) {
//            shared_ptr<BillboardParticleEmitter> emitter = node->getAttachedEmitter();
//            
//            Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();
//            Mat4 model_view_projection = node->getScene()->getCamera()->getProjection() * model_view;
//            
//        }
        
        
        
//        for (SceneNode * node : scene->getEmittersRef()) {
//
//            shared_ptr<ParticleEmitter> emitter = node->getAttachedEmitter();
//            if (emitter != nullptr) {
//                /* Calculate necessary transforms */
//                Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();
//                Mat4 model_view_projection = node->getScene()->getCamera()->getProjection() * model_view;
//                
//                ParticleSystem::Emitter * e = emitter->getEmitter().get();
//                
//                GLProgram * p = useProgram("ParticleShader");
//                
//                p->setParamMat4("model_view_matrix", model_view);
//                p->setParamMat4("model_view_projection_matrix", model_view_projection);
//                p->setParamFloat("point_size_factor", getScreenHeight() / 512.0f);
//                
//                int stride = sizeof(ParticleSystem::Particle);
//                p->enableFloatArrayPtr("in_vertex", 3, stride, (e->particle_array->position));
//                p->enableFloatArrayPtr("in_color", 4, stride, (e->particle_array->color));
//                p->enableFloatArrayPtr("in_point_size", 1, stride, &(e->particle_array->size));
//                
//#ifndef _IOS_
//                glEnable(GL_POINT_SPRITE);
//                glEnable(GL_PROGRAM_POINT_SIZE_EXT);
//#endif
//                glEnable(GL_TEXTURE_2D);
//                emitter->getTexture()->bind();
//                
//                glDepthMask(GL_FALSE);
//                glEnable(GL_BLEND);
//                glBlendFunc(GL_ONE, GL_ONE);
//                
//                glDrawArrays(GL_POINTS, 0, e->particle_count);
//                
//                glDepthMask(GL_TRUE);
//                glDisable(GL_BLEND);
//#ifndef _IOS_
//                glDisable(GL_POINT_SPRITE);
//                glDisable(GL_PROGRAM_POINT_SIZE_EXT);
//#endif
//                glDisable(GL_TEXTURE_2D);
//                p->disableArrayPtr("in_vertex");
//                p->disableArrayPtr("in_color");
//                p->disableArrayPtr("in_point_size");
//            }
//        }
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
    
    void GLSLRenderer::registerProgram(GLProgram * program)
    {
        program_map_[program->getName()] = program;
    }
    
    void GLSLRenderer::registerFramebuffer(String name, GLuint id)
    {
        framebuffer_map_[name] = id;
    }
}