#pragma once 

#include "Color.h"
#include "Vector.h"


struct SVertex 
{
	SVertex();
	SVertex(RayTracing::Vector3&,RayTracing::Vector3&,RayTracing::Color&);
	~SVertex();

	RayTracing::Vector3 mPosition;
	RayTracing::Vector3 mNormal;
	RayTracing::Color mPointColor;
};