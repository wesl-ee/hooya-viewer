#include "MasonRow.h"

MasonRow::MasonRow() :
dirty{false},
currWidth{0},
clampHeight{250},
clampWidth{1500}
{
}

void MasonRow::SetMaxWidth(unsigned w) {
	clampWidth = w;
}

void MasonRow::ExpandToFillWidth() {
	std::lock_guard<std::mutex> l(content_lock);
	double ratio = clampWidth / (double)currWidth;
	for (auto &i : content) {
		i->ConstrainWidth(std::floor(i->RenderWidth() * ratio));
		i->ConstrainHeight(std::floor(i->RenderHeight() * ratio));
	}
	dirty = true;
}

void MasonRow::Draw() {
	if (dirty) {
		std::lock_guard<std::mutex> l(content_lock);
		for (auto &i : content) {
			i->Draw();
		}
	}
	toAdd.Clear([&](enqueued_t e) {
		std::lock_guard<std::mutex> l(content_lock);
		auto brick = std::move(e.src);

		add(*brick);
		brick->Draw();
		content.push_back(brick);
		show();
	});
}

bool MasonRow::Append(Glib::RefPtr<Gdk::Pixbuf> src) {
	auto brick = std::make_shared<ImageBrick>(src);
	brick->ConstrainWidth(clampBrickWidth);
	brick->ConstrainHeight(clampHeight);

	if (currWidth + brick->RenderWidth() > clampWidth)
		return false;
	currWidth += brick->RenderWidth();

	toAdd.Push(enqueued_t {
		brick,
	});

	return true;
}

void MasonRow::ClampHeight(unsigned h) {
	clampHeight = h;
}

void MasonRow::ClampBrickWidth(unsigned w) {
    clampBrickWidth = w;
}
