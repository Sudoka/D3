//
//  d3Axes.hpp
//  D3
//
//  Created by Srđan Rašić on 8/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Axes_hpp
#define D3_d3Axes_hpp

#include "d3Gl.hpp"

namespace d3 {
#pragma mark Interface
    class d3Axes : public d3Node::Attachment {
    protected:
        d3RenderOperation *render_operation_;
        d3Vec3* iva;
        
    public:
        d3Axes()
        {
            iva = new d3Vec3[6 * 2];
            
            // X-axis
            iva[0] = iva[2] = d3Vec3(1.f, 0.f, 0.f);    // color
            iva[1] = d3Vec3(-1000.f, 0.f, 0.f);         // star point
            iva[3] = d3Vec3( 1000.f, 0.f, 0.f);         // end point
            
            // Y-axis
            iva[4] = iva[6] = d3Vec3(0.f, 1.f, 0.f);    // color
            iva[5] = d3Vec3(0.f, -1000.f, 0.f);         // star point
            iva[7] = d3Vec3(0.f,  1000.f, 0.f);         // end point
            
            // Z-axis
            iva[8] = iva[10] = d3Vec3(0.f, 0.f, 1.f);    // color
            iva[9] = d3Vec3(0.f, 0.f, -1000.f);         // star point
            iva[11] = d3Vec3(0.f, 0.f,  1000.f);         // end point
            
            render_operation_ = new d3RenderOperation();
            render_operation_->setVertexArray(new d3ArrayDescriptor<float>((float*)&iva[1], 6, sizeof(d3Vec3) * 2));
            render_operation_->setColorArray(new d3ArrayDescriptor<float>((float*)&iva[0], 6, sizeof(d3Vec3) * 2));
            render_operation_->setGeometryType(GL_LINES);
        }
        
        ~d3Axes()
        {
            delete render_operation_;
        }
        
        virtual bool isVisible() const { return true; }
        virtual d3RenderOperation * getRenderOperation() { return render_operation_; }
    };
}

#endif
