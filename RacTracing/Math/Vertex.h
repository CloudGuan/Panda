#pragma once 

#include "Color.h"

struct SVertex 
{
	SVertex();
	~SVertex();
	float mPosition[3];
	float mNormal[3];
	RayTracing::Color mPointColor;
};