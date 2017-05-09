#pragma once 

/** 
*	Add BoundBox to all object
*/

#include "Object.h"
#include "../Math/Vertex.h"

#include <vector>
#include <atomic>

class BoundBox;
extern std::atomic<uint32_t> numIntersect;
extern std::atomic<uint32_t> numRayTriangleTests;

class StaticMesh :public Object
{
public:
	StaticMesh();
	StaticMesh(std::vector<SVertex>&,std::vector<int[3]>&);
	virtual ~StaticMesh();

	virtual IntersectResult Intersect(RayTracing::Ray&)override;

	void AddVertex(SVertex&);
	bool IntersectTriangle(const SVertex&,const SVertex&,const SVertex&,const RayTracing::Ray&,IntersectResult&);
	void AddBoundBox(BoundBox*);
public:
	std::vector<SVertex>	mVertexLists;
	std::vector<int*>		mVerIndexLists;
	BoundBox*	mBoundBox;
};