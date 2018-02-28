#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image) : image_(image) {
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	Vector2D v(0, -1);
	image_->render(o->getGame()->getRenderer(), getDestRect(o), v.angle(o->getDirection()));
}


void ImageRenderer::render(GameObject* o, Uint32 time, double angle) {
	image_->render(o->getGame()->getRenderer(), getDestRect(o), angle);
}

SDL_Rect ImageRenderer::getDestRect(GameObject* o){
	SDL_Rect rect
		RECT(o->getPosition().getX(), o->getPosition().getY(),
		o->getWidth(), o->getHeight());
	return rect;
}
