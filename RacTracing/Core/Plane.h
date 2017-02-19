#pragma once

#include "Object.h"


class Plane :public Object 
{
public:
	Plane();
	Plane(RayTracing::Vector3&, double);
	~Plane();
public:
	virtual IntersectResult Intersect(RayTracing::Ray&)override;
private:
	RayTracing::Vector3 Normal;
	RayTracing::Vector3 Point;
	double				Distance;
#ifdef _DEBUG
	char				Name[20];
	static int			index;
#endif

};