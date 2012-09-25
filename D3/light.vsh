//
//  light.vsh
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

//precision mediump float;

/* Light descriptor */
struct LightSourceParameters {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    vec3 halfVector;
    vec3 spotDirection;
    float spotExponent;
    float spotCutoff; // (range: [0.0,90.0], 180.0)
    float spotCosCutoff; // (range: [1.0,0.0],-1.0)
    vec3 attenuation;
};

/* Material descriptor */
struct MaterialParameters {
    vec4 emission;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

/* Maximum number of lights */
const int MaxLights = 5;

uniform int numberOfLights;

uniform LightSourceParameters lightSource[MaxLights];
uniform MaterialParameters material;

attribute vec4 position;
attribute vec3 normal;
//attribute vec4 color;

varying vec4 colorVarying;

uniform mat4 camera_transform;
uniform mat4 model_view;
uniform mat3 normal_transform;

varying float distance;
varying vec4 diffuse, ambient, specular;
varying vec3 frag_normal, frag_light_direction, frag_half_vector;
varying vec3 attenuation;

invariant gl_Position;

void main()
{
    //vec4 position4 = vec4(position, 1.0);
    
    gl_Position = model_view * position;
    
    vec3 vertex_to_light = vec3(lightSource[0].position - gl_Position);
    
    distance = length(vertex_to_light);
    frag_normal = normalize(normal_transform * normal);
    frag_light_direction = normalize(vertex_to_light);
    frag_half_vector = normalize(lightSource[0].halfVector);
    
    vec4 diffuse_color = material.diffuse;
    //if (color != vec4(0.0, 0.0, 0.0, 0.0)) diffuse_color = color*0.0001 + vec4(0.8, 0.8, 0.8, 1.0);
    
    diffuse = material.diffuse * lightSource[0].diffuse;
    ambient = material.ambient * lightSource[0].ambient;
    specular = material.specular * lightSource[0].specular;
       
    
    attenuation = lightSource[0].attenuation;
    
    gl_Position = camera_transform * gl_Position;
}