//
//  Example.cpp
//  D3
//
//  Created by Srđan Rašić on 9/27/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//
// Usage: arrows to move camera, 'wasd' to move box
//

#define GLUT
#define D3_COMPILE  // Compile engine (include all cpps to avoid libraries for now)
#include "d3.hpp"

using namespace d3;

class Example2 : public Example {
public:
    Example2(String path) : Example(path) {}
    
    virtual void onKeyDown(int key) {
        static float cam_radius = 15.0;
        static float cam_rotation = 0.0;
        static float cam_y = 8;
        
        switch(key) {
            case 'd' :
                getScene()->getRoot()->getSubnode("Kocka")->move(Vec3(0, 0, -0.5)); break;
            case 'a' :
                getScene()->getRoot()->getSubnode("Kocka")->move(Vec3(0, 0, 0.5)); break;
            case 'w' :
                getScene()->getRoot()->getSubnode("Kocka")->move(Vec3(-0.5, 0, 0)); break;
            case 's' :
                getScene()->getRoot()->getSubnode("Kocka")->move(Vec3(0.5, 0, 0)); break;
                
            case GLUT_KEY_UP + 1000:
                cam_y -= 0.5f; break;
            case GLUT_KEY_DOWN + 1000:
                cam_y += 0.5f; break;
            case GLUT_KEY_LEFT + 1000:
                cam_rotation += kPi/6.0; break;
            case GLUT_KEY_RIGHT + 1000:
                cam_rotation -= kPi/6.0; break; break;
        }
        
        Vec3 pos = Vec3(cosf(cam_rotation) * cam_radius, cam_y, sinf(cam_rotation) * cam_radius);
        getScene()->getCamera()->getParent()->setPosition(pos);
    }
};

int main(int argc, char** argv)
{
    (new Example2("Resources"))->run();
    return EXIT_SUCCESS;
}