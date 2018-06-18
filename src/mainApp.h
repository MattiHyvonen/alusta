#pragma once

#include <gtkmm.h>
#include <GL/glew.h>

#include <string>

#define MAINAPP_DEBUG

namespace alusta{

	class mainWindow : public Gtk::Window {
	protected: 
		static bool initialized;
	public: 
		//check if OpenGL is initialized & GL functions can be run:
		static bool isInitialized() {return initialized;}

	public:
		mainWindow();

		void setClearing(bool enableClearing = true);

		/* setup() is called after OpenGL is initialized. You can run GL
		 * functions in setup() but generally not before.
		 
		 * draw cycle:
		 * Timeout event calls update() at 60 fps.
		 * After update() a render event is sent, which calls render()
		 
		 * Update keeps pretty well on time. If it takes too long, render() will
		 * drop frames.
		 */
		
		//user defineable virtual functions:
		virtual void setup(); //this is run on realize event
		virtual void update(); //this is run on timeout event at 60 fps
		virtual void render(); //this is run on render event

	protected:
		Gtk::GLArea drawingArea;
		bool clearing = true;

		//event functions
		void onRealize();
		void onUnrealize();
		bool onRender(const Glib::RefPtr<Gdk::GLContext>& context);
		bool onTimeout();
	};

}