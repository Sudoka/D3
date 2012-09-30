//
//  ParticleShader.fsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

uniform sampler2D texture_sampler;
varying lowp vec4 out_color;

void main()
{
    gl_FragColor = texture2D(texture_sampler, gl_PointCoord) * out_color;
}