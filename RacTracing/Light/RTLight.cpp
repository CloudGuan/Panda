#include "RTLight.h"

RTLight::RTLight()
	:Position(0,0,0)
	, Irradiance(RayTracing::Color::White)
	,bShadow(false)
{

}

RTLight::RTLight(RayTracing::Vector3& inPos, RayTracing::Color& inIrr, bool On/*=false*/)
	:Position(inPos)
	,Irradiance(inIrr)
	,bShadow(On)
{

}

RTLight::~RTLight()
{

}

RayTracing::Color RTLight::Intersect(Object* Scene,IntersectResult& HitPos)
{
	return RayTracing::Color::Black;
}

