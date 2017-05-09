#include "Mesh.h"
#include "BoundBox.h"

std::atomic<uint32_t> numIntersect(0);
std::atomic<uint32_t> numRayTriangleTests(0);

StaticMesh::StaticMesh() 
	:mBoundBox(nullptr)
{

}

StaticMesh::StaticMesh(std::vector<SVertex>& inVer, std::vector<int[3]>& inVerInd)
	:mBoundBox(nullptr)
{
	
}

StaticMesh::~StaticMesh()
{
	for (unsigned int Index=0;Index<mVerIndexLists.size();Index++) 
	{
		delete[] mVerIndexLists[Index];
		mVerIndexLists[Index] = nullptr;
	}

	if (mBoundBox) delete mBoundBox;
}

void StaticMesh::AddBoundBox(BoundBox* pBBox)
{
	mBoundBox = pBBox;
}

IntersectResult StaticMesh::Intersect(RayTracing::Ray& InRay)
{
	/**traversal the list of vertexs */
	//double mDistance = 1e10;
	IntersectResult HitRes = IntersectResult::NoHit;

	/**before test intersect with object,test bbox*/
	if (mBoundBox) 
	{
		if (!mBoundBox->Intersect(InRay, HitRes.Distance))
			return HitRes;
	}

	//IntersectResult TempHit = IntersectResult::NoHit;
	for (auto It = mVerIndexLists.cbegin(); It != mVerIndexLists.cend(); ++It)
	{
		numRayTriangleTests.fetch_add(1);
		if (IntersectTriangle(mVertexLists[(*It)[0]], mVertexLists[(*It)[1]], mVertexLists[(*It)[2]], InRay, HitRes))
		{
			numIntersect.fetch_add(1);
			/*if (mDistance > TempHit.Distance) 
			{
				mDistance = TempHit.Distance;
				HitRes = TempHit;
			}*/
			break;
		}
	}
	return HitRes;
}

void StaticMesh::AddVertex(SVertex& pVertex)
{
	
}

/**法线使用平面的法线作为基准*/
bool StaticMesh::IntersectTriangle(const SVertex& InV0, const SVertex& InV1, const SVertex& InV2, const RayTracing::Ray& InRay,IntersectResult& oHitPoint)
{
	/**Compute edges of triangle and normal */
	oHitPoint=IntersectResult::NoHit;

	RayTracing::Vector3 mEdge0 = InV1.mPosition - InV0.mPosition;
	RayTracing::Vector3 mEdge1 = InV2.mPosition - InV0.mPosition;
	//RayTracing::Vector3 mNormal = mEdge0.cross(mEdge1);
	/**
	* if parrel to plane of triangle
	* greater zero means intersect with triangle
	*/

	RayTracing::Vector3 mDxE2 = InRay.GetDirection().cross(mEdge1);

	double mDet = mEdge0.dot(mDxE2);
	/**if det is negative,intersect with the backface*/
	if (mDet < 1e-8)
		return false;

	/**
	* the experience :  P = (1-u-v)A-uB-vC;
	* if P is inside of Triangle, 0<=u<=1 0<=v<=1 and u+v<=1
	*/

	double mInvDet = 1.0 / mDet;
	RayTracing::Vector3 mOsubA = InRay.GetOrigin() - InV0.mPosition;

	double mU = mOsubA.dot(mDxE2)*mInvDet;
	if (mU < 0.0 || mU>1.0) return false;

	RayTracing::Vector3 mTxE1 = mOsubA.cross(mEdge0);
	double mV = InRay.GetDirection().dot(mTxE1)*mInvDet;

	if (mV < 0.0 || (mV + mU)>1.0) return false;

	double mT = mTxE1.dot(mEdge1)*mInvDet;

	/** Compute the Barycentric Coordinates */

	/** Compute point's positon,normal and color*/
	oHitPoint.Geometry = this;
	oHitPoint.Position = InRay.GetPoint(mT);
	//mHitPoint.Normal = InV0.mNormal*(1 - mU - mV) + InV1.mNormal*mU + InV2.mNormal*mV;
	oHitPoint.Normal = (mEdge0.cross(mEdge1)).normalize();
	oHitPoint.Distance = mT;
	//we should get the color of point by material
	//RayTracing::Color OutColor=InV0.mPointColor*(1 - mU - mV) + InV1.mPointColor*mU + InV2.mPointColor*mV;
	return true;
}



