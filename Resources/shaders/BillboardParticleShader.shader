//
//  BillboardParticleShader.vsh
//  D3
//
//  Created by Srđan Rašić on 10/7/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifdef VERTEX_SHADER

uniform mat4 model_view_projection_matrix;

attribute vec4 in_position;
attribute vec4 in_color;
attribute mediump vec4 in_texcoord;

/* Varyings */
varying lowp vec4 texcoord;
varying lowp vec4 frag_color;

void main () {
    gl_Position = model_view_projection_matrix * in_position;
    frag_color = in_color;
    texcoord = in_texcoord;
}

#endif

#ifdef FRAGMENT_SHADER

uniform lowp sampler2D texture_sampler;

varying lowp vec4 texcoord;
varying lowp vec4 frag_color;

void main()
{
    /* Get pixel */
    lowp vec4 texel = texture2D(texture_sampler, texcoord.st);
    
    /* Final color */
    gl_FragColor = texel * frag_color;
}



#endif