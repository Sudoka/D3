//
//  particle_system.vsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

uniform mat4 model_view_projection_matrix;
uniform float point_size_factor;

attribute vec4 in_vertex;
attribute float in_point_size;

attribute vec4 in_color;

varying lowp vec4 out_color;

void main() {
    out_color = in_color;
    gl_PointSize = in_point_size * point_size_factor;
    gl_Position = model_view_projection_matrix * in_vertex;
}