#pragma once

#include "Object.h"
#include "../Light/RTLight.h"
#include <vector>

/**
*	2.0 using bvh tree acculate
*/
class Rscene :public Object 
{
public:
	Rscene();
	~Rscene();
	void LoadScene();
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