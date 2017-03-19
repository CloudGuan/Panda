#pragma once 

#include "Object.h"
#include "../Math/Vertex.h"


#include <vector>

class StaticMesh :public Object
{
public:
	StaticMesh() = delete;
	StaticMesh(std::vector<SVertex>&,std::vector<int[3]>&);
	~StaticMesh();

	virtual IntersectResult Intersect(RayTracing::Ray&)override;

	bool IntersectTriangle(const SVertex&,const SVertex&,const SVertex&,const RayTracing::Ray&);
public:
	std::vector<SVertex>	mVertexLists;
	std::vector<int[3]>		mVerIndexLists;
};