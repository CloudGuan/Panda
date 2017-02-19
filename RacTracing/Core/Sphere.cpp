#include "Sphere.h"
#include "../Material/PhongMaterial.h"

Sphere::Sphere()
{

}

Sphere::Sphere(const RayTracing::Vector3& cen, double r)
	:Center(cen)
	,Radius(r)
{
	pMaterial = new PhongMaterial(20);
}

Sphere::~Sphere()
{

}
/**
*	define v=o-c (o means ray's origin,c means center)
*	(v-td)^2=r^2;
*=>	t^2+2d.v*t+v^2-r^2=0;
*/
IntersectResult Sphere::Intersect(RayTracing::Ray& pRay)
{
	RayTracing::Vector3 Vv = pRay.GetOrigin() - Center;
	double subVR = Vv.SquareLength() - Radius*Radius;
	double dotVD = pRay.GetDirection().dot(Vv);

	/**方程有解，则能够说明相交，这个时候我们需要推算然后剔除背面的那个点*/
	if (dotVD <= 0) 
	{
		double qurDetla = dotVD*dotVD - subVR;
		if (qurDetla >= 0) 
		{
			IntersectResult Res;
			Res.Geometry = this;
			Res.Distance = -dotVD - sqrtl(qurDetla);
			Res.Position = pRay.GetPoint(Res.Distance);
			Res.Normal = (Res.Position - Center).normalize();

			/*if (pMaterial)
				Out = pMaterial->Sample(pRay, Res.Position, Res.Normal);*/
			return Res;
		}
	}
	return IntersectResult::NoHit;
}

