#pragma once

#include "../Material/Material.h"


/**
*	Phong ����ģ�ͣ�һ�����ھ����ģ���ʼ�������иĽ���
*	finalColor=ambient+diffuse+specular
*	Kd ��ʾ���ʵ�������ϵ����Ks ������ķ���ϵ��ϵ��
*	ambient �����ʱ���Ǹ�����Ԥ�ȼ���õĳ���
*	diffuse=kd*(Lm*N)*light_diffuse*material_diffuse
*	specular=ks*��Rm*Eye��^a*material_spec*light_spec
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