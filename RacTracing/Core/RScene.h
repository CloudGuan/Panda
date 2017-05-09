#pragma once

#include "Object.h"
#include "../Light/RTLight.h"
#include <vector>

class Rscene :public Object 
{
public:
	Rscene();
	~Rscene();
	void LoadMesh();
	IntersectResult DrawCall(RayTracing::Ray&,RayTracing::Color&);
	virtual IntersectResult Intersect(RayTracing::Ray&);
	bool	AddObject(Object*);
	bool	AddLights(RTLight*);
private:
	std::vector<Object*> GameScene;
	RTLight*			 SceneLight;
//	double				 Depth;
};