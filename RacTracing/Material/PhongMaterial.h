#pragma once

#include "../Material/Material.h"


/**
*	Phong 光照模型（一个基于经验的模型最开始，后来有改进）
*	finalColor=ambient+diffuse+specular
*	Kd 表示材质的漫反射系数，Ks 环境光的反射系数系数
*	ambient 大多数时候是个可以预先计算好的常数
*	diffuse=kd*(Lm*N)*light_diffuse*material_diffuse
*	specular=ks*（Rm*Eye）^a*material_spec*light_spec
*/

class PhongMaterial :public Material 
{
public:
	PhongMaterial()=default;
	PhongMaterial(float);
	~PhongMaterial();
public:
	virtual RayTracing::Color Sample(RayTracing::Ray& InRay, RayTracing::Vector3& Position, RayTracing::Vector3& Normal) override;

private:
	RayTracing::Color	Diffuse;
	RayTracing::Color	Specular;
	float				Shininess;
};