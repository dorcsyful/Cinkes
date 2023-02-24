#pragma once

//You can define the basic shaders you want in your code
//Any shader you put here will be loaded. You can specify which shader you want on a per object basis when creating them
//(you can also specify the path directly in the code)
//Defines:
//WIDTH & HEIGHT: width and height of the rendered window
//OPENGL_VERSION_MAJOR & OPENGLVERSION_MINOR: modify this if you need an older/newer version. Note that this will not change the version the shader uses
//BASE_VERTEX_SHADER & BASE_FRAGMENT_SHADER: the shader used if no custom shader is specified. Allows for textured
//BASE_TEXTURE: the texture used if nothing custom is speficied. It's a picture of my cat
//LINE_VERTEX_SHADER & LINE_FRAGMENT_SHADER: used for drawing lines. Changing it is not recommended unless the path is changed

#define WIDTH 800.f
#define HEIGHT 600.f
#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 6
#define BASE_TEXTURE "../CinkesRenderer/resources/images/testure.jpg"

#define BASE_VERTEX_SHADER "../CinkesRenderer/resources/shaders/CShader.vs"
#define LINE_VERTEX_SHADER "../CinkesRenderer/resources/shaders/CLineShader.vs"

#define BASE_FRAGMENT_SHADER "../CinkesRenderer/resources/shaders/CShader.fss"
#define LINE_FRAGMENT_SHADER "../CinkesRenderer/resources/shaders/CLineShader.fss"
