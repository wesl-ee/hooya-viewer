#include "ImageBrickData.h"

ImageBrickData::ImageBrickData() :
lastRenderWidth{0},
lastRenderHeight{0},
clampHeight{0},
clampWidth{0},
renderHeight{0},
renderWidth{0}
{
}

void ImageBrickData::RenderSrc() {
	if (!renderWidth)
		renderWidth = src->get_width();
	if (!renderHeight)
		renderHeight = src->get_height();
	auto surface = Gdk::Cairo::create_surface_from_pixbuf(src, 1);

	rendered = src->scale_simple(
		renderWidth / PREVIEW_SCALE_FACTOR,
		renderHeight / PREVIEW_SCALE_FACTOR,
		Gdk::InterpType::INTERP_BILINEAR);
	set_size_request(renderWidth, renderHeight);
}

unsigned ImageBrickData::ScaledWidth(unsigned h) {
	return std::round(src->get_width() * (h / (double)src->get_height()));
}

unsigned ImageBrickData::ScaledHeight(unsigned w) {
	return std::round(src->get_height() * (w / (double)src->get_width()));
}

unsigned ImageBrickData::RenderWidth() {
	return renderWidth;
}

unsigned ImageBrickData::RenderHeight() {
	return renderHeight;
}

unsigned ImageBrickData::ConstrainWidth(unsigned w) {
	clampWidth = w;

	if (clampHeight)
		renderWidth = std::min(ScaledWidth(clampHeight), clampWidth);
	else
		renderWidth = clampWidth;

	renderHeight = std::min(ScaledHeight(clampWidth), clampHeight);

	return renderHeight;
}

unsigned ImageBrickData::ConstrainHeight(unsigned h) {
	clampHeight = h;

	if (clampWidth)
		renderHeight = std::min(ScaledHeight(clampWidth), clampHeight);
	else
		renderHeight = clampHeight;

	renderWidth = std::min(ScaledWidth(clampHeight), clampWidth);

	return renderWidth;
}

void ImageBrickData::Unconstrain() {
	clampWidth = 0;
	clampHeight = 0;
}

Glib::RefPtr<Gdk::Pixbuf> ImageBrickData::Rendered() {
	return rendered;
}

void ImageBrickData::Draw() {
	if (lastRenderWidth != renderWidth || lastRenderHeight != renderHeight) {
		lastRenderWidth = renderWidth;
		lastRenderHeight = renderWidth;
		RenderSrc();
	}

	show();
}

bool ImageBrickData::on_draw(const Cairo::RefPtr<Cairo::Context> &ct) {
	ct->scale(
		PREVIEW_SCALE_FACTOR,
		PREVIEW_SCALE_FACTOR);
	Gdk::Cairo::set_source_pixbuf(ct, rendered);
	ct->paint();

	return true;
}

