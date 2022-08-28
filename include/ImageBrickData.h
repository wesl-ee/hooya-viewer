#ifndef MASON_IMAGEBRICKDATA_H
#define MASON_IMAGEBRICKDATA_H

#include <cmath>
#include <iostream>
#include <filesystem>
#include <gtkmm.h>
#include <gdkmm/pixbuf.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>

#define PREVIEW_SCALE_FACTOR 0.5

class ImageBrickData: public Gtk::DrawingArea {
public:
	Glib::RefPtr<Gdk::Pixbuf> src;

	ImageBrickData();
	void FromFile(std::filesystem::path p);
	void RenderSrc();
	Glib::RefPtr<Gdk::Pixbuf> Rendered();
	unsigned ConstrainHeight(unsigned h);
	unsigned ConstrainWidth(unsigned w);
	unsigned RenderHeight();
	unsigned RenderWidth();
	unsigned ScaledWidth(unsigned h);
	unsigned ScaledHeight(unsigned w);
	void Unconstrain();
	bool onButtonPress(GdkEventButton *event);
	void Draw();
private:
	Glib::RefPtr<Gdk::Pixbuf> rendered;

	unsigned lastRenderWidth, lastRenderHeight, clampHeight, clampWidth, renderHeight, renderWidth;
	double aspectRatio;
protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
};

#endif
