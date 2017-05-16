#pragma once

/**包围盒计算，之后的物体都优先计算包围盒的体积，来加快光线跟踪计算的计算量*/
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
