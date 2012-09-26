//
//  ambient.vsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

/* Vertex geometry uniforms */
uniform mat4 model_view;
uniform mat4 camera_transform;

/* Vertex attributes */
attribute vec4 position;
attribute vec2 tex_coord;

/* To fragment */
varying vec2 tex_coord_vry;

/* Safe multipass */
invariant gl_Position;

void main()
{
    /* Interpolate texture coordinate */
    tex_coord_vry = tex_coord;
    
    /* Transform vertex to eye space */
    gl_Position = camera_transform * (model_view * position);
}