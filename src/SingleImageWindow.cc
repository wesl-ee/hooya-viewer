#include "SingleImageWindow.h"

SingleImageWindow::SingleImageWindow(Glib::RefPtr<Gdk::Pixbuf> src) {

	set_border_width(0);
	set_title("Hooya Single Image");
	set_role("Viewer");
	add(eventBox);
	eventBox.add(frame);
	eventBox.add_events(Gdk::SCROLL_MASK);
	eventBox.signal_size_allocate().connect([&](Gtk::Allocation a) {
		data.ConstrainWidth(
			std::min(a.get_width(), data.src->get_width()));
		data.ConstrainHeight(
			std::min(a.get_height(), data.src->get_height()));

		data.Draw();
	});
	eventBox.signal_scroll_event().connect([&](GdkEventScroll *e) {
		int delta = 0;
		if (e->direction == GdkScrollDirection::GDK_SCROLL_UP) {
			delta = 10;
		} else if (e->direction == GdkScrollDirection::GDK_SCROLL_DOWN) {
			delta = -10;
		} else return true;
		Zoom(delta);
		return true;
	});
	signal_key_press_event().connect([&](GdkEventKey *e) {
		switch(e->keyval) {
		case GDK_KEY_plus:
			Zoom(10);
			break;
		case GDK_KEY_minus:
			Zoom(-10);
			break;
		}
		return true;
	});
	data.src = src;
	data.ConstrainWidth(std::min(defaultClampWidth, (unsigned)src->get_width()));
	data.ConstrainHeight(std::min(defaultClampHeight, (unsigned)src->get_height()));

	set_default_size(data.RenderWidth(), data.RenderHeight());

	frame.add(data);
	show_all_children();
}

void SingleImageWindow::Zoom(int px) {
	data.ConstrainWidth(
		std::min(data.RenderWidth() + px,
		(unsigned)data.src->get_width()));
	data.ConstrainHeight(
		std::min(data.RenderHeight() + px,
		(unsigned)data.src->get_height()));

	resize(data.RenderWidth(), data.RenderHeight());
	data.Draw();
}

void SingleImageWindow::Draw() {
	auto h = std::min(get_height(), data.src->get_height());
	auto w = std::min(get_width(), data.src->get_width());

	data.ConstrainWidth(w);
	data.ConstrainHeight(h);
	data.RenderSrc();
	data.Draw();
}
