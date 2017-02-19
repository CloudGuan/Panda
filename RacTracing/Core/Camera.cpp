#include "Camera.h"
#include <cmath>

Camera::Camera(const RayTracing::Vector3& pos, const RayTracing::Vector3& frodir, const RayTracing::Vector3& updir, double fov)
	:Position(pos)
	, Front(frodir)
	, Up(updir)
	, FovAng(fov)
{
	/**注意这里x乘的顺序，这是会有方向影响的对于向量*/
	RightAxi = Front.cross(Up);
	UpAxi = RightAxi.cross(Front);
	/**这里是计算在一个视角内，能够映射的范围我们期望的是在[-1,1]之间*/
	FovScale = tan(fov*0.5*RayTracing::PI / 180.0) * 2;

}

Camera::~Camera()
{

}

RayTracing::Ray Camera::GenerateRay(double sx, double sy)
{
	/**这里和书上写的适口空间裁剪似乎公式上推正有点不一样，这里是用摄像机生成光线*/
	RayTracing::Vector3 dxr = RightAxi*((sx-0.5)*FovScale);
	RayTracing::Vector3 dxu = UpAxi*((sy - 0.5)*FovScale);


	return RayTracing::Ray(Position,(Front+dxr+dxu).normalize());
}

