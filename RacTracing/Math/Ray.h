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
		Vector3 GetOrigin() const { return Origin; }
		Vector3 GetDirection()const { return Direction; } 
		Vector3 GetPoint(double) const;
	private:
		Vector3 Origin;
		Vector3 Direction;
	};


}