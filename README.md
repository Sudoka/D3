# D3
A user-friendly cross-platfrom inverted scene graph based OpenGL graphics & physics engine.

![Screenshot](http://www.deviantpics.com/images/rAesp.png)

# Features
## Cross-platfrom
Written in C++ to maximize portability and performance. Currently implemented support for Desktop (using GLUT as window manager) and iOS.

## _Inverted_ Scene Graph
Rather then referencing Drawable object from each node, this engine utilises somewhat inverted approach. Each object (Drawable or some other) that can occur multiple times in scene is called Occurable. Those kind of objects contain list of all scene nodes at which instance of object should appear. This makes rendering of simple scenes that contain many instances of the same object very efficient. 

## Programable pipeline
All rendering is done by shaders and system is designed to make use of shaders user-friendly.

## Resource manager
A simple but very useful Resource manager class and concept.

## Particle system
Many properties can be manipulated through XML file so system can be used to achieve broad set of effects like fire, rain/snow, jet engines, explosions, etc...

## Physics
Collision detection and particle simulations.

# Requirements
* libpng 
* GLUT
* TinyXML 

# Basic usage
1. Inherit Application class.
2. In constructor add scene content- use getScene() and getResourceManager() to do so
3. Instanciate your class and call base mathod run() on it.

## Example
    (new d3::Example("/path/to/resources"))->run();

# Licence
This work is licensed under a [Creative Commons Attribution 3.0 Unported License](http://creativecommons.org/licenses/by/3.0/deed.en_US).

# Note
This is a work in progress.