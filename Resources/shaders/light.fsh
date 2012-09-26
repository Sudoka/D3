//
//  light.fsh
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

//precision mediump float;

varying vec4 colorVarying;

varying vec3 attenuation;
varying float distance;
varying vec4 diffuse, ambient, specular;
varying vec3 frag_normal, frag_light_direction, frag_half_vector;

void main()
{
    vec3 normal = normalize(frag_normal);
    
    float nDotL = max(0.0, dot(normal, normalize(frag_light_direction)));
    
    vec4 color = vec4(0.1, 0.1, 0.1, 1.0);
    
    if (nDotL > 0.0) {
        
        float att = 1.0 / (attenuation.x + attenuation.y * distance + attenuation.z * distance * distance);
        
        color += att * (ambient + diffuse * nDotL);
        
        vec3 half_vector = normalize(frag_half_vector);
        float nDotHV = max(0.0, dot(normal, half_vector));
        color += att* specular * pow(nDotHV, 20.0);
    }
    
    gl_FragColor = color /* texel*/;
}
