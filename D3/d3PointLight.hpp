//
//  d3PointLight.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3PointLight_hpp
#define D3_d3PointLight_hpp

#include "d3Node.hpp"

namespace d3 {
    class d3Vec4;
    
#pragma mark Interface
    class d3PointLight : public d3Node::Attachment, public d3StateOperation {
    protected:
        d3Vec4 ambient_color_;
        d3Vec4 diffuse_color_;
        d3Vec4 specular_color_;

        bool is_on_;
        
    public:
        d3PointLight();
        
        virtual void setOn(bool state);
        
        virtual void setAmbientColor(d3Vec4 color);
        virtual void setDiffuseColor(d3Vec4 color);
        virtual void setSpecularColor(d3Vec4 color);
        virtual void setAmbientAndDiffuseColor(d3Vec4 color);
        
        virtual bool isVisible() const;
        
        virtual void apply();
        
        virtual d3StateOperation * getStateOperation() { return this; }
    };
}

#endif
