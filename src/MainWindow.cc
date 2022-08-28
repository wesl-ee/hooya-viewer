#include "MainWindow.h"

MainWindow::MainWindow(std::filesystem::path d) :
lastWidth{0},
lastHeight{0},
readyToRedraw{true} {
	imageDirectory = d;

	set_title("Hooya Viewer");
	set_border_width(0);

	set_default_size(defaultHeight, defaultWidth);

	lastWidth = defaultWidth;
	lastHeight = defaultHeight;

	add(frame);
	frame.add(scrollWindow);
	scrollWindow.add(masonLayout);

	show_all_children();

	masonLayout.ClampBrickHeight(150);
	masonLayout.ClampBrickWidth(250);

	signal_realize().connect([&, d] {
	});

	signal_configure_event().connect([&, d](GdkEventConfigure *event) {
		if (lastWidth == 0) {
			masonLayout.ClampWidth(event->width);
			masonLayout.LoadDirectory(d);
		}
		uint32_t allocWidth = event->width;
		if (lastWidth != allocWidth) {
			lastWidth = allocWidth;
			if (readyToRedraw) {
				readyToRedraw = false;
				Glib::signal_timeout().connect([&]() {
					masonLayout.ClampWidth(get_width());
					masonLayout.Redraw(d);
					readyToRedraw = true;
					return false;
				}, 1000);
			} else {
			}
		}
		return false;
	}, false);
}

MainWindow::~MainWindow() {
}
