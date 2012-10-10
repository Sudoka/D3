//
//  BlinnPhongShader.vsh
//  D3
//
//  Created by Srđan Rašić on 9/28/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifdef VERTEX_SHADER

/* Constants */
//const int max_texcoords = 1;
const int max_light_sources = 2;

/* Definitions */
struct LightSourceParameters {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    vec3 half_vector;
    vec3 spot_direction;
    float spot_exponent;
    float spot_cutoff;
    float spot_cos_cutoff;
    vec3 attenuation;
};

struct MaterialParameters {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

/* Uniforms */
uniform mat4 model_view_matrix;
uniform mat4 model_view_projection_matrix;
uniform mediump mat3 normal_matrix;
uniform mediump mat4 texture_matrix;

uniform LightSourceParameters light_source[max_light_sources];
uniform MaterialParameters material;

uniform int num_of_enabled_lights;
uniform int need_local_viewer;     // set true if there is Point or Spot light in scene
uniform vec4 scene_ambient_color;

/* Attributes */
attribute vec4 in_position;
attribute mediump vec3 in_normal;
attribute mediump vec4 in_texcoord;

/* Varyings */
varying lowp vec4 texcoord;
varying lowp vec4 frag_color_primary;
varying lowp vec4 frag_color_secondary;

/* Other */
invariant gl_Position;

/* Functions */
void DirectionalLight(const in  int     i,
                      const in  vec3    normal,
                      inout vec4    ambient,
                      inout vec4    diffuse,
                      inout vec4    specular)
{
    float nDotVP; // normal . light direction
    float nDotHV; // normal . half vector
    float pf;   // power factor;
    
    nDotVP = max(0.0, dot(normal, normalize(vec3(light_source[i].position))));
    nDotHV = max(0.0, dot(normal, vec3(light_source[i].half_vector)));
    
    if (nDotVP == 0.0)
        pf = 0.0;
    else
        pf = pow(nDotHV, material.shininess);
    
    ambient += light_source[i].ambient;
    diffuse += light_source[i].diffuse * nDotVP;
    specular += light_source[i].specular * pf;
}

void PointLight(const in  int   i,
                const in vec3   eye,
                const in vec3   eye_vertex_position3,
                const in mediump vec3  normal,
                inout vec4  ambient,
                inout vec4  diffuse,
                inout vec4  specular)
{
    float nDotVP; // normal . light direction
    float nDotHV; // normal . half vector
    float pf;   // power factor;
    float attenuation; // computed attenuation factor
    float d; // distance from vertex to light source
    vec3 VP; // direction from vertex to light source
    vec3 half_vector; // direction of max highlights
    
    VP = vec3(light_source[i].position) - eye_vertex_position3;
    d = length(VP);
    VP = normalize(VP);
    
    attenuation = 1.0 / (light_source[i].attenuation.x +
                         light_source[i].attenuation.y * d +
                         light_source[i].attenuation.z * d * d);
    
    half_vector = normalize(VP + eye);
    
    nDotVP = max(0.0, dot(normal, VP));
    nDotHV = max(0.0, dot(normal, half_vector));
    
    if (nDotVP == 0.0)
        pf = 0.0;
    else
        pf = pow(nDotHV, material.shininess);
    
    ambient += light_source[i].ambient * attenuation;
    diffuse += light_source[i].diffuse * nDotVP * attenuation;
    specular += light_source[i].specular * pf * attenuation;
}

void SpotLight(const in  int    i,
               const in vec3    eye,
               const in vec3    eye_vertex_position3,
               const in  vec3   normal,
               inout vec4   ambient,
               inout vec4   diffuse,
               inout vec4   specular)
{
    float nDotVP; // normal . light direction
    float nDotHV; // normal . half vector
    float pf;   // power factor;
    float attenuation; // computed attenuation factor
    float spot_dot; // cosine of angle between spotlight
    float spot_attenuation; // spotlight attenutation factor
    float d; // distance from vertex to light source
    vec3 VP; // direction from vertex to light source
    vec3 half_vector; // direction of max highlights
    
    VP = vec3(light_source[i].position) - eye_vertex_position3;
    d = length(VP);
    VP = normalize(VP);
    
    attenuation = 1.0 / (light_source[i].attenuation.x +
                         light_source[i].attenuation.y * d +
                         light_source[i].attenuation.z * d * d);
    
    spot_dot = dot(-VP, normalize(light_source[i].spot_direction));
    if (spot_dot < light_source[i].spot_cos_cutoff)
        spot_attenuation = 0.0;
    else
        spot_attenuation = pow(spot_dot, light_source[i].spot_exponent);
    
    attenuation *= spot_attenuation;
    
    half_vector = normalize(VP + eye);
    
    nDotVP = max(0.0, dot(normal, VP));
    nDotHV = max(0.0, dot(normal, half_vector));
    
    if (nDotVP == 0.0)
        pf = 0.0;
    else
        pf = pow(nDotHV, material.shininess);
    
    ambient += light_source[i].ambient * attenuation;
    diffuse += light_source[i].diffuse * nDotVP * attenuation;
    specular += light_source[i].specular * pf * attenuation;
}



void main()
{
    vec4 eye_vertex_position4;
    vec3 eye_vertex_position3;
    
    vec3 normal;
    vec3 eye;
    
    /* Calculate normal */
    normal = normalize(normal_matrix * in_normal);  // optimize if possible
    
    /* Calculate texture coordinate(s) */
    texcoord = texture_matrix * in_texcoord;
    
    /* Calculate positions */   
    if (need_local_viewer == 1) {
        eye_vertex_position4 = model_view_matrix * in_position;
        eye_vertex_position3 = (vec3(eye_vertex_position4)) / eye_vertex_position4.w;
        eye = -normalize(eye_vertex_position3);
    }
    
    lowp vec4 ambient = vec4(0.0);
    lowp vec4 diffuse = vec4(0.0);
    lowp vec4 specular = vec4(0.0);
    
    for (int i = 0; i < num_of_enabled_lights; i++) {
        if (light_source[i].position.w == 0.0)
            DirectionalLight(i, normal, ambient, diffuse, specular);
        else if (light_source[i].spot_cutoff == 180.0)
            PointLight(i, eye, eye_vertex_position3, normal, ambient, diffuse, specular);
        else
            SpotLight(i, eye, eye_vertex_position3, normal, ambient, diffuse, specular);
    }
    
    frag_color_primary = clamp(scene_ambient_color + ambient * material.ambient + diffuse * material.diffuse, 0.0, 1.0);
    frag_color_secondary = clamp(vec4(specular.rgb * material.specular.rgb, 1.0), 0.0, 1.0);
    
    gl_Position = model_view_projection_matrix * in_position;
}

#endif

#ifdef FRAGMENT_SHADER

uniform lowp sampler2D texture_sampler;

uniform lowp float texture_mask;

varying lowp vec4 texcoord;
varying lowp vec4 frag_color_primary;
varying lowp vec4 frag_color_secondary;

void main()
{
    /* Get pixel */
    lowp vec4 texel = texture2D(texture_sampler, texcoord.st) + vec4(texture_mask, texture_mask, texture_mask, texture_mask);
    
    /* Final color */
    gl_FragColor = clamp(texel * frag_color_primary + frag_color_secondary, 0.0, 1.0);
}

#endif