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
#include "SceneNode.hpp"
#include "Movable.hpp"
#include "Occurable.hpp"
#include "Program.hpp"
#include "VertexData.hpp"
#include "BufferedVertexData.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Image.hpp"

// Primitives
#include "GeometryFactory.hpp"

// Rendering system
#include "Program.hpp"
#include "GLSLProgram.hpp"
#include "SceneRenderer.hpp"
#include "GLSLSceneRenderer.hpp"

#include "Drawable.hpp"
#include "TexturedMesh.hpp"

// Physics
#include "SceneSimulator.hpp"
#include "ParticleSystem.hpp"
#include "BillboardParticles.hpp"

// Resources
#include "ResourceManager.hpp"
#include "Application.hpp"

// Implementation
// Simple method to avoid compiling lib
#ifdef D3_COMPILE
#include "Math.cpp"
#include "Node.cpp"
#include "SceneNode.cpp"
#include "Scene.cpp"
#include "Camera.cpp"
#include "Light.cpp"
#include "Image.cpp"
#include "Texture.cpp"
#include "GeometryFactory.cpp"
#include "FileIO.cpp"
#include "SceneRenderer.cpp"
#include "GLSLProgram.cpp"
#include "GLSLSceneRenderer.cpp"
#include "SceneSimulator.cpp"
#include "ParticleSystem.cpp"
#include "ResourceManager.cpp"
#include "BillboardParticles.cpp"

#ifdef GLUT
#include "GLUTWindow.cpp"
#elif defined _IOS_
#include "EAGLWindow.mm"
#endif

#include "VertexData.cpp"
#include "BufferedVertexData.cpp"
#include "Program.cpp"
#include "Movable.cpp"
#include "Occurable.cpp"
#include "Drawable.cpp"
#include "TexturedMesh.cpp"

#include "Application.cpp"
#include "Example.hpp"

#endif
#endif
