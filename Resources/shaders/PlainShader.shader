//
//  PlainShader.vsh
//  D3
//
//  Created by Srđan Rašić on 10/7/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifdef VERTEX_SHADER

uniform mat4 model_view_projection_matrix;

attribute vec4 in_position;

void main () {
    gl_Position = model_view_projection_matrix * in_position;
}

#endif

#ifdef FRAGMENT_SHADER

void main()
{
    gl_FragColor = vec4(0.9, 0.9, 0.9, 1.0);
}


#endif