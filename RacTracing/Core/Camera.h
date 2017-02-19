#pragma once

/**�Բ����·�����⣬��Ӧ����ν������*/
#include "../Math/Vector.h"
#include "../Math/Ray.h"


class Camera 
{
public:
	Camera(const RayTracing::Vector3&,const RayTracing::Vector3&, const RayTracing::Vector3&,double);
	~Camera();
	/**
	*	��������Ļ�ϵ�һ�����ص㣬�����������귴�Ƴ�������ά�ռ�����ߵ��˷��̡�
	*/

	RayTracing::Ray GenerateRay(double sx,double sy);
private:
	/**����������ֱ�Ϊ�����λ�ã������Լ������������������Ҫ�������������м��㣬�������ͶӰƽ��*/
	RayTracing::Vector3 Position;
	RayTracing::Vector3 Front;
	RayTracing::Vector3 Up;
	double				FovAng;
	double				FovScale;

	/**����ͶӰƽ��*/
	RayTracing::Vector3 RightAxi;
	RayTracing::Vector3 UpAxi;
};