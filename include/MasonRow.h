#ifndef MASON_MASONROW_H
#define MASON_MASONROW_H

#include <cmath>
#include <iostream>
#include <algorithm>
#include <gtkmm/grid.h>
#include "AtomicQ.h"
#include "ImageBrick.h"

typedef struct enqueued_t {
	std::shared_ptr<ImageBrick> src;
} enqueued_t;

class MasonRow : public Gtk::Grid {
public:
	MasonRow();
	void Draw();
	bool Append(Glib::RefPtr<Gdk::Pixbuf> src);
	void ClampHeight(unsigned h);
	void ClampBrickWidth(unsigned w);
	void ExpandToFillWidth();
	void SetMaxWidth(unsigned w);
	bool Has(ImageBrick*);
private:
	bool dirty;
	std::vector<std::shared_ptr<ImageBrick>> content;
	unsigned currWidth, clampHeight, clampWidth, clampBrickWidth;
	AtomicQ<enqueued_t> toAdd;
	mutable std::mutex content_lock;
};

#endif
