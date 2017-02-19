#pragma once

#include "Object.h"

#include "../Math/Ray.h"
#include "../Math/Vector.h"

class Sphere:public Object
{
public:
	Sphere();
	Sphere(const RayTracing::Vector3&, double);
	~Sphere();
	/**用于计算某一条光线和物体有没有相交*/
	virtual IntersectResult Intersect(RayTracing::Ray&) override;
private:
	RayTracing::Vector3 Center;
	double				Radius;
};

