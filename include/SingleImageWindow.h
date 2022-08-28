#ifndef SINGLEIMAGEWINDOW_H
#define SINGLEIMAGEWINDOW_H

#include <iostream>
#include <filesystem>
#include <cmath>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/eventbox.h>
#include <glibmm/dispatcher.h>
#include "ImageBrickData.h"

class SingleImageWindow : public Gtk::Window {
public:
	SingleImageWindow(Glib::RefPtr<Gdk::Pixbuf> src);
	void Draw();
	void Zoom(int px);
private:
	ImageBrickData data;
	Gtk::Image image;
	Gtk::Frame frame;
	Gtk::Grid grid;
	Gtk::EventBox eventBox;

	unsigned defaultClampWidth = 300;
	unsigned defaultClampHeight = 300;
};

#endif
