//
//  GLSLRenderer.cpp
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "GLSLSceneRenderer.hpp"
#include "OpenGLHeaders.hpp"
#include "ResourceManager.hpp"
#include "SceneNode.hpp"

namespace d3 {
    GLSLSceneRenderer::GLSLSceneRenderer(ResourceManager * resource_manager, Scene * scene) : SceneRenderer(scene)
    {        
        /* Load programs */
        registerProgram((GLSLProgram *)resource_manager->getProgram("PlainShader.shader").get());
        registerProgram((GLSLProgram *)resource_manager->getProgram("BlinnPhongShader.shader").get());
        registerProgram((GLSLProgram *)resource_manager->getProgram("BillboardParticleShader.shader").get());
        
        /* Setup OpenGL initial settings */
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
    }
    
    //! SceneRenderer:: Draws scene
    void GLSLSceneRenderer::render()
    {
        // Clear framebuffer
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

        //glDepthMask(GL_TRUE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Setup viewport
        glViewport(0, 0, Application::get().getWindow().getWidth(), Application::get().getWindow().getHeight());
        
        // Get and update camera if window has been resized
        scene->getCamera().setAspectRatio(Application::get().getWindow().getWidth() / (float) Application::get().getWindow().getHeight());
        
        useProgram("BlinnPhongShader.shader");
        
        // Setup lights
        for(auto it : light_map) {
            Light * light = it.first;
            String light_tag = String("light_source[") + it.second + String("].");
            
            /* Get params ref */
            Light::LightSourceParameters & param = light->getParametersRef();
            
            /* Set up shader parameters */
            Mat4 model_view = light->getMover().getScene().getCamera().getTransform() * light->getMover().getCachedTransformRef();
            Mat4 normal_matrix = model_view.inverse().transpose();
            Vec4 position = model_view * param.position;
            Vec3 spotDirection = normal_matrix * param.spotDirection;
            Vec3 half_vector = light->getMover().getScene().getCamera().getMover().getDerivedPosition() - param.position;
            
            getProgram().setParamVec4(light_tag + "ambient", param.ambient);
            getProgram().setParamVec4(light_tag + "diffuse", param.diffuse);
            getProgram().setParamVec4(light_tag + "specular", param.specular);
            getProgram().setParamVec4(light_tag + "position", position);
            getProgram().setParamVec3(light_tag + "half_vector", half_vector);
            getProgram().setParamVec3(light_tag + "spot_direction", spotDirection);
            getProgram().setParamFloat(light_tag + "spot_exponent", param.spotExponent);
            getProgram().setParamFloat(light_tag + "spot_cutoff", param.spotCutoff);
            getProgram().setParamFloat(light_tag + "spot_cos_cutoff", param.spotCosCutoff);
            getProgram().setParamVec3(light_tag + "attenuation", param.attenuation);
        }
        
        // Setup scene parameters
        Vec4 ambient_color(0.1, 0.1, 0.1, 1.0);
        getProgram().setParamVec4("scene_ambient_color", ambient_color);
        getProgram().setParamInt("num_of_enabled_lights", (int)light_map.size());
        getProgram().setParamBool("need_local_viewer", 1);
        
        // Draw scene
        for (Drawable * drawable : drawable_list) {
            drawable->_drawOccurrences(*this);
        }
    }
    
    //! SceneRenderer:: Binds texture to device
    void GLSLSceneRenderer::useTexture(shared_ptr<Texture> & texture)
    {
        texture->_bind();
    }
    
    //! SceneRenderer:: Binds program to device
    Program * GLSLSceneRenderer::useProgram(String name)
    {
        current_program_ = program_map_[name];
        current_program_->bind();
        
        return current_program_;
    }
    
    //! SceneRenderer:: @return Currently bound program
    Program & GLSLSceneRenderer::getProgram()
    {
        return * current_program_;
    }
    
    //! SceneRenderer:: Sets depth mask (true to enable writing to depth buffer, false otherwise)
    void GLSLSceneRenderer::setDepthMask(bool value)
    {
        glDepthMask(value);
    }
    
    //! SceneRenderer:: True to enable blending, false otherwise
    void GLSLSceneRenderer::setBlend(bool value)
    {
        if (value)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);
    }
    
    //! SceneRenderer:: Sets blending function coefficients
    void GLSLSceneRenderer::setBlendFunc(unsigned c_src, unsigned c_dst)
    {
        glBlendFunc(c_src, c_dst);
    }

    //! SceneRenderer:: Binds array to device
    void GLSLSceneRenderer::bindArray(shared_ptr<VertexData> & array)
    {
        array->_bind();
    }
    
    //! SceneRenderer:: Draws currently bound array
    void GLSLSceneRenderer::drawArrays(unsigned primitive_type, unsigned count)
    {
        glDrawArrays(primitive_type, 0, count);
    }
    
    //! SceneRenderer:: Draws elements indicated by index buffer
    void GLSLSceneRenderer::drawElements(unsigned primitive_type, unsigned count, const shared_ptr<VertexData> & ibo)
    {
        ibo->_bind();
        glDrawElements(primitive_type, count, GL_UNSIGNED_INT, ibo->getArrayPointer());
    }
    
    //! Inserts new program
    void GLSLSceneRenderer::registerProgram(GLSLProgram * program)
    {
        program_map_[program->getName()] = program;
    }
}