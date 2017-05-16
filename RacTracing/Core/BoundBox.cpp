#include "BoundBox.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

/**��ʱ����6 ���� ֮����չ��12����*/

const double kEpsilon = 1e-8;
const double kInfinity = std::numeric_limits<double>::max();

BoundBox::BoundBox()
{
	/**�����ȼ�������*/
	/**in bound 0 means near 1 means far*/
	for (unsigned int index = 0; index < 3; index++)
	{
		mBoundValue.push_back(new double[2]{kInfinity,-kInfinity});
	}
}

BoundBox::~BoundBox()
{
	/**delete all memory block */
	int mArraySize = 3;
	for (unsigned int index=0;index<mArraySize;index++)
	{
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
	/**��С��*/
	if (mBoundValue[0][0] > pInPoint.mx) mBoundValue[0][0] = pInPoint.mx;
	if (mBoundValue[1][0] > pInPoint.my) mBoundValue[1][0] = pInPoint.my;
	if (mBoundValue[2][0] > pInPoint.mz) mBoundValue[2][0] = pInPoint.mz;
	/**�����*/
	if (mBoundValue[0][1] < pInPoint.mx) mBoundValue[0][1] = pInPoint.mx;
	if (mBoundValue[1][1] < pInPoint.my) mBoundValue[1][1] = pInPoint.my;
	if (mBoundValue[2][1] < pInPoint.mz) mBoundValue[2][1] = pInPoint.mz;
}

RayTracing::Vector3 BoundBox::GetCenter()const
{
	return RayTracing::Vector3(
		(mBoundValue[0][0] + mBoundValue[0][1]) / 2,
		(mBoundValue[1][0] + mBoundValue[1][1]) / 2,
		(mBoundValue[2][0] + mBoundValue[2][1]) / 2
	);
}

double*& BoundBox::operator[](int index)
{
	return mBoundValue[index];
}

double* BoundBox::operator[](int index) const
{
	return mBoundValue[index];
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