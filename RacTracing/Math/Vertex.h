#pragma once 

#include "Color.h"

struct SVertex 
{
	SVertex()=delete;
	SVertex(float[3],float[3],RayTracing::Color&);
	~SVertex();
	float mPosition[3];
	float mNormal[3];
	RayTracing::Color mPointColor;
};