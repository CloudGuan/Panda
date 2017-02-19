#include "Plane.h"
#include "../Material/CheckMaterial.h"
#include <stdio.h>

Plane::Plane()
{

}

int Plane::index = 1;
Plane::Plane(RayTracing::Vector3& InNormal, double d)
	:Normal(InNormal)
	,Distance(d)
{
	Point = Normal*Distance;
	sprintf_s(Name, "Plane_%d", index++);
	//pMaterial = new CheckMaterial(0.1f,0.1f);
}

Plane::~Plane()
{

}

IntersectResult Plane::Intersect(RayTracing::Ray& InRay)
{
	double DdotN = InRay.GetDirection().dot(Normal);
	if (DdotN >= 0)
		return IntersectResult::NoHit;

	double OdotN = Normal.dot(Point-InRay.GetOrigin());
	IntersectResult ResHit;
	ResHit.Geometry = this;
	ResHit.Normal = Normal;
	ResHit.Distance = OdotN / DdotN;
	ResHit.Position = InRay.GetPoint(ResHit.Distance);
	/*if (pMaterial)
		Out = pMaterial->Sample(InRay, ResHit.Position, ResHit.Normal);*/

	return ResHit;
}

