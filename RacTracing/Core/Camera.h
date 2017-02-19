#pragma once

/**卧槽这个路径问题，我应该如何解决？？*/
#include "../Math/Vector.h"
#include "../Math/Ray.h"


class Camera 
{
public:
	Camera(const RayTracing::Vector3&,const RayTracing::Vector3&, const RayTracing::Vector3&,double);
	~Camera();
	/**
	*	根据在屏幕上的一个像素点，计算他的坐标反推出其在三维空间的射线的人方程。
	*/

	RayTracing::Ray GenerateRay(double sx,double sy);
private:
	/**这里的三个分别为摄像机位置，朝向，以及世界的正方向，我们需要根据这三个进行计算，计算出来投影平面*/
	RayTracing::Vector3 Position;
	RayTracing::Vector3 Front;
	RayTracing::Vector3 Up;
	double				FovAng;
	double				FovScale;

	/**构建投影平面*/
	RayTracing::Vector3 RightAxi;
	RayTracing::Vector3 UpAxi;
};