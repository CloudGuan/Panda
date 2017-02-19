#pragma once

#include <SDL.h>
#include "Math/Ray.h"
#include "Core/RScene.h"

struct WRect 
{
	int Width;
	int Heigh;
};

class RenderEngine 
{
public:
	RenderEngine();
	~RenderEngine();
public:
	bool Initialize(int x,int y,int width,int heigh);
	bool Draw();
	RayTracing::Color RayTracingRender(Rscene* Scene, RayTracing::Ray&, int Maxref);
private:
	SDL_Window*		pWindows;
	SDL_Renderer*	pRenderer;
	SDL_Texture*	pTexture;
	bool			bLoop;
	/***/
	WRect			WindInfo;
};
