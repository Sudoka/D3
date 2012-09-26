//
//  texture.vsh
//  D3
//
//  Created by Srđan Rašić on 9/25/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//
//precision mediump float;
invariant gl_Position;

attribute vec4 position;
attribute vec2 texcoord;

uniform mat4 cameraTransformMatrix;
uniform mat4 modelViewMatrix;

varying vec2 textureCoordinate;

uniform int has_texture ;


void main()
{
        textureCoordinate = texcoord;
    
    gl_Position = cameraTransformMatrix * modelViewMatrix * position;
}