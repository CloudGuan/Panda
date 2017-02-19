#pragma once

#include "RTLight.h"

class PointLight :public RTLight 
{
public:
	PointLight()=default;
	PointLight(RayTracing::Vector3&,RayTracing::Color&,bool On);
	~PointLight();

	virtual RayTracing::Color Intersect(Object* Scene, IntersectResult& HitPos);
};