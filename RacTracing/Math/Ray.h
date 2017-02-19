#pragma once

#include "Vector.h"

namespace RayTracing 
{

	class Ray 
	{
	public:
		Ray(const Vector3&,const Vector3&);
		Ray(const Ray&);
		~Ray();
	public:
		Vector3 GetOrigin() { return Origin; }
		Vector3 GetDirection() { return Direction; }
		Vector3 GetPoint(double);
	private:
		Vector3 Origin;
		Vector3 Direction;
	};


}