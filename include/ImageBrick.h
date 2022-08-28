#ifndef MASON_IMAGEBRICK_H
#define MASON_IMAGEBRICK_H

#include <iostream>
#include <filesystem>
#include <gtkmm/eventbox.h>
#include <gdkmm/pixbuf.h>
#include "SingleImageWindow.h"
#include "ImageBrickData.h"

bool onButtonPress(GdkEventButton* event);

class ImageBrick : public Gtk::Frame {
public:
	ImageBrick(Glib::RefPtr<Gdk::Pixbuf> src);
	unsigned ConstrainWidth(unsigned w);
	unsigned ConstrainHeight(unsigned h);
	unsigned RenderWidth();
	unsigned RenderHeight();
	unsigned SrcWidth();
	unsigned SrcHeight();
	void Unconstrain();
	void Draw();
    ImageBrickData *Data();
private:
	std::unique_ptr<SingleImageWindow> singleImageWindow;

	Gtk::EventBox eventBox;
	bool onButtonPress(GdkEventButton *event);
	std::filesystem::path srcFile;
	ImageBrickData data;
	static const uint32_t defaultWidth = 300;
	static const uint32_t defaultHeight = 300;
    unsigned constrainWidth, constrainHeight;
};

#endif
