#include "mesh.h"
#include "shaders.h"

namespace alusta {

	bool mesh::generateBuffers() {
		if (mainWindow::isInitialized()) {
			//use the default shader to draw the mesh
			mshader = defaultShader;
			mshader.use();
			//generate 1 vertex array object
			glGenVertexArrays(1, &vao);
			//generate vertex buffer objects vbo for vertices and cbo for colors, and element buffer object ebo for faces
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &cbo);
			glGenBuffers(1, &ebo);
			good = true;
			return true;
		} 
		else {
			return false;
		}
	}

	mesh::mesh() {
		generateBuffers();
		#ifdef MESH_DEBUG
		if (good)
			std::cout << "mesh::mesh: created mesh\n";
		else
			std::cout << "mesh::mesh: buffers not created\n";
		#endif
		
	}

	void mesh::setVertices(const std::vector<glm::vec3>& newVertices) {
		if (!good)
			generateBuffers();
		if (good) {
			mshader.use();
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			GLint posAttrib = glGetAttribLocation(mshader.getID(), "position");
			glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(posAttrib);
			glBufferData(GL_ARRAY_BUFFER, newVertices.size() * sizeof(glm::vec3), &newVertices[0], GL_STATIC_DRAW);
		}
	}

	void mesh::setFaces(const std::vector<glm::uvec3>& newFaces) {
		if (!good)
			generateBuffers();
		if (good) {
			mshader.use();
			glBindVertexArray(vao);
			numberOfFaces = newFaces.size();
			//TODO: check index validity
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, newFaces.size() * sizeof(glm::uvec3), &newFaces[0], GL_STATIC_DRAW);
		}
	}

	void mesh::setColors(const std::vector<glm::vec3>& newColors) {
		if (!good)
			generateBuffers();
		if (good) {
			mshader.use();
			glBindVertexArray(vao);
			GLint colAttrib = glGetAttribLocation(mshader.getID(), "color");
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(colAttrib);
			glBufferData(GL_ARRAY_BUFFER, newColors.size() * sizeof(glm::vec3), &newColors[0], GL_STATIC_DRAW);
		}
	}
	
	
	bool mesh::setShader(shader newShader) {
		if (!good)
			generateBuffers();
		if(newShader.isGood() ) {
			mshader = newShader;
			return true;
		}
		else return false;
	}

	
	void mesh::draw() {
		if (!good)
			generateBuffers();
		if (good) {
			mshader.use();
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, numberOfFaces * 3, GL_UNSIGNED_INT, 0);
		} else {
			#ifdef MESH_DEBUG
			std::cerr << "mesh::draw : bad mesh\n";
			#endif
		}
	}
};