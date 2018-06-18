#pragma once

#include "mainApp.h"
#include "shaders.h"
#include <glm/glm.hpp>
#include <iostream>

//define MESH_DEBUG to print useful information to stdout & stderr
//#define MESH_DEBUG

namespace alusta{
	
	/* Class for drawing meshes using OpenGL
	 * 
	 * Contains buffer objects for vertices, colors &c.
	 * Note: mesh class doesn't contain any vertex data and such
	 * It just handles writing to the OpenGL buffers
	  
	 * TODO: problems:
	 * mesh object is not copyable! Copy safety, deletion & such for buffer objects
	 */
	
	class mesh {
	protected:		
		//the shader that is used for drawing:
		shader mshader;
		
		bool good = false;
		GLuint vao;
		GLuint vbo;
		GLuint cbo; //vertex buffer for colors
		GLuint ebo; //element buffer ie. faces
		GLuint numberOfFaces = 0;
		
		//generateBuffers():
		//Generate buffer objects, set default shader, and set good = true.
		//This is required to call any GL functions on the mesh.
		//Fails if OpenGL is not initialized. 
		//Be sure this is run in mainWindow::setup() or after.
		bool generateBuffers();
		
	public:
		mesh();
		
		//check if the mesh is ready for drawing & other GL stuff
		bool isGood();
		
		//write mesh data to the buffer 
		//These also try to run generateBuffers if not run yet
		void setVertices(const std::vector<glm::vec3>& vertices);
		void setFaces(const std::vector<glm::uvec3>& faces);
		void setColors(const std::vector<glm::vec3>& colors);
		
		bool setShader(shader newShader);
		void draw();
	};
}