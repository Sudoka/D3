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
// Math
#include "d3Math.hpp"
#include "d3Vec3.hpp"
#include "d3Vec4.hpp"
#include "d3Mat3.hpp"
#include "d3Mat4.hpp"
#include "d3Quat.hpp"

// Core
//#include "d3Base.hpp"

// Scene graph
#include "d3Scene.hpp"
#include "d3Node.hpp"
#include "d3ArrayDescriptor.hpp"
#include "d3Material.hpp"
#include "d3Texture.hpp"
#include "d3StateOperation.hpp"
#include "d3RenderOperation.hpp"
#include "d3PointLight.hpp"
#include "d3SpotLight.hpp"
#include "d3DirectionalLight.hpp"
#include "d3Box.hpp"
#include "d3Camera.hpp"
#include "d3Axes.hpp"
#include "d3Plane.hpp"
#include "d3Image.hpp"


// Rendering system
#include "d3GLSceneGraphRenderer.hpp"

// Implementation
// Simple method to avoid compiling lib
#ifdef D3_COMPILE
#include "d3Node.cpp"
#include "d3Box.cpp"
#include "d3Scene.cpp"
#include "d3Camera.cpp"
#include "d3PointLight.cpp"
#include "d3DirectionalLight.cpp"
#include "d3SpotLight.cpp"
#include "d3Image.cpp"
#include "d3RenderOperation.cpp"
#include "d3Material.cpp"
#include "d3Texture.cpp"
#include "d3GLSceneGraphRenderer.cpp"

#endif
#endif
