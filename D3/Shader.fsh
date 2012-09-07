//
//  Shader.fsh
//  
//
//  Created by Srđan Rašić on 9/6/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

varying vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
