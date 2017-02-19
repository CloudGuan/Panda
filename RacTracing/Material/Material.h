#pragma once

#include <SDL.h>
#include "../Math/Color.h"
#include "../Math/Ray.h"

class Material 
{
public:
	//static RayTracing::Vector3	LightPost;
	//static RayTracing::Color	LightColor;
public:
	Material();
	Material(float inReflectiveness);
	~Material();
public:
	virtual RayTracing::Color Sample(RayTracing::Ray& InRay,RayTracing::Vector3& Position,RayTracing::Vector3& Normal);
protected:
	SDL_Texture*	pTexture;
	float			Reflectiveness;
};