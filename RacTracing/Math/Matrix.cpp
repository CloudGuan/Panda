#include "Matrix.h"
#include "Vector.h"

namespace RayTracing 
{
	Matrix3X3::Matrix3X3(const Vector3& L1, const Vector3& L2, const Vector3& L3)
	{
		mValue[0][0] = L1.mx;
		mValue[1][0] = L1.my;
		mValue[2][0] = L1.mz;

		mValue[0][1] = L2.mx;
		mValue[1][1] = L2.my;
		mValue[2][1] = L2.mz;

		mValue[0][2] = L3.mx;
		mValue[1][2] = L3.my;
		mValue[2][2] = L3.mz;
	}

	Matrix3X3::~Matrix3X3()
	{

	}

	double Matrix3X3::GetDet()
	{
		double mTempNum1 = (mValue[0][0] * mValue[1][1] * mValue[2][2] + mValue[0][1] * mValue[1][2] * mValue[2][0] + mValue[0][2] * mValue[1][0] * mValue[2][1]);
		double mTempNum2 = (mValue[0][2] * mValue[1][1] * mValue[2][0] + mValue[0][1] * mValue[1][0] * mValue[2][2] + mValue[0][0] * mValue[1][2] * mValue[2][1]);

		return mTempNum1 - mTempNum2;
	}

}