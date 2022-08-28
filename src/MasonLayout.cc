#include "MasonLayout.h"

MasonLayout::MasonLayout() :
clampWidth{500},
clampBrickHeight{250},
clampBrickWidth{250},
rendering{false},
dispatcher()
{
	set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
	set_row_spacing(0);
	set_column_spacing(0);

	dispatcher.connect(sigc::mem_fun(*this, &MasonLayout::onImagePendingDraw));

}

void MasonLayout::ClampWidth(unsigned w) {
	// TODO Resize rows
	clampWidth = w;
	resizeRows();
}

void MasonLayout::ClampBrickHeight(unsigned w) {
	// TODO Resize rows
	clampBrickHeight = w;
	resizeRows();
}

void MasonLayout::ClampBrickWidth(unsigned w) {
	// TODO Resize rows
	clampBrickWidth = w;
	resizeRows();
}

void MasonLayout::onImagePendingDraw() {
	updated.Clear([&](std::size_t i) {
		if (i < rows.size()) {
			rows.at(i)->Draw();
		}
	});
}

void MasonLayout::Add(Glib::RefPtr<Gdk::Pixbuf> src) {
	std::lock_guard<std::mutex> l(rows_lock);
	if (!rows.size()) {
		newRow();
	}

	if (!rows.back()->Append(src)) {
		rows.back()->ExpandToFillWidth();
		updated.Push(rows.size() - 1);

		newRow();
		rows.back()->Append(src);
	} else {
		updated.Push(rows.size() - 1);
	}

	dispatcher.emit();
}

unsigned MasonLayout::ClampWidth() {
	return clampWidth;
}

unsigned MasonLayout::ClampBrickHeight() {
	return clampBrickHeight;
}

void MasonLayout::resizeRows() {
	RemoveAll();
/*	if (!resizeThread)
		resizeThread = new std::thread([this] {
	});*/
}

bool MasonLayout::Rendering() {
	return rendering;
}

void MasonLayout::LazyLoadDirectory(std::filesystem::path d) {
	std::cout << d;
	/* loadThread = new std::thread([this, d] {
	}); */
}

void MasonLayout::Redraw(std::filesystem::path d) {
	if (rendering) {
		stopRender = true;
		loadThread->join();
		stopRender = false;
	}
	RemoveAll();
	LoadDirectory(d);
}

void MasonLayout::LoadDirectory(std::filesystem::path d) {
	loadThread = new std::thread([this, d] {
		rendering = true;
		for (const auto &f : std::filesystem::directory_iterator(d)) {
			if (stopRender)
				break;
			if (std::filesystem::is_directory(f))
				continue;
			this->Load(f);
		}
		rendering = false;
	});
}

void MasonLayout::Load(std::filesystem::path f) {
	Glib::RefPtr<Gdk::Pixbuf> src;

	try {
		src = Gdk::Pixbuf::create_from_file(f);
	} catch (Gdk::PixbufError &e) {
		switch(e.code()) {
		case Gdk::PixbufError::CORRUPT_IMAGE:
		case Gdk::PixbufError::INSUFFICIENT_MEMORY:
		case Gdk::PixbufError::BAD_OPTION:
		case Gdk::PixbufError::UNKNOWN_TYPE:
		case Gdk::PixbufError::UNSUPPORTED_OPERATION:
		case Gdk::PixbufError::FAILED:
		case Gdk::PixbufError::INCOMPLETE_ANIMATION:
			return;
		}
	}

	Add(src);
	dispatcher.emit();
}

void MasonLayout::newRow() {
	auto row = std::make_unique<MasonRow>();
	row->ClampHeight(clampBrickHeight);
	row->ClampBrickWidth(clampBrickWidth);
	row->SetMaxWidth(clampWidth);
	{
		rows.push_back(std::move(row));
	}
	add(*rows.back());
}

void MasonLayout::RemoveAll() {
	std::lock_guard<std::mutex> l(rows_lock);
	rows.clear();
}
