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
	/**Compute edges of triangle and normal */
	
    RayTracing::Vector3 mEdge0 = InV1.mPosition - InV0.mPosition;
	RayTracing::Vector3 mEdge1 = InV2.mPosition - InV0.mPosition;
	RayTracing::Vector3 mNormal = mEdge0.cross(mEdge1);
	/**
	* if parrel to plane of triangle
	* greater zero means intersect with triangle 
	*/
	if (InRay.GetDirection().dot(mNormal) == 0)
		return false;
	/**
	* the experience :  P = (1-u-v)A-uB-vC;
	* if P is inside of Triangle, 0<=u<=1 0<=v<=1 and u+v<=1
	*/
	
	return false;
}

