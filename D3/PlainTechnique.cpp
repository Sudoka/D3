//
//  PlainTechnique.cpp
//  D3
//
//  Created by Srđan Rašić on 10/5/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "PlainTechnique.hpp"

namespace d3 {
    
    PlainTechnique::PlainTechnique() {
        program = Application::get()->getDevice()->getCurrentProgram();
    }
    
    void PlainTechnique::setupContext() {
        //            glMaterialf(GL_FRONT, GL_SHININESS, renderable->getMaterial()->getShininess());
        //            glMaterialfv(GL_FRONT, GL_AMBIENT, renderable->getMaterial()->getAmbientColor());
        //            glMaterialfv(GL_FRONT, GL_DIFFUSE, renderable->getMaterial()->getDiffuseColor());
        //            glMaterialfv(GL_FRONT, GL_SPECULAR, renderable->getMaterial()->getSpecularColor());
        // useProgram (default)
    }
    
    void PlainTechnique::setupVertexData() {
        for (VertexData * vd : getRenderable()->getVertexData()) {
            vd->bindToProgram(program);
        }
    }
    
    void PlainTechnique::draw() {
        VertexData * indices = getRenderable()->getIndexData();
        
        if (indices != nullptr) {
            glDrawElements(getRenderable()->getPrimitiveType(),
                           getRenderable()->getElementCount(),
                           GL_UNSIGNED_INT,
                           indices->getArrayPointer());
        } else {
            glDrawArrays(getRenderable()->getPrimitiveType(),
                         0,
                         getRenderable()->getElementCount());
        }
    }
    
    void PlainTechnique::restoreContext() {
        for (VertexData * vd : getRenderable()->getVertexData()) {
            vd->unbindFromProgram(program);
        }
    }
}