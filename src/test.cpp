#include "alusta.h"

/* Example
 * 
 * Inherit window class from alusta::mainWindow
 * Run Gtk app in main() using the window
 * Define mesh data, 2 meshes and a custom shader which is loaded from files
 * Change vertex data in update step and draw the meshes
 */

class glTestWindow : public alusta::mainWindow {

	alusta::shader triangleShader;
	alusta::mesh testRectangle;
	alusta::mesh testTriangle;

	std::vector<glm::vec3> vertices_A = {
		glm::vec3(-0.5f,  0.5f, 0),
		glm::vec3( 0.5f,  0.5f, 0),
		glm::vec3( 0.5f, -0.5f, 0),
		glm::vec3(-0.5f, -0.5f, 0)
	};
	std::vector<glm::vec3> colors_A = {
		glm::vec3( 1.0f,  0.0f, 0.0f),
		glm::vec3( 0.0f,  1.0f, 0.0f),
		glm::vec3( 0.0f,  0.0f, 1.0f),
		glm::vec3( 1.0f,  1.0f, 1.0f)
	};
	std::vector<glm::uvec3> faces_A = {
		glm::uvec3(0, 1, 2),
		glm::uvec3(2, 3, 0)
	};
	std::vector<glm::vec3> vertices_B = {
		glm::vec3(-0.8f, -0.7f, 0),
		glm::vec3( 0.8f,  0.0f, 0),
		glm::vec3(-0.6f, -0.2f, 0)
	};
	std::vector<glm::vec3> colors_B = {
		glm::vec3( 1.0f,  1.0f, 1.0f),
		glm::vec3( 1.0f,  1.0f, 1.0f),
		glm::vec3( 0.0f,  0.0f, 1.0f)
	};
	std::vector<glm::uvec3> faces_B = {
		glm::uvec3(0, 1, 2)
	};	
	
	void setup(){
		
		triangleShader.loadFromFile("data/shaders/custom.vertexShader",
		"data/shaders/custom.fragmentShader"
		);
		testTriangle.setShader(triangleShader);
		
		testRectangle.setVertices(vertices_A);
		testRectangle.setColors(colors_A);
		testRectangle.setFaces(faces_A);
		
		testTriangle.setVertices(vertices_B);
		testTriangle.setColors(colors_B);
		testTriangle.setFaces(faces_B);

	}

	
	void update(){
		vertices_B[0] += glm::vec3(0.01, 0.01, 0);
		testTriangle.setVertices(vertices_B);
		if(vertices_B[0].x > 1)
			vertices_B[0].x = -1;
		if(vertices_B[0].y > 1)
			vertices_B[0].y = -1;
	}
	
	
	void render(){
		testRectangle.draw();
		testTriangle.draw();
	}
};


int main(int argc, char *argv[]) {
	auto app = Gtk::Application::create("mainApp");
	glTestWindow window;
	app->run(window);
	return 0;
}
