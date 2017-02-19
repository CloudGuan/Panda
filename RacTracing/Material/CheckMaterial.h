#pragma once

#include "Material.h"

class CheckMaterial :public Material 
{
public:
	CheckMaterial() = default;
	CheckMaterial(float, float);
	~CheckMaterial();
public:
	virtual RayTracing::Color Sample(RayTracing::Ray& InRay, RayTracing::Vector3& Position, RayTracing::Vector3& Normal)override;
private:
	float XScale;
	float ZScale;
};