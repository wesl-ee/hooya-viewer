#include "ImageBrick.h"

ImageBrick::ImageBrick(Glib::RefPtr<Gdk::Pixbuf> src) :
constrainWidth{0},
constrainHeight{0}
{
	data.src = src;
	set_border_width(0);
	set_shadow_type(Gtk::SHADOW_NONE);
	add(eventBox);
	eventBox.add(data);
	eventBox.signal_button_press_event().connect([&](GdkEventButton *event) {
		return onButtonPress(event);
	});
}

bool ImageBrick::onButtonPress(GdkEventButton *event) {
	if (event->type == GdkEventType::GDK_2BUTTON_PRESS) {
		singleImageWindow = std::make_unique<SingleImageWindow>(data.src);
		singleImageWindow->show();
		singleImageWindow->Draw();
	}
	return true;
}

unsigned ImageBrick::ConstrainWidth(unsigned w) {
	return data.ConstrainWidth(w);
}

void ImageBrick::Unconstrain() {
	return data.Unconstrain();
}

unsigned ImageBrick::ConstrainHeight(unsigned h) {
	return data.ConstrainHeight(h);
}

unsigned ImageBrick::RenderWidth() {
	return data.RenderWidth();
}

unsigned ImageBrick::RenderHeight() {
	return data.RenderHeight();
}

unsigned ImageBrick::SrcHeight() {
	return data.src->get_height();
}

unsigned ImageBrick::SrcWidth() {
	return data.src->get_width();
}

void ImageBrick::Draw() {
	data.Draw();
	show_all();
}

