#include "mainApp.h"
#include "mesh.h"
#include "shaders.h"
#include <iostream>

namespace alusta {

	bool mainWindow::initialized = false;
	
	mainWindow::mainWindow() {
		set_title("OpenGL window");
		set_default_size(640, 512);

		add(drawingArea);
		drawingArea.set_auto_render();

		//to prevent scaling down:
		drawingArea.set_size_request(640, 512);

		drawingArea.set_required_version(3, 2);

		drawingArea.signal_realize().connect(
			sigc::mem_fun(this, &mainWindow::onRealize)
			);

		drawingArea.signal_unrealize().connect(
			sigc::mem_fun(this, &mainWindow::onUnrealize),
			false
			);
		drawingArea.signal_render().connect(
			sigc::mem_fun(this, &mainWindow::onRender)
			);
		//TODO: this timing might not be precise!
		Glib::signal_timeout().connect(
			sigc::mem_fun(this, &mainWindow::onTimeout), 16.6667 //about 60 fps
			);

		drawingArea.show();
	}

	void mainWindow::setClearing(bool enableClearing) {
		clearing = enableClearing;
	}

	void mainWindow::onRealize() {
		drawingArea.make_current();
		glewExperimental = true; //GLArea only supports Core profile
		if (glewInit() != GLEW_OK) {
			std::cerr << "ERROR: Failed to initialize GLEW. (Maybe the OpenGL context not exist)" << std::endl;
		}
		
		initialized = true;

		//make the default shader
		defaultShader.loadFromSource(VERTEX_SHADER_SRC_DEFAULT, FRAGMENT_SHADER_SRC_DEFAULT);
		if(!defaultShader.use() )
			std::cerr << "couldn't load shader\n";
		
		//run the user-defined setup
		setup();
	}

	void mainWindow::onUnrealize() {
		//TODO: free some resources
	}

	bool mainWindow::onRender(const Glib::RefPtr<Gdk::GLContext>& context) {
		if (clearing)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();
		return true;
	}

	bool mainWindow::onTimeout() {		
		//run the user-defined update function
		update();

		//invalidate the area inside the window to redraw it
		auto win = get_window();
		if (win) {
			Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
			win->invalidate_rect(r, false);
		}
		
		return true;
	}

	void mainWindow::render() {
		#ifdef MAINAPP_DEBUG
		std::cerr << "default render\n";
		#endif
	}

	
	void mainWindow::update() {
		#ifdef MAINAPP_DEBUG
		std::cerr << "default update\n";
		#endif
	}
	
	
	void mainWindow::setup() {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		#ifdef MAINAPP_DEBUG
		std::cerr << "default setup\n";
		#endif
	}
};