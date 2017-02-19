#include "Camera.h"
#include <cmath>

Camera::Camera(const RayTracing::Vector3& pos, const RayTracing::Vector3& frodir, const RayTracing::Vector3& updir, double fov)
	:Position(pos)
	, Front(frodir)
	, Up(updir)
	, FovAng(fov)
{
	/**ע������x�˵�˳�����ǻ��з���Ӱ��Ķ�������*/
	RightAxi = Front.cross(Up);
	UpAxi = RightAxi.cross(Front);
	/**�����Ǽ�����һ���ӽ��ڣ��ܹ�ӳ��ķ�Χ��������������[-1,1]֮��*/
	FovScale = tan(fov*0.5*RayTracing::PI / 180.0) * 2;

}

Camera::~Camera()
{

}

RayTracing::Ray Camera::GenerateRay(double sx, double sy)
{
	/**���������д���ʿڿռ�ü��ƺ���ʽ�������е㲻һ��������������������ɹ���*/
	RayTracing::Vector3 dxr = RightAxi*((sx-0.5)*FovScale);
	RayTracing::Vector3 dxu = UpAxi*((sy - 0.5)*FovScale);


	return RayTracing::Ray(Position,(Front+dxr+dxu).normalize());
}

