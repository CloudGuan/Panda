#include "Ray.h"


RayTracing::Ray::Ray(const Vector3& org, const Vector3& dir)
	:Origin(org)
	,Direction(dir)
{

}

RayTracing::Ray::Ray(const Ray& rhs)
	:Origin(rhs.Origin)
	,Direction(rhs.Direction)
{

}

RayTracing::Ray::~Ray()
{

}

RayTracing::Vector3 RayTracing::Ray::GetPoint(double t)
{
	return (Origin + Direction*t);
}
