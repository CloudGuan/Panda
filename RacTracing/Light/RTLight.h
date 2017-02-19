#pragma once

#include "../Math/Color.h"
#include "../Math/Ray.h"
#include "../Core/Object.h"

class RTLight 
{
public:
	RTLight();
	RTLight(RayTracing::Vector3&, RayTracing::Color&,bool On=false);
	~RTLight();

	void TurnOnShadow() { bShadow = true; };
	void TurnOffShadow() { bShadow = false; };

	virtual RayTracing::Color Intersect(Object* Scene,IntersectResult& HitPos);
protected:
	RayTracing::Vector3 Position;
	RayTracing::Color	Irradiance;
	bool				bShadow;
};