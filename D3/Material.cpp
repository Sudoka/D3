//
//  BlinnPhongMaterial.cpp
//  
//
//  Created by Srđan Rašić on 8/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "Material.hpp"

namespace d3 {
    
    Material::Material()
    {
        setAmbientColor(Vec4(0.2, 0.2, 0.2, 1.0));
        setDiffuseColor(Vec4(0.8, 0.8, 0.8, 1.0));
        setSpecularColor(Vec4(0.0, 0.0, 0.0, 1.0));
        setShininess(0);
    }
    
    void Material::setAmbientAndDiffuseColor(Vec4 color)
    {
        setAmbientColor(color);
        setDiffuseColor(color);
    }
}