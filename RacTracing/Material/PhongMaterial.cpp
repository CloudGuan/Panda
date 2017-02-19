#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(float InRe)
	:Diffuse(1.0,0,0,1)
	,Specular(1.0,1.0,1.0,1.0)
	,Shininess(InRe)
{
}

PhongMaterial::~PhongMaterial()
{

}
/**InRay:视线方向 Position：光线入射方向 Normal:法线方向*/
RayTracing::Color PhongMaterial::Sample(RayTracing::Ray& InRay,RayTracing::Vector3& Position,RayTracing::Vector3& Normal)
{
	/**因为是平行关所以暂时简化了计算*/

	double NdotL = Normal.dot(Position);
	RayTracing::Vector3 H = (Position -InRay.GetDirection()).normalize();
	double NdotH = Normal.dot(H);

	RayTracing::Color outD = Diffuse*SDL_max(NdotL, 0.0);
	RayTracing::Color outSp = Specular*SDL_pow(SDL_max(NdotH, 0), Shininess);

	return (outD+outSp);
}

