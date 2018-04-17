#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture* image);
	ImageRenderer(Texture * image, Vector2D numFrames, Vector2D frame);

	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
	SDL_Rect getDestRect(GameObject * o); // calcula el Rect de destino

private:
	Texture* image_;
	SDL_Rect rectFrame;
	Vector2D numFrames_ = { 1,1 };
	Vector2D frame_ = { 0,0 };
};

#endif /* IMAGERENDERER_H_ */
