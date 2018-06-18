#include "shaders.h"
#include "filesystem.h"
#include "mainApp.h"

#include <iostream>

namespace alusta{

	bool shader::loadFromSource(const char* vertexShaderSource, const char* fragmentShaderSource) {
		if(!mainWindow::isInitialized() )
			return false;
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		//check if compiled
		GLint status;
		char buffer[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			std::cerr << "vertex shader didn't compile!\n";
			glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
			std::cerr << buffer;
			return false;
		}
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			std::cerr << "fragments shader didn't compile!\n";
			glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
			std::cerr << buffer;
			return false;
		}
		program_id = glCreateProgram();
		glAttachShader(program_id, vertexShader);
		glAttachShader(program_id, fragmentShader);

		glBindFragDataLocation(program_id, 0, "outColor"); //this would happen anyway by default though
		glLinkProgram(program_id);
		return true;
	}
	
	bool shader::loadFromFile(std::string vertexShaderFile, std::string fragmentShaderFile) {
		std::string vertexSource = loadFileAsString(vertexShaderFile);
		std::string fragmentSource = loadFileAsString(fragmentShaderFile);
		return loadFromSource(vertexSource.c_str(), fragmentSource.c_str() );	
	}

	
	bool shader::isGood() {
		//TODO: check everything
		if(program_id == 0)
			return false;
		else return true;
	}
	
	
	bool shader::use() {
		if(!mainWindow::isInitialized() )
			return false;
		
		if(this->isGood()) {
			glUseProgram(program_id);
			return true;
		}
		else return false;
	}

	shader defaultShader;
	
	const char* VERTEX_SHADER_SRC_DEFAULT =
		R"glsl(
		#version 150 core

		in vec3 position;
		in vec3 color;

		out vec3 vertexColor;

		void main() {
			vertexColor = color;
			gl_Position = vec4(position.xy, 0.0, 1.0);
		}
		)glsl";	

	const char* FRAGMENT_SHADER_SRC_DEFAULT =
		R"glsl(
		#version 150 core

		in vec3 vertexColor;

		out vec4 outColor;

		void main()
		{
			outColor = vec4(vertexColor.rgb, 1);
		}
		)glsl";

	
};
