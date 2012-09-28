//
//  .hpp
//  
//
//  Created by Srđan Rašić on 8/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __hpp
#define __hpp

// Interfaces
// Resources
#include "FileIO.hpp"

// Window
#include "Window.hpp"
#ifdef GLUT
#include "GLUTWindow.hpp"
#elif defined _IOS_
#include "EAGLWindow.hpp"
#endif

// Math
#include "Math.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat3.hpp"
#include "Mat4.hpp"
#include "Quat.hpp"

// Scene graph
#include "Scene.hpp"
#include "Node.hpp"
#include "ArrayDescriptor.hpp"
#include "Geometry.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "StateOperation.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "ParticleEmitter.hpp"

// Primitives
#include "GeometryFactory.hpp"
#include "Modeler.hpp"


// Rendering system
#include "GLShader.hpp"
#include "GLProgram.hpp"
#include "SceneRenderer.hpp"
//#include "GLSceneRenderer.hpp"
#include "GLSLRenderer.hpp"
#include "SimpleRenderer.hpp"


// Physics
#include "SceneSimulator.hpp"
#include "ParticleSystem.hpp"

// Resources
#include "ResourceManager.hpp"

//#include "Engine.hpp"

#include "Application.hpp"

// Implementation
// Simple method to avoid compiling lib
#ifdef D3_COMPILE
#include "Math.cpp"
#include "Node.cpp"
#include "Scene.cpp"
#include "Camera.cpp"
#include "PointLight.cpp"
#include "DirectionalLight.cpp"
#include "SpotLight.cpp"
#include "Image.cpp"
#include "Material.cpp"
#include "Texture.cpp"
//#include "GLSceneRenderer.cpp"
#include "GeometryFactory.cpp"
#include "FileIO.cpp"
#include "GLShader.cpp"
#include "GLProgram.cpp"
#include "GLSLRenderer.cpp"
#include "SimpleRenderer.cpp"
#include "Modeler.cpp"
#include "SceneSimulator.cpp"
#include "ParticleSystem.cpp"
#include "ParticleEmitter.cpp"
#include "ResourceManager.cpp"

#ifdef GLUT
#include "GLUTWindow.cpp"
#elif defined _IOS_
#include "EAGLWindow.mm"
#endif

//#include "Engine.cpp"

#include "Application.cpp"
#include "Example.hpp"

#endif
#endif
