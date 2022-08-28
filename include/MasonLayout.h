#ifndef MASON_MASONLAYOUT_H
#define MASON_MASONLAYOUT_H

#include <filesystem>
#include <vector>
#include <thread>
#include <glibmm/dispatcher.h>
#include <gtkmm/container.h>
#include <gtkmm/grid.h>
#include "AtomicQ.h"
#include "MasonRow.h"
#include "ImageBrick.h"

class MasonLayout : public Gtk::Grid {
public:
	MasonLayout();
	void Add(Glib::RefPtr<Gdk::Pixbuf> src);
	void LoadDirectory(std::filesystem::path d);
	void LazyLoadDirectory(std::filesystem::path d);
	void Load(std::filesystem::path f);
	void RemoveAll();
	void ClampBrickHeight(unsigned w);
	unsigned ClampBrickHeight();
	void ClampBrickWidth(unsigned w);
	unsigned ClampBrickWidth();
	void ClampWidth(unsigned w);
	unsigned ClampWidth();
	bool Rendering();
	void Redraw(std::filesystem::path d);
private:
	void onImagePendingDraw();
	void resizeRows();

	unsigned clampWidth;
	unsigned clampBrickHeight, clampBrickWidth;
	bool rendering, stopRender;
	std::vector<std::unique_ptr<MasonRow>> rows;
	std::vector<ImageBrick*> displayed;
	Glib::Dispatcher dispatcher;
	AtomicQ<std::size_t> updated;

	std::thread *loadThread;
	mutable std::mutex rows_lock;

	void newRow();
};

#endif
