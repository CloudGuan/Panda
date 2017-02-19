#include "CheckMaterial.h"

#include <windows.h>

CheckMaterial::CheckMaterial(float xs, float zs)
	:XScale(xs)
	,ZScale(zs)
{

}

CheckMaterial::~CheckMaterial()
{

}

RayTracing::Color CheckMaterial::Sample(RayTracing::Ray& InRay, RayTracing::Vector3& Position, RayTracing::Vector3& Normal)
{
	return (SDL_abs(SDL_floor(Position.mx*XScale) + SDL_floor(Position.mz*ZScale)) % 2)< 1 ? RayTracing::Color::White : RayTracing::Color::Black;
}

