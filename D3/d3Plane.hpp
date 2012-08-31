//
//  d3Plane.hpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Plane_hpp
#define D3_d3Plane_hpp

#include "d3Gl.hpp"

namespace d3 {
#pragma mark Interface
    class d3Plane : public d3Node::Attachment  {
    protected:
        d3RenderOperation *render_operation_;
        d3Vec3* iva;
        
    public:
        d3Plane() {
            float width = 2;
            float height = 2;
            
            int subdivs = 10;
            float offsetX = 1.0 / subdivs;
            float offsetZ = 1.0 / subdivs;
            
            iva = new d3Vec3[subdivs * (12 + subdivs * 6)];
            
            int idx = 0;
            for (int j = 1; j <= subdivs; j++) {
                iva[idx++] = d3Vec3((offsetX * (j - 1) - 0.5) * width, 0, - 0.5 * height);  // vertex
                iva[idx++] = d3Vec3(0, 1, 0);                                               // normal
                iva[idx++] = d3Vec3(offsetX * (j - 1), 0.0, 0);                             // texture coordinate
                
                iva[idx++] = d3Vec3((offsetX * j - 0.5) * width, 0, - 0.5 * height);
                iva[idx++] = d3Vec3(0, 1, 0);
                iva[idx++] = d3Vec3(offsetX * j, 0.0, 0);
                
                for (int i = 1; i <= subdivs; i++) {
                    iva[idx++] = d3Vec3((offsetX * (j - 1) - 0.5) * width, 0, (offsetZ * i - 0.5) * height);
                    iva[idx++] = d3Vec3(0, 1, 0);
                    iva[idx++] = d3Vec3(offsetX * (j - 1), offsetZ * i, 0);
                    
                    iva[idx++] = d3Vec3((offsetX * j - 0.5) * width, 0, (offsetZ * i - 0.5) * height);
                    iva[idx++] = d3Vec3(0, 1, 0);
                    iva[idx++] = d3Vec3(offsetX * j, offsetZ * i, 0);
                }
                
                iva[idx++] = d3Vec3((offsetX * j - 0.5) * width, 0, (offsetZ * subdivs - 0.5) * height);
                iva[idx++] = d3Vec3(0, 1, 0);
                iva[idx++] = d3Vec3(offsetX * j - 1.0, offsetX * subdivs, 0);
                
                iva[idx++] = d3Vec3((offsetX * j - 0.5) * width, 0, - 0.5 * height);
                iva[idx++] = d3Vec3(0, 1, 0);
                iva[idx++] = d3Vec3(offsetX * j, 0.0, 0);
            }
            
            render_operation_ = new d3RenderOperation();
            render_operation_->setVertexArray(new d3ArrayDescriptor<float>((float*)&iva[0], idx/3, sizeof(d3Vec3) * 3));
            render_operation_->setNormalArray(new d3ArrayDescriptor<float>((float*)&iva[1], idx/3, sizeof(d3Vec3) * 3));
            render_operation_->setTexCoordArray(new d3ArrayDescriptor<float>((float*)&iva[2], idx/3, sizeof(d3Vec3) * 3));
            render_operation_->setGeometryType(GL_TRIANGLE_STRIP);

        }
        
        virtual bool isVisible() const { return true; }
        
        virtual d3RenderOperation * getRenderOperation() { return render_operation_; }
    };
}

#endif
