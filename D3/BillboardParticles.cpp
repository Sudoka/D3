//
//  BillboardParticles.cpp
//  D3
//
//  Created by Srđan Rašić on 10/7/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "BillboardParticles.hpp"

namespace d3 {
    BillboardParticles::BillboardParticles(shared_ptr<ParticleSystem> particle_system) : emitter(particle_system)
    {
        unsigned max_particle_count  = emitter->max_particle_count;
        
        /* Create index buffer */
        ibo = shared_ptr<VertexData>(new BufferedVertexData(sizeof(unsigned) * max_particle_count * 6,
                                                            sizeof(unsigned), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER, NULL));
        unsigned * indices = (unsigned *)ibo->mapData();
        
        IndexTemplate tmp;
        for (int i = 0; i < max_particle_count * 6; i++)
            indices[i] = (i/6)*4 + tmp.indices[i%6];
        
        ibo->unmapData();
        
        /* Create texcoord buffer */
        tbo = shared_ptr<VertexData>(new BufferedVertexData(sizeof(Vec3) * 4 * max_particle_count,
                                                            sizeof(Vec3), GL_STATIC_DRAW, GL_ARRAY_BUFFER, NULL));
        Vec3 * texcoords = (Vec3 *)tbo->mapData();
        for (int i = 0; i < max_particle_count; i++) {
            texcoords[i*4+0] = Vec3(0, 0, 0);
            texcoords[i*4+1] = Vec3(1, 0, 0);
            texcoords[i*4+2] = Vec3(1, 1, 0);
            texcoords[i*4+3] = Vec3(0, 1, 0);
        }
        tbo->unmapData();
        tbo->setAttribute("in_texcoord", VertexData::AttribProps(0, 2, GL_FLOAT));
        
        /* Create position and colour buffer */
        vbo_size = sizeof(VertexTemplate) * 4 * max_particle_count;
        vbo = shared_ptr<VertexData>(new BufferedVertexData(vbo_size * getNumberOfOccurrences(),
                                                            sizeof(VertexTemplate), GL_STREAM_DRAW, GL_ARRAY_BUFFER, NULL));
        vbo->setAttribute("in_position", VertexData::AttribProps(0, 3, GL_FLOAT));
        vbo->setAttribute("in_color", VertexData::AttribProps(sizeof(Vec3), 4, GL_UNSIGNED_BYTE, GL_TRUE));
    }
    
    //! SceneSimulator::Updatable:: Updates VBO
    void BillboardParticles::update(float dt)
    {
        this->particle_count = emitter->particle_count;
        
        /* Set positions and colors */
        vbo->resetSize(sizeof(VertexTemplate) * 4 * particle_count * getNumberOfOccurrences());
        
        VertexTemplate * vbo_array = (VertexTemplate *)vbo->mapData();
        
        unsigned ctr = 0;
        for (SceneNode * node : getOriginList()) {
            Mat4 cam_transform = Application::get().getScene().getCamera().getTransform() * node->getCachedTransformRef();
            
            Vec3 up(cam_transform.a01, cam_transform.a11, cam_transform.a21);
            Vec3 right(cam_transform.a00, cam_transform.a10, cam_transform.a20);
            
            for (unsigned i = 0; i < particle_count; i++) {
                unsigned index = (particle_count * ctr + i) * 4;
                
                float size = emitter->properties_array[i].size;
                Vec3 position = emitter->properties_array[i].position;
                int color = to8BitVec4(emitter->properties_array[i].color);
                //Vec4 color = emitter->properties_array[i].color;
                
                vbo_array[index+0].color = color; vbo_array[index+0].position = (up * (-1) - right) * size + position;
                vbo_array[index+1].color = color; vbo_array[index+1].position = (up - right) * size + position;
                vbo_array[index+2].color = color; vbo_array[index+2].position = (up + right) * size + position;
                vbo_array[index+3].color = color; vbo_array[index+3].position = (right - up) * size + position;
            }
            
            ctr++;
        }
        
        vbo->unmapData();
    }
    
    //! Drawable:: Called upon drawing
    void BillboardParticles::preDraw(SceneRenderer & renderer)
    {
        renderer.useProgram("BillboardParticleShader.shader");
        renderer.setDepthMask(false);
        renderer.setBlend(true);
        renderer.setBlendFunc(GL_SRC_ALPHA, GL_ONE);
        renderer.useTexture(emitter->properties->texture);
        renderer.getProgram().setVertexData(tbo.get());
        
        current_node = 0;
    }
    
    //! Drawable:: Draw one occurrence
    void BillboardParticles::drawOccurrence(SceneRenderer & renderer, SceneNode & node)
    {
        Mat4 model_view = node.getScene().getCamera().getTransform() * node.getCachedTransformRef();
        Mat4 model_view_projection = node.getScene().getCamera().getProjection() * model_view;
        
        renderer.getProgram().setParamMat4("model_view_projection_matrix", model_view_projection);
        renderer.getProgram().setVertexData(vbo.get(), current_node * sizeof(VertexTemplate) * particle_count * 4);
        renderer.drawElements(GL_TRIANGLE_STRIP, particle_count * 6, ibo);
        
        current_node++;
    }
    
    //! Drawable:: Called after drawing
    void BillboardParticles::postDraw(SceneRenderer & renderer)
    {
        renderer.setDepthMask(true);
        renderer.setBlend(false);
        renderer.getProgram().disableArrayPtr("in_position");
        renderer.getProgram().disableArrayPtr("in_texcoord");
        renderer.getProgram().disableArrayPtr("in_color");
    }
}