//
//  ParticleShader.vsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifdef VERTEX_SHADER

uniform mat4 model_view_matrix;
uniform mat4 model_view_projection_matrix;
uniform float point_size_factor;

attribute vec4 in_vertex;
attribute float in_point_size;

attribute vec4 in_color;

varying lowp vec4 out_color;

void main() {
    vec4 eye4 = model_view_matrix * in_vertex;
    vec3 eye3 = vec3(eye4) / eye4.w;
    float distance = length(eye3)/4;
    
    out_color = in_color;
    gl_PointSize = in_point_size * point_size_factor / distance;
    gl_Position = model_view_projection_matrix * in_vertex;
}

#endif

#ifdef FRAGMENT_SHADER

uniform sampler2D texture_sampler;
varying lowp vec4 out_color;

void main()
{
    gl_FragColor = texture2D(texture_sampler, gl_PointCoord) * out_color;
}

#endif