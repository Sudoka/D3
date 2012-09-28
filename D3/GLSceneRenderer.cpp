//
//  GLGraphRenderer.cpp
//  
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLSceneRenderer.hpp"
#include "OpenGLHeaders.hpp"

namespace d3 {
    
    void renderParticleEmitter(ParticleEmitter * particle_emitter)
    {
    }
    
    static int next_free_light_id_;
    
    static int setupPointLight(PointLight *light)
    {
        int light_id = GL_LIGHT0 + next_free_light_id_++;
        
        glEnable(light_id);
        
        Vec3 p = light->getParent()->getDerivedPosition();
        glLightfv(light_id, GL_POSITION, Vec4(p.x, p.y, p.z, 1.0));
        glLightfv(light_id, GL_AMBIENT, light->getAmbientColor());
        glLightfv(light_id, GL_DIFFUSE, light->getDiffuseColor());
        glLightfv(light_id, GL_SPECULAR, light->getSpecularColor());
        glLightf(light_id, GL_CONSTANT_ATTENUATION, light->getAttenuation().x);
        glLightf(light_id, GL_LINEAR_ATTENUATION, light->getAttenuation().y);
        glLightf(light_id, GL_QUADRATIC_ATTENUATION, light->getAttenuation().z);
        
        return light_id;
    }
    
    static void setupSpotLight(PointLight *light)
    {
        int light_id = setupPointLight(light);
        
        glLightf(light_id, GL_SPOT_CUTOFF, ((SpotLight*)light)->getCutoff());
        glLightf(light_id, GL_SPOT_EXPONENT, ((SpotLight*)light)->getExponent());
        //glLightfv(light_id, GL_SPOT_DIRECTION, ((SpotLight*)light)->getDirection());
    }
    
    static void setupDirectionalLight(PointLight *light)
    {
        int light_id = setupPointLight(light);
        
        Vec3 p = ((DirectionalLight*)light)->getDirection();
        glLightfv(light_id, GL_POSITION, Vec4(p.x, p.y, p.z, 0.0));
    }
    
    void GLSceneRenderer::GLTurnLightsOperation::beginNode(d3::Node *node)
    {
        Node::Attachment * attachment = node->getAttachedObject();
        if (attachment) {
            
            PointLight *light;
            
            if ((light = dynamic_cast<SpotLight *>(attachment)) != nullptr) {
                setupSpotLight(light);
                return;
            } else if ((light = dynamic_cast<DirectionalLight *>(attachment)) != nullptr) {
                setupDirectionalLight(light);
                return;
            } else if ((light = dynamic_cast<PointLight *>(attachment)) != nullptr) {
                setupPointLight(light);
                return;
            }
        }
    }
    
    GLSceneRenderer::GLNodeDrawOperation::GLNodeDrawOperation(GLSceneRenderer * renderer) : renderer_(renderer)
    {
    }
    
    GLSceneRenderer * GLSceneRenderer::GLNodeDrawOperation::getRenderer() const
    {
        return renderer_;
    }
    
    void GLSceneRenderer::GLNodeDrawOperation::beginNode(Node *node)
    {
        Mat4 modelview_matrix = getRenderer()->modelview_matrix_stack_.top();
        
        Vec3 position = node->getPosition();
        Vec3 scale = node->getScale();
        Quat orientation = node->getOrientation().normalized();
        Vec3 axis = orientation.getRotationAxis().unit();
        float angle = orientation.getRotationAngle();
        
        Mat4 translation = getTranslationMat4(position);
        Mat4 scaling = getScalingMat4(scale);
        Mat4 rotation = getRotationMat4(axis, angle);
        
        modelview_matrix = modelview_matrix * ((translation * scaling) * rotation);
        glLoadMatrixf(modelview_matrix.transpose());
        getRenderer()->modelview_matrix_stack_.push(modelview_matrix);
        
//        glPushMatrix();
//        Mat4 transform = (translation * rotation) * scaling;
//        glMultMatrixf(transform.transpose());
        
//        glTranslatef(position.x, position.y, position.z);
//        glRotatef(angle / kPiOver180, axis.x, axis.y, axis.z);
//        glScalef(scale.x, scale.y, scale.z);
        
        // draw attached object
        Node::Attachment * attachment = node->getAttachedObject();
        if (attachment) {
            // If particles system
            ParticleEmitter * emitter;
            if ((emitter = dynamic_cast<ParticleEmitter *>(attachment)) != nullptr) {
                renderParticleEmitter(emitter);
                return;
            }
            
            // if renderable
            if (attachment->isRenderable()) {
                Renderable * r = (Renderable*)attachment;
                
                if (!r->getGeometry())
                    return;
                
                shared_ptr<Geometry> g = r->getGeometry();
                
                if (g->getVertexArray() != nullptr) {
                    if (r->getMaterial() != nullptr) {
                        glMaterialf(GL_FRONT, GL_SHININESS, r->getMaterial()->getShininess());
                        glMaterialfv(GL_FRONT, GL_AMBIENT, r->getMaterial()->getAmbientColor());
                        glMaterialfv(GL_FRONT, GL_DIFFUSE, r->getMaterial()->getDiffuseColor());
                        glMaterialfv(GL_FRONT, GL_SPECULAR, r->getMaterial()->getSpecularColor());
                        
                    }
                    
                    if (g->getColorArray()) {
                        glEnable(GL_COLOR_MATERIAL);
                        glEnableClientState(GL_COLOR_ARRAY);
                        glColorPointer(4, GL_FLOAT, g->getColorPointerStride(), g->getColorArray().get());    //FIX size
                    }
                    
                    if (g->getNormalArray()) {
                        glEnableClientState(GL_NORMAL_ARRAY);
                        glNormalPointer(GL_FLOAT, g->getNormalPointerStride(), g->getNormalArray().get());
                    }
                    
                    if (r->getTexture() != nullptr && g->getTexCoordArray()) {
                        glEnable(GL_TEXTURE_2D);
                        r->getTexture()->bind();
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
                    if (g->getColorArray()) {
                        glDisableClientState(GL_COLOR_ARRAY);
                        glDisable(GL_COLOR_MATERIAL);
                    }
                    
                    if (g->getNormalArray()) {
                        glDisableClientState(GL_NORMAL_ARRAY);
                    }
                    
                    if (r->getTexture() != nullptr && g->getTexCoordArray()) {
                        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                        glDisable(GL_TEXTURE_2D);
                    }
                }
            }
        }
        
        // draw bb
        if (node->getBoundingBoxVisibility()) {
            glDisable(GL_LIGHTING);
            
            Vec3 box = node->getBoundingBox().size;
            shared_ptr<Geometry> g = GeometryFactory::createBoundingBox(box);   // TODO: Optimize
            
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, g->getVertexPointerStride(), g->getVertexArray().get());
            
            glDrawElements(g->getGeometryType(),
                           g->getSize(),
                           GL_UNSIGNED_INT,
                           g->getIndices().get());
            // disable VA
            glEnable(GL_LIGHTING);
        }
    }
    
    void GLSceneRenderer::GLNodeDrawOperation::endNode(Node *node)
    {
        //glPopMatrix();
        getRenderer()->modelview_matrix_stack_.pop();
    }
    
    GLSceneRenderer::GLSceneRenderer(int width, int height) : SceneRenderer(width, height)
    {        
        // Setup OpenGL initial settings
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable (GL_LIGHTING);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Vec4(0.2, 0.2, 0.2, 1.0));
        //glEnable(GL_CULL_FACE);
        glEnable(GL_NORMALIZE);
        
        glPointSize(1.0);
        
    }
    
    void GLSceneRenderer::render(Scene *scene)
    {
        // Get and update camera if window has been resized
        Camera * camera = scene->getCamera();
        camera->setAspectRatio(getScreenWidth()/(float)getScreenHeight());
        
        // Clear framebuffer
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Setup viewport
        #ifndef _IOS_
        glViewport(0, 0, getScreenWidth(), getScreenHeight()); // comment this line for iOS
        #endif
        
        // Setup projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        Frustum frustum = camera->getFrustum();
        glFrustum(frustum.left, frustum.right, frustum.down, frustum.up, frustum.near, frustum.far);
        //glOrtho(-10, 10, -10, 10, 1, 100);
        
        // Setup camera view point
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixf(camera->getTransform().transpose());
        
        // Setup stack
        modelview_matrix_stack_.push(camera->getTransform());
        
        // Setup lights ids
        next_free_light_id_ = 0;
        
        // Turn on lights
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new GLTurnLightsOperation()));
        
        // Render scene
        scene->getRoot()->traverse(shared_ptr<Node::VisitOperation>(new GLNodeDrawOperation(this)));

        // Finish
        //glFinish();
    }
}