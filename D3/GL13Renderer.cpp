//
//  GLGraphRenderer.cpp
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GL13Renderer.hpp"

#ifdef _IOS_
#import <OpenGLES/ES1/gl.h>
#else
#include <OpenGL/gl.h>
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace d3 {        
    GL13Renderer::GL13Renderer(int width, int height) : SceneRenderer(width, height)
    {        
        // Setup OpenGL initial settings
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable (GL_LIGHTING);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Vec4(0.1, 0.1, 0.1, 1.0));
        glEnable(GL_NORMALIZE);
    }
    
    void GL13Renderer::render(Scene *scene)
    {
        // Get and update camera if window has been resized
        Camera * camera = scene->getCamera().get();
        camera->setAspectRatio(getScreenWidth()/(float)getScreenHeight());
        
        // Clear framebuffer
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Setup viewport
        glViewport(0, 0, getScreenWidth(), getScreenHeight()); // comment this line for iOS
        
        // Setup projection
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(camera->getProjection());
        
        // Setup camera view point
        glMatrixMode(GL_MODELVIEW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        // Setup lights ids
        int next_free_light_id = 0;
        for (SceneNode * node : scene->getLightSourcesRef()) {
            PointLight *light = dynamic_cast<PointLight *>(node->getAttachedObject().get());
            assert (light != nullptr);

            /* Get params ref */
            PointLight::LightSourceParameters & param = light->getParametersRef();
            
            /* Set up shader parameters */
            Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();
            glLoadMatrixf(model_view);
            
            param.position = Vec4(0, 0, 0, 1);
            
            GLuint light_id = GL_LIGHT0 + next_free_light_id;
            glEnable(light_id);
            glLightfv(light_id, GL_POSITION, param.position);
            glLightfv(light_id, GL_AMBIENT, param.ambient);
            glLightfv(light_id, GL_DIFFUSE, param.diffuse);
            glLightfv(light_id, GL_SPECULAR, param.specular);
            glLightf(light_id, GL_CONSTANT_ATTENUATION, param.attenuation.x);
            glLightf(light_id, GL_LINEAR_ATTENUATION, param.attenuation.y);
            glLightf(light_id, GL_QUADRATIC_ATTENUATION, param.attenuation.z);
            glLightf(light_id, GL_SPOT_CUTOFF, param.spotCutoff);
            glLightf(light_id, GL_SPOT_EXPONENT, param.spotExponent);
            glLightfv(light_id, GL_SPOT_DIRECTION, param.spotDirection);
            
            next_free_light_id++;
        }

        // Render scene
        for (SceneNode * node : scene->getRenderablesRef()) {            
            //glDisable(GL_BLEND);
            
            /* Draw renderable */
            TexturedGeometry * renderable = dynamic_cast<TexturedGeometry *>(node->getAttachedObject().get());
            if (renderable != nullptr) {
                /* Get and check geometry */
                const Geometry * g = renderable->getGeometry().get();
                if (g->getVertexArray() == nullptr) return;
                
                /* Calculate necessary transforms */
                Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();
                glLoadMatrixf(model_view);
                
                glMaterialf(GL_FRONT, GL_SHININESS, renderable->getMaterial()->getShininess());
                glMaterialfv(GL_FRONT, GL_AMBIENT, renderable->getMaterial()->getAmbientColor());
                glMaterialfv(GL_FRONT, GL_DIFFUSE, renderable->getMaterial()->getDiffuseColor());
                glMaterialfv(GL_FRONT, GL_SPECULAR, renderable->getMaterial()->getSpecularColor());
                
                if (g->getColorArray()) {
                    glEnable(GL_COLOR_MATERIAL);
                    glEnableClientState(GL_COLOR_ARRAY);
                    glColorPointer(4, GL_FLOAT, g->getColorPointerStride(), g->getColorArray().get());
                }
                
                if (g->getNormalArray()) {
                    glEnableClientState(GL_NORMAL_ARRAY);
                    glNormalPointer(GL_FLOAT, g->getNormalPointerStride(), g->getNormalArray().get());
                }
                
                if (renderable->getTexture() != nullptr && g->getTexCoordArray()) {
                    glEnable(GL_TEXTURE_2D);
                    renderable->getTexture()->bind();
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    glTexCoordPointer(2, GL_FLOAT, g->getTexCoordPointerStride(), g->getTexCoordArray().get());
                }
                
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, g->getVertexPointerStride(), g->getVertexArray().get());
                
                if (g->getIndices()) {
                    glDrawElements(g->getGeometryType(),
                                   g->getSize(),
                                   GL_UNSIGNED_INT,
                                   g->getIndices().get());
                } else {
                    glDrawArrays(g->getGeometryType(), 0, g->getSize());
                }
                
                // undo
                glDisableClientState(GL_VERTEX_ARRAY);
                
                if (g->getColorArray()) {
                    glDisableClientState(GL_COLOR_ARRAY);
                    glDisable(GL_COLOR_MATERIAL);
                }
                
                if (g->getNormalArray()) {
                    glDisableClientState(GL_NORMAL_ARRAY);
                }
                
                if (renderable->getTexture() != nullptr && g->getTexCoordArray()) {
                    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }

        for (SceneNode * node : scene->getEmittersRef()) {
            shared_ptr<BillboardParticleEmitter> emitter = node->getAttachedEmitter();
            
            glMatrixMode(GL_MODELVIEW);
            Mat4 model_view = node->getScene()->getCamera()->getTransform() * node->getCachedTransformRef();

//            for(int i=0; i<3; i++ )
//                for(int j=0; j<3; j++ ) {
//                    if ( i==j )
//                        model_view.m[i*4+j] = 1.0;
//                    else
//                        model_view.m[i*4+j] = 0.0;
//                }
            
            glLoadMatrixf(model_view);
                        
            //GLsizei color_offset = sizeof(BillboardParticleEmitter::VertexGeometryTemplate);
            //GLsizei texcoord_offset = color_offset + sizeof(BillboardParticleEmitter::VertexTexcoordTemplate);
            
            //glBindBuffer(GL_ARRAY_BUFFER, emitter->vertex_buffer);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDepthMask(GL_FALSE);
            glDisable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);
            
            glBindBuffer(GL_ARRAY_BUFFER, emitter->vertex_buffer);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, sizeof(Vec3), 0);
            
            glEnable(GL_TEXTURE_2D);
            emitter->properties->texture->bind();
            glBindBuffer(GL_ARRAY_BUFFER, emitter->vertex_texcoord_buffer);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, sizeof(Vec3), 0);
            
            
            glBindBuffer(GL_ARRAY_BUFFER, emitter->vertex_color_buffer);
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(int), 0);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, emitter->element_buffer);
            glDrawElements(GL_TRIANGLE_STRIP, emitter->particle_count * 6, GL_UNSIGNED_SHORT, 0);
            
            // undo
            glDisableClientState(GL_VERTEX_ARRAY);
            
            glDisableClientState(GL_COLOR_ARRAY);
            glDisable(GL_COLOR_MATERIAL);
            
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_LIGHTING);
            glDisable(GL_BLEND);
            glDepthMask(GL_TRUE);

        }
    }
}