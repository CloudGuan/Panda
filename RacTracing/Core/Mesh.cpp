#include "Mesh.h"


StaticMesh::StaticMesh(std::vector<SVertex>& inVer, std::vector<int[3]>& inVerInd)
{

}

StaticMesh::~StaticMesh()
{

}

IntersectResult StaticMesh::Intersect(RayTracing::Ray& InRay)
{
	/**traversal the list of vertexs */
	double mDistance = 1e-10;
	for (auto It = mVerIndexLists.cbegin(); It != mVerIndexLists.cend(); ++It)
	{
		if (IntersectTriangle(mVertexLists[(*It)[0]], mVertexLists[(*It)[1]], mVertexLists[(*It)[2]], InRay)) 
		{
			
		}
	}

	return IntersectResult::NoHit;
}

bool StaticMesh::IntersectTriangle(const SVertex& InV0, const SVertex& InV1, const SVertex& InV2, const RayTracing::Ray& InRay)
{
	/**Compute edges of triangle and normal */

	RayTracing::Vector3 mEdge0 = InV1.mPosition - InV0.mPosition;
	RayTracing::Vector3 mEdge1 = InV2.mPosition - InV0.mPosition;
	//RayTracing::Vector3 mNormal = mEdge0.cross(mEdge1);
	/**
	* if parrel to plane of triangle
	* greater zero means intersect with triangle
	*/
	RayTracing::Vector3 mDxE2 = InRay.GetDirection().cross(mEdge1);
	double mDet = mDxE2.dot(mEdge1);
	/**if det is negative,intersect with the backface*/
	if (mDet < 0)
		return false;

	/**
	* the experience :  P = (1-u-v)A-uB-vC;
	* if P is inside of Triangle, 0<=u<=1 0<=v<=1 and u+v<=1
	*/

	double mInvDet = 1.0 / mDet;
	RayTracing::Vector3 mOsubA = InRay.GetOrigin() - InV0.mPosition;

	double mU = mOsubA.dot(mDxE2)*mInvDet;
	if (mU < 0 || mU>1) return false;

	RayTracing::Vector3 mTxE1 = mOsubA.cross(mEdge0);
	double mV = InRay.GetDirection().dot(mTxE1)*mInvDet;

	if (mV < 0 || (mV + mU)>1) return false;

	double mT = mTxE1.dot(mEdge1)*mInvDet;
	
	return true;
}

