//
//  texture.fsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//
//precision mediump float;
varying vec2 textureCoordinate;

uniform sampler2D tex;
uniform sampler2D lightning_tex;
uniform int has_texture ;

void main()
{
    vec4 light = texture2D(lightning_tex, gl_FragCoord.st / vec2(640, 480) );
    
    vec4 texel = vec4(0.8, 0.8, 0.8, 1.0);
    
    texel = texture2D(tex, textureCoordinate);
    
    gl_FragColor = texel* light;
}
