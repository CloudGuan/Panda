#include "SpotLight.h"

SpotLight::SpotLight(RayTracing::Vector3& InPos,RayTracing::Color& InIrr,RayTracing::Vector3& InDir, int T, int O)
	:RTLight(InPos,InIrr,true)
	,Direction(InDir.normalize())
{
	HalfTheta = SDL_cos((T*M_PI)/360.0);
	HalfO = SDL_cos((O*M_PI)/360.0);

	SubTO = 1/(HalfTheta - HalfO);
}

SpotLight::~SpotLight()
{

}

RayTracing::Color SpotLight::Intersect(Object* Scene, IntersectResult& HitPos)
{
	/**ע����Ϊ��������ʱ�����䵽��������Ĺ����Ǵӵ�ָ������ģ�����Ҫ��һ��*/
	HitPos.LightDir = Position - HitPos.Position;

	double rr = HitPos.LightDir.SquareLength();
	double r = SDL_sqrt(rr);

	HitPos.LightDir = HitPos.LightDir / r;

	double spot(0.0);
	double LdotD = -(HitPos.LightDir.dot(Direction));

	if (LdotD >= HalfTheta)
		spot = 1.0;
	else if (LdotD <= HalfO)
		spot = 0.0;
	else 
		spot = SDL_pow((LdotD - HalfO)*SubTO,0.5);

	if (bShadow) 
	{
		RayTracing::Ray TestRay(HitPos.Position, HitPos.LightDir);
		IntersectResult TestRes = Scene->Intersect(TestRay);
		if (TestRes.Geometry&&TestRes.Distance <= r)
			return RayTracing::Color::Black;
	}

	return Irradiance*spot*(2000.0/rr);
}

