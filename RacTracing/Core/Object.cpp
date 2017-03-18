#include "Object.h"

Object::Object()
	:pMaterial(nullptr)
{

}

Object::~Object()
{
	if (pMaterial) 
	{
		delete pMaterial;
		pMaterial=nullptr;
	}
}

IntersectResult Object::Intersect(RayTracing::Ray& In)
{
	return IntersectResult::NoHit;
}

void Object::DrawMaterial(RayTracing::Ray& InRay, RayTracing::Vector3& Position, RayTracing::Vector3& Normal,RayTracing::Color& OutColor)
{
	if (pMaterial)
	{
		RayTracing::Color mMatColor = pMaterial->Sample(InRay, Position, Normal);
		OutColor = OutColor*mMatColor+mMatColor;
	}
	else
		OutColor = OutColor*0.5;
}

IntersectResult IntersectResult::NoHit;

IntersectResult::IntersectResult()
	:Geometry(nullptr)
	, Position(RayTracing::Vector3::Zero)
	, Normal(RayTracing::Vector3::Zero)
	, Distance(-1)
{

}

IntersectResult::~IntersectResult()
{
	Geometry = nullptr;
}
