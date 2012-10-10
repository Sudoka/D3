//
//  TexturedMesh.cpp
//  D3
//
//  Created by Srđan Rašić on 10/8/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "TexturedMesh.hpp"

namespace d3 {
    TexturedMesh::TexturedMesh(shared_ptr<VertexData> index_array,  //!> Index array
                               shared_ptr<VertexData> vertex_array, //!> Interleaved vertex array
                               unsigned int primitive_type,         //!> Primitive type
                               unsigned int element_count,          //!> Number of elements to draw
                               shared_ptr<Texture> texture)         //!> Optional texture
    {
        this->index_array = index_array;
        this->vertex_array = vertex_array;
        this->texture = texture;
        this->primitive_type = primitive_type;
        this->element_count = element_count;
        this->material = shared_ptr<Material>(new Material);
    }
    
    //! Sets texture
    void TexturedMesh::setTexture(shared_ptr<Texture> texture)
    {
        this->texture = texture;
    }
    
    //! Sets material
    void TexturedMesh::setMaterial(shared_ptr<Material> material)
    {
        this->material = material;
    }
    
    //! Drawable:: Called upon drawing
    void TexturedMesh::preDraw(SceneRenderer & renderer)
    {
        renderer.useProgram("BlinnPhongShader.shader");
        renderer.getProgram().setParamVec4("material.ambient", material->getAmbientColor());
        renderer.getProgram().setParamVec4("material.diffuse", material->getDiffuseColor());
        renderer.getProgram().setParamVec4("material.specular", material->getSpecularColor());
        renderer.getProgram().setParamFloat("material.shininess", material->getShininess());
        renderer.getProgram().setVertexData(vertex_array.get());
        
        if (texture) {
            renderer.useTexture(texture);
            renderer.getProgram().setParamFloat("texture_mask", 0.f);
        } else 
            renderer.getProgram().setParamFloat("texture_mask", 1.f);
    }
    
    //! Drawable:: Draw one occurrance
    void TexturedMesh::drawOccurrence(SceneRenderer & renderer, SceneNode & node)
    {
        Mat4 model_view_matrix = node.getScene().getCamera().getTransform() * node.getCachedTransformRef();   // Ref, not ptr, FIX
        Mat4 model_view_projection_matrix = node.getScene().getCamera().getProjection() * model_view_matrix;
        Mat3 normal_matrix = model_view_matrix.inverse().transpose();
        Mat4 texture_matrix = Mat4();
        
        renderer.getProgram().setParamMat4("model_view_matrix", model_view_matrix);
        renderer.getProgram().setParamMat4("model_view_projection_matrix", model_view_projection_matrix);
        renderer.getProgram().setParamMat4("texture_matrix", texture_matrix);
        renderer.getProgram().setParamMat3("normal_matrix", normal_matrix);

        if (index_array)
            renderer.drawElements(primitive_type, element_count, index_array);
        else
            renderer.drawArrays(primitive_type, element_count);
    }
    
    //! Drawable:: Called after drawing
    void TexturedMesh::postDraw(SceneRenderer & renderer)
    {
        for (auto it : vertex_array->getAttribMapRef())
            renderer.getProgram().disableArrayPtr(it.first);
    }
}