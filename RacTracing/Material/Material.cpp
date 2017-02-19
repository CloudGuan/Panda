#include "Material.h"

//RayTracing::Vector3 Material::LightPost(RayTracing::Vector3(1,1,1).normalize());
//RayTracing::Color	Material::LightColor(1.0,1.0,1.0,1.0);

Material::Material()
	:pTexture(nullptr)
	,Reflectiveness(0.5)
{

}

Material::Material(float inReflectiveness)
	:pTexture(nullptr)
	,Reflectiveness(inReflectiveness)
{

}

Material::~Material()
{

}

RayTracing::Color Material::Sample(RayTracing::Ray& InRay, RayTracing::Vector3& Position, RayTracing::Vector3& Normal)
{
	return RayTracing::Color::White;
}
