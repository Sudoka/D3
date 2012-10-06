//
//  PlaneTechnique.hpp
//  D3
//
//  Created by Srđan Rašić on 10/5/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_PlainTechnique_hpp
#define D3_PlainTechnique_hpp

namespace d3 {
    class PlainTechnique : public Technique {
    private:
        Program * program;
        
    protected:
        PlainTechnique();
        
        virtual void setupContext();
        virtual void setupVertexData();
        virtual void draw();
        virtual void restoreContext();
    };
}

#endif
