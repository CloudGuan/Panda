#include "Mesh.h"


StaticMesh::StaticMesh(std::vector<SVertex>& inVer, std::vector<int>& inVerInd)
{

}

StaticMesh::~StaticMesh()
{

}

IntersectResult StaticMesh::Intersect(RayTracing::Ray&)
{
	return IntersectResult::NoHit;
}

bool StaticMesh::IntersectTriangle(const SVertex&, const SVertex&, const SVertex&, const RayTracing::Ray&)
{
	return false;
}

