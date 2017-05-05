
#include "Render.h"
#include "Core/Sphere.h"
#include "Core/Camera.h"

#include "Core/Plane.h"
#include "Light/DirectLight.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"

#include <SDL_render.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <time.h>


RenderEngine::RenderEngine()
	:pWindows(nullptr)
	,pRenderer(nullptr)
	,pTexture(nullptr)
	,bLoop(false)
{

}

RenderEngine::~RenderEngine()
{
	if(pRenderer)
		SDL_DestroyRenderer(pRenderer);
	if(pWindows)
		SDL_DestroyWindow(pWindows);
	SDL_Quit();
}

bool RenderEngine::Initialize(int x, int y, int width, int heigh)
{
	WindInfo.Width = width;
	WindInfo.Heigh = heigh;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		return false;
	}
	pWindows = SDL_CreateWindow("Ray Tracing", x, y, WindInfo.Width, WindInfo.Heigh, SDL_WINDOW_SHOWN);
	if (pWindows == nullptr) {
		return false;
	}
	pRenderer = SDL_CreateRenderer(pWindows, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (pRenderer == nullptr) 
	{
		return false;
	}
#ifdef _DEBUG
	SDL_RendererInfo RInfo;
	SDL_GetRendererInfo(pRenderer, &RInfo);
	std::cout << "Renderer Name: "<<RInfo.name<<std::endl;
	for (Uint32 i=0;i<RInfo.num_texture_formats;i++)
	{
		std::cout << SDL_GetPixelFormatName(RInfo.texture_formats[i])<<'\t';
	}
	std::cout << std::endl;
#endif
	
	SDL_RenderSetLogicalSize(pRenderer, WindInfo.Width, WindInfo.Heigh);
	
	pTexture = SDL_CreateTexture(
		pRenderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WindInfo.Width, WindInfo.Heigh
	);
	bLoop = true;
	return true;
}

bool RenderEngine::Draw()
{
	SDL_Event hEvent;
	Initialize(100,100,500,500);
	//SDL_Color RenderColor;
	//Sphere SingleSphere(RayTracing::Vector3(0,10,-10),10.0);
	//Plane  SinglePlane(RayTracing::Vector3(0,1,0),5.0);

	Rscene TargetScene;
	//TargetScene.AddObject(new Sphere(RayTracing::Vector3(0.0,10.0,-10.0), 8.0));
	//TargetScene.AddObject(new Plane(RayTracing::Vector3(0.0, 1.0, 0.0), 0.0));
	//TargetScene.AddObject(new Plane(RayTracing::Vector3(0.0, 0.0, 1.0), -50.0));
	//TargetScene.AddObject(new Plane(RayTracing::Vector3(1.0, 0.0, 0.0), -20.0));
	TargetScene.LoadMesh();

	TargetScene.AddLights(new DirectLight(
		RayTracing::Vector3(1.0,1.0,1.0), 
		RayTracing::Vector3(-1.75, -2.0, -1.5),
		RayTracing::Color::White,false));

	/*TargetScene.AddLights(new PointLight(
		RayTracing::Vector3(30.0, 40.0, 20.0),
		RayTracing::Color::White,
		true
	));*/

	/*TargetScene.AddLights(new SpotLight(
		RayTracing::Vector3(30.0, 40.0, 20.0),
		RayTracing::Color(0.0,0.0,1.0,1.0),
		RayTracing::Vector3(-1.0, -1.0, -1.0),
		20,
		30));*/

	Camera Eye(RayTracing::Vector3(0,10,10),RayTracing::Vector3(0,0,-1),RayTracing::Vector3(0,1,0),90);

	
	

	int index = 0;
	/**预先计算好能够更快一些*/
	double dx = 1.0 / WindInfo.Width;
	double dy = 1.0 / WindInfo.Heigh;
	double dDepth = 255.0 / 20;
	Uint8* piexl = nullptr; //new Uint8[WindInfo.w*WindInfo.h*4];

	SDL_Rect TextureRect;
	TextureRect.x = 0;
	TextureRect.y = 0;
	TextureRect.w = WindInfo.Width;
	TextureRect.h = WindInfo.Heigh;

	RayTracing::Color OutColor;
	while (bLoop) 
	{	
		while (SDL_PollEvent(&hEvent))
		{
			switch (hEvent.type)
			{
			case SDL_QUIT:
			{
				bLoop = false;
				break;
			}
			case SDL_KEYDOWN:
			{

				RayTracing::Ray SingleRay(Eye.GenerateRay(0.5,0.5));
				RayTracingRender(&TargetScene, SingleRay, 2);
				printf_s("ButtonDown!!!");
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				clock_t mStartTime = clock();
				/**循环来使用*/
				SDL_RenderClear(pRenderer);
				//SDL_Color RenderColor;
				//SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
				//SDL_RenderDrawLine(pRenderer, 100, 100,150,150);
				int res = SDL_LockTexture(pTexture, &TextureRect, reinterpret_cast<void**>(&piexl), &index);

				for (int col = 0; col < WindInfo.Heigh; col++)
				{
					double sy = 1 - col*dy;
					for (int raw = 0; raw < WindInfo.Width; raw++)
					{
						double sx = raw*dx;
						RayTracing::Ray SingleRay(Eye.GenerateRay(sx, sy));
						//IntersectResult HitRes = TargetScene.Intersect(SingleRay,OutColor);
						OutColor = RayTracingRender(&TargetScene, SingleRay,1);
						int offset = (col*WindInfo.Width + raw) * 4;
						//bgra
						//Uint8 depth =255-SDL_min(HitRes.Distance*dDepth,255.0f);
						OutColor.Standardizing();
						piexl[offset + 0] = OutColor.b * 255;
						piexl[offset + 1] = OutColor.g * 255;
						piexl[offset + 2] = OutColor.r * 255;
						piexl[offset + 3] = 255;
						
					}
				}
				clock_t mEndTime = clock();
				printf_s("Time is： %f\n", (float)(mEndTime - mStartTime) / CLOCKS_PER_SEC);
				SDL_UnlockTexture(pTexture);
				SDL_RenderCopy(pRenderer,pTexture, NULL, NULL);
				SDL_RenderPresent(pRenderer);
				//mEndTime = clock();
				//printf_s("Time is： %f\n", (float)(mEndTime - mStartTime) / CLOCKS_PER_SEC);
				break;
			}
			default:
				break;
			}
		}
	}
	/*if(piexl)
		delete[] piexl;*/
	return bLoop;
}

RayTracing::Color RenderEngine::RayTracingRender(Rscene* Scene, RayTracing::Ray& InRay, int Maxref)
{
	if (Maxref < 1)
		return RayTracing::Color::Black;

	RayTracing::Color TempColor;
	IntersectResult HitRes = Scene->DrawCall(InRay,TempColor);
	if (HitRes.Geometry&&Maxref>1) 
	{
		RayTracing::Vector3 RefDir = HitRes.Normal*(-2 * HitRes.Normal.dot(InRay.GetDirection())) + InRay.GetDirection();
		RayTracing::Ray RefRay(HitRes.Position, RefDir.normalize());
		TempColor = TempColor*0.75 + RayTracingRender(Scene, RefRay, Maxref - 1)*0.25;
	}

	return TempColor;
}

