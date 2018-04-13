#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image) : image_(image) 
{
	rectFrame.h = image_->getHeight() / numFrames_.getY();
	rectFrame.w = image_->getWidth() / numFrames_.getX();
	rectFrame.x = 0;
	rectFrame.y = 0;
}

ImageRenderer::ImageRenderer(Texture * image, Vector2D numFrames, Vector2D frame):
	image_(image),numFrames_(numFrames), frame_(frame)
{
	rectFrame.h = image_->getHeight() / numFrames_.getY();
	rectFrame.w = image_->getWidth() / numFrames_.getX();
	rectFrame.x = rectFrame.w * frame.getX();
	rectFrame.y = rectFrame.h * frame.getY();
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	Vector2D v(0, 1);
	double a = o->getDirection().angle(v);
	image_->render(o->getGame()->getRenderer(), getDestRect(o), a, &rectFrame);
}

SDL_Rect ImageRenderer::getDestRect(GameObject* o) {
	SDL_Rect rect
		RECT(o->getPosition().getX(), o->getPosition().getY(),
			o->getWidth(), o->getHeight());
	return rect;
}
