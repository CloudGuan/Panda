#pragma once

#include "RTLight.h"


class DirectLight :public RTLight 
{
public:
	DirectLight();
	DirectLight(RayTracing::Vector3&, RayTracing::Vector3&, RayTracing::Color&, bool On = false);
	~DirectLight();
public:
	/**计算这个点的光照量*/
	virtual RayTracing::Color Intersect(Object* Scene, IntersectResult& HitPos)override;
private:
	/**平行光源的照射方向*/
	RayTracing::Vector3 Direction;
};
