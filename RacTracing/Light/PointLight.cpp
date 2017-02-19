
#include "PointLight.h"

PointLight::PointLight(RayTracing::Vector3& Pos, RayTracing::Color& InIrr, bool On)
	:RTLight(Pos,InIrr,On)
{

}

PointLight::~PointLight()
{

}

RayTracing::Color PointLight::Intersect(Object* Scene, IntersectResult& HitPos)
{

}

