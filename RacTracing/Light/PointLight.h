#pragma once

#include "RTLight.h"

/**
*	点光源，照射幅和点到光源的距离成反比
*/

class PointLight :public RTLight 
{
public:
	PointLight()=default;
	PointLight(RayTracing::Vector3&,RayTracing::Color&,bool On);
	~PointLight();

	virtual RayTracing::Color Intersect(Object* Scene, IntersectResult& HitPos);
};