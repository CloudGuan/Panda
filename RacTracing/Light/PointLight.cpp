
#include "PointLight.h"

PointLight::PointLight(RayTracing::Vector3& Pos, RayTracing::Color& InIrr, bool On)
	:RTLight(Pos,InIrr,On)
{

}

PointLight::~PointLight()
{

}

RayTracing::Color PointLight::Intersect(Object* Scene, IntersectResult& HitPos)
{
	/**work out the light dir*/
	HitPos.LightDir = Position - HitPos.Position;

	double rr = HitPos.LightDir.SquareLength();
	double r = SDL_sqrt(rr);

	HitPos.LightDir = HitPos.LightDir / r;
	if(bShadow)
	{
		RayTracing::Ray TestRay(HitPos.Position,HitPos.LightDir);
		IntersectResult TestRes=Scene->Intersect(TestRay);
		if (TestRes.Geometry&&TestRes.Distance <= r)
			return RayTracing::Color::Black;
	}

	return Irradiance*(1500.0/ rr);
}

