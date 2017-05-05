#pragma once 

/** 
*	Add BoundBox to all object
*/

#include "Object.h"
#include "../Math/Vertex.h"

#include <vector>

class StaticMesh :public Object
{
public:
	StaticMesh();
	StaticMesh(std::vector<SVertex>&,std::vector<int[3]>&);
	virtual ~StaticMesh();

	virtual IntersectResult Intersect(RayTracing::Ray&)override;

	void AddVertex(SVertex&);
	bool IntersectTriangle(const SVertex&,const SVertex&,const SVertex&,const RayTracing::Ray&,IntersectResult&);
public:
	std::vector<SVertex>	mVertexLists;
	std::vector<int*>		mVerIndexLists;
};