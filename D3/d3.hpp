//
//  d3.hpp
//  D3
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef D3_d3_hpp
#define D3_d3_hpp

// Interfaces
// Resources
#include "d3FileIO.hpp"

// Math
#include "d3Math.hpp"
#include "d3Vec3.hpp"
#include "d3Vec4.hpp"
#include "d3Mat3.hpp"
#include "d3Mat4.hpp"
#include "d3Quat.hpp"

// Scene graph
#include "d3Scene.hpp"
#include "d3Node.hpp"
#include "d3ArrayDescriptor.hpp"
#include "d3Geometry.hpp"
#include "d3Material.hpp"
#include "d3Texture.hpp"
#include "d3StateOperation.hpp"
#include "d3PointLight.hpp"
#include "d3SpotLight.hpp"
#include "d3DirectionalLight.hpp"
#include "d3Renderable.hpp"
#include "d3Camera.hpp"
#include "d3Image.hpp"
#include "d3GeometryFactory.hpp"


// Rendering system
#include "d3GLShader.hpp"
#include "d3GLProgram.hpp"
#include "d3SceneRenderer.hpp"
#include "d3GLSceneRenderer.hpp"
#include "d3GLSLRenderer.hpp"



// Implementation
// Simple method to avoid compiling lib
#ifdef D3_COMPILE
#include "d3Math.cpp"
#include "d3Node.cpp"
#include "d3Scene.cpp"
#include "d3Camera.cpp"
#include "d3PointLight.cpp"
#include "d3DirectionalLight.cpp"
#include "d3SpotLight.cpp"
#include "d3Image.cpp"
#include "d3Material.cpp"
#include "d3Texture.cpp"
#include "d3GLSceneRenderer.cpp"
#include "d3GeometryFactory.cpp"
#include "d3FileIO.cpp"
#include "d3GLShader.cpp"
#include "d3GLProgram.cpp"
#include "d3GLSLRenderer.cpp"


#endif
#endif
