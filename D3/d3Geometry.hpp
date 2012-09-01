//
//  d3Geometry.hpp
//  D3
//
//  Created by Srđan Rašić on 9/1/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3Geometry_hpp
#define D3_d3Geometry_hpp

namespace d3 {
    class d3Geometry {
    protected:
        d3ArrayDescriptor<unsigned int> * indices_;
        d3ArrayDescriptor<float> * vertex_array_;
        d3ArrayDescriptor<float> * normal_array_;
        d3ArrayDescriptor<float> * tex_coord_array_;
        d3ArrayDescriptor<float> * color_array_;
        
        unsigned int geometry_type_;
        
    public:
        d3Geometry();
        
        void setGeometryType(unsigned int geometry_type);
        unsigned int getGeometryType();
        
        void setVertexArray(d3ArrayDescriptor<float> * vertex_array);
        d3ArrayDescriptor<float> * getVertexArray() const;
        
        void setIndices(d3ArrayDescriptor<unsigned int> * indices);
        d3ArrayDescriptor<unsigned int> * getIndices() const;
        
        void setNormalArray(d3ArrayDescriptor<float> * normal_array);
        d3ArrayDescriptor<float> * getNormalArray() const;
        
        void setTexCoordArray(d3ArrayDescriptor<float> * tex_coord_array);
        d3ArrayDescriptor<float> * getTexCoordArray() const;
        
        void setColorArray(d3ArrayDescriptor<float> * color_array);
        d3ArrayDescriptor<float> * getColorArray() const;
    };
}

#endif
