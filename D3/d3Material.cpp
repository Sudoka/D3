//
//  d3Material.cpp
//  D3
//
//  Created by Srđan Rašić on 8/29/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "d3Material.hpp"

namespace d3 {
    
    d3Material::d3Material()
    {
        setAmbientColor(d3Vec4(0.2, 0.2, 0.2, 1.0));
        setDiffuseColor(d3Vec4(0.8, 0.8, 0.8, 1.0));
        setSpecularColor(d3Vec4(0.0, 0.0, 0.0, 1.0));
        setShininess(0);
    }
    
    void d3Material::setAmbientAndDiffuseColor(d3Vec4 color)
    {
        setAmbientColor(color);
        setDiffuseColor(color);
    }
}