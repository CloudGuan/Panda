#pragma once
#include "RTLight.h"

class SpotLight :public RTLight 
{
public:
	SpotLight()=default;
	SpotLight(RayTracing::Vector3&,RayTracing::Color&,RayTracing::Vector3&,int T,int O);
	~SpotLight();

	virtual RayTracing::Color Intersect(Object* Scene, IntersectResult& HitPos);
private:
	RayTracing::Vector3 Direction;
	double HalfTheta;
	double HalfO;
	double SubTO;
};