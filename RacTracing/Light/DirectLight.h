#pragma once

#include "RTLight.h"


class DirectLight :public RTLight 
{
public:
	DirectLight();
	DirectLight(RayTracing::Vector3&, RayTracing::Vector3&, RayTracing::Color&, bool On = false);
	~DirectLight();
public:
	/**���������Ĺ�����*/
	virtual RayTracing::Color Intersect(Object* Scene, IntersectResult& HitPos)override;
private:
	/**ƽ�й�Դ�����䷽��*/
	RayTracing::Vector3 Direction;
};
