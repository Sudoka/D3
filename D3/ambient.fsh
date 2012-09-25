//
//  ambient.fsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

/* Uniforms */
uniform sampler2D texture_sampler;
//uniform vec4 ambient_color;

/* From vertex */
varying vec2 tex_coord_vry;

void main()
{
    /* Get pixel color */
    vec4 texel = texture2D(texture_sampler, tex_coord_vry);
    
    /* Final color */
    gl_FragColor = texel;
}
