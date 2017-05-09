#include "BoundBox.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

/**��ʱ����6 ���� ֮����չ��12����*/

const double kEpsilon = 1e-8;
const double kInfinity = std::numeric_limits<double>::max();

BoundBox::BoundBox()
{
	/**�����ȼ�������*/
	mBoundNormalPlanes.push_back(new RayTracing::Vector3(1.0, 0.0, 0.0));
	mBoundNormalPlanes.push_back(new RayTracing::Vector3(0.0, 1.0, 0.0));
	mBoundNormalPlanes.push_back(new RayTracing::Vector3(0.0, 0.0, 1.0));

	/**in bound 0 means near 1 means far*/
	for (unsigned int index = 0; index < mBoundNormalPlanes.size(); index++)
	{
		mBoundValue.push_back(new double[2]{kInfinity,-kInfinity});
	}
}

BoundBox::~BoundBox()
{
	/**delete all memory block */
	int mArraySize = mBoundNormalPlanes.size();
	for (unsigned int index=0;index<mArraySize;index++)
	{
		delete mBoundNormalPlanes[index];
		mBoundNormalPlanes[index] = nullptr;
		delete[] mBoundValue[index];
		mBoundValue[index] = nullptr;
	}
}

/**
*	inpute the ponint in world coordinary
*	we will get six different value 
*/
void BoundBox::ComputeBound(RayTracing::Vector3& pInPoint)
{
	for (int index=0; index<mBoundNormalPlanes.size();index++) 
	{
		double mDis = mBoundNormalPlanes[index]->mx*pInPoint.mx + mBoundNormalPlanes[index]->my*pInPoint.my + mBoundNormalPlanes[index]->mz*pInPoint.mz;
		if (mBoundValue[index][0] > mDis) mBoundValue[index][0] = mDis;
		if (mBoundValue[index][1] < mDis) mBoundValue[index][1] = mDis;
	}
}

/**
*	Tips: �������е� ���岻ֹ��һ����ʱ�� ���ǰ�Χ������õĶ���ͬ���İ�Χ�У������������Ӧ�÷��ڼ��س����ĵط������Ұ���Ҫ����Ķ�������ʵ�ּ����
*	���ڵڶ����汾���¡�
*/

bool BoundBox::Intersect(RayTracing::Ray& pInRay, double& oDis)
{
	/** 
	*	oDis Means the direction of camera !!!
	*	��ʱ�����д��
	*/
	RayTracing::Vector3 mOr = pInRay.GetOrigin();
	RayTracing::Vector3 mDir = pInRay.GetDirection();
	

	float tmin = (mBoundValue[0][0] - mOr.mx) / mDir.mx;
	float tmax = (mBoundValue[0][1] - mOr.mx) / mDir.mx;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (mBoundValue[1][0] - mOr.my) / mDir.my;
	float tymax = (mBoundValue[1][1] - mOr.my) / mDir.my;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (mBoundValue[2][0] - mOr.mz) / mDir.mz;
	float tzmax = (mBoundValue[2][1] - mOr.mz) / mDir.mz;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return true;
}