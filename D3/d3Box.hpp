//
//  d3Box.hpp
//  D3
//
//  Created by Srđan Rašić on 8/24/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Box_hpp
#define D3_d3Box_hpp

#include "d3Node.hpp"

namespace d3 {
#pragma mark Interface
    class d3Box : public d3Node::Attachment {
    protected:
        d3RenderOperation *render_operation_;
        
    public:
        d3Box();
        
        virtual bool isVisible() const;
        
        virtual d3RenderOperation * getRenderOperation() { return render_operation_; }
    };
}

#endif
