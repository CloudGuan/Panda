#pragma once

/**��Χ�м��㣬֮������嶼���ȼ����Χ�е���������ӿ���߸��ټ���ļ�����*/
/** Using box with six face !!*/

#include <vector>

namespace RayTracing 
{
	class Ray;
	class Vector3;
}

class BoundBox 
{
public:
	BoundBox();
	~BoundBox();
	bool Intersect(RayTracing::Ray& pInRay,double&);
	void ComputeBound(RayTracing::Vector3&);
	RayTracing::Vector3 GetCenter()const;
	double*& operator[](int);
	double* operator[](int)const;
private:
	//std::vector<RayTracing::Vector3*> mBoundNormalPlanes;
	/**
	*	ray intersect with normal and we will get t near and t far
	*	bound[0][0] 
	*/
	std::vector<double*> mBoundValue;
};
