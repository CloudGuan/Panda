#include "DirectLight.h"

DirectLight::DirectLight()
{

}

DirectLight::DirectLight(RayTracing::Vector3& Postion, RayTracing::Vector3& InDir, RayTracing::Color& InIrr, bool On /*= false*/)
	:RTLight(Postion,InIrr,On)
	,Direction(InDir.normalize())
{

}

DirectLight::~DirectLight()
{

}

/**
*	��ͬ�ĵ㲻ͬ�ļ���
*/
RayTracing::Color DirectLight::Intersect(Object* Scene, IntersectResult& HitPos)
{
	RayTracing::Vector3 neDir = -Direction;
	if (bShadow) 
	{
		
		RayTracing::Ray InverRay(HitPos.Position, neDir);
		IntersectResult HitRes = Scene->Intersect(InverRay);
		if (HitRes.Geometry)
			return RayTracing::Color::Black;
	}
	/**�������������*/
	double NdotD = HitPos.Normal.dot(neDir);
	HitPos.LightDir = neDir;
	if (NdotD <= 0)
		NdotD = 0.0;
	return Irradiance*NdotD;
}

