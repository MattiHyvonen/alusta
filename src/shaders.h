#pragma once

#include <gtkmm.h>
#include <GL/glew.h>
namespace alusta{

	/* Class for handling OpenGL shaders
	 */

	class shader{
		//TODO: copy safety etc.; deleting shaders
		//for now just check isGood() always!
	protected:
		GLuint program_id = 0;
	public:	
		//load and compile shader program from source code:
		bool loadFromSource(const char* vertexShaderSource, const char* fragmentShaderSource);
		bool loadFromFile(std::string vertexShaderFile, std::string fragmentShaderFile);
		
		//access the program ID, used by GL functions:
		//ID is positive integer, 0 on error
		GLuint getID() {return program_id;}
		
		//check if shader is good to be used:
		bool isGood();
		
		//Start using shader
		//This is mostly used internally. Mesh class contains shader
		//and always enables it when drawing. See mesh.h, mesh.cpp
		bool use();
	};
		
	//global default shader
	extern shader defaultShader;
	
	//default source codes. Defined in shaders.cpp
	extern const char* VERTEX_SHADER_SRC_DEFAULT;
	extern const char* FRAGMENT_SHADER_SRC_DEFAULT;
}