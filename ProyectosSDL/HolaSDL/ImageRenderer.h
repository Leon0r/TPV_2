#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture* image);
	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
	virtual void render(GameObject* o, Uint32 time, double angle);
	
private:
	Texture* image_;
	virtual SDL_Rect getDestRect(GameObject* o);
};

#endif /* IMAGERENDERER_H_ */
