#pragma once
#include "../Math/Ray.h"
#include "../Material/Material.h"

struct IntersectResult;

class Object 
{
public:
	Object();
	virtual ~Object();
public:
	virtual IntersectResult Intersect(RayTracing::Ray&);
	void DrawMaterial(RayTracing::Ray& InRay, RayTracing::Vector3& Position, RayTracing::Vector3& Normal,RayTracing::Color&);
protected:
	Material* pMaterial;
};

struct IntersectResult
{
	IntersectResult();
	~IntersectResult();
	Object* Geometry;
	RayTracing::Vector3 Position;
	RayTracing::Vector3 Normal;
	RayTracing::Vector3 LightDir;

	double	Distance;

	static IntersectResult NoHit;
};