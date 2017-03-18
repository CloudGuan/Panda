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

bool StaticMesh::IntersectTriangle(const SVertex& InV0, const SVertex& InV1, const SVertex& InV2, const RayTracing::Ray& InRay)
{
	/**Compute edges of triangle*/

	RayTracing::Vector3 mEdge0 = InV0.mPosition - InV1.mPosition;
	RayTracing::Vector3 mEdge1 = InV1.mPosition - InV2.mPosition;
	/**if parrel to plane of triangle*/

	/**if out side of triangle */
	return false;
}

