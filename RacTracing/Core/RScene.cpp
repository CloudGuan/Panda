#include "RScene.h"

Rscene::Rscene()
	:SceneLight(nullptr)
{

}

Rscene::~Rscene()
{
	for (unsigned int i=0;i<GameScene.size();i++)
	{
		if(GameScene[i])
			delete GameScene[i];
		GameScene[i] = nullptr;
	}
}

IntersectResult Rscene::DrawCall(RayTracing::Ray& InRay, RayTracing::Color& OutColor)
{
	/**׷�ٴ���Ļ�����һ�����ߣ�����ͳ����Ľ���*/
	IntersectResult HitRes = Intersect(InRay);
	/**����������ݲ��ʼ�����ɫ*/
	if(HitRes.Geometry)
	{
		/**�����Դϵͳ�������ڵ�,��ʱ��ֻ��һ����Դ*/
		if (SceneLight) 
		{
			OutColor = SceneLight->Intersect(this, HitRes);
			if (OutColor == RayTracing::Color::Black)
				return HitRes;
			else
			{
				HitRes.Geometry->DrawMaterial(InRay, HitRes.LightDir, HitRes.Normal, OutColor);
			}
			/**Using for debuging */
			//OutColor = RayTracing::Color::White;
			//HitRes.Geometry->DrawMaterial(InRay,RayTracing::Vector3(1.75,2.0,1.5).normalize(), HitRes.Normal, OutColor);
		}
	}
	return HitRes;
}

IntersectResult Rscene::Intersect(RayTracing::Ray& InRay)
{
	double Mindistance=1e30;
	RayTracing::Color TempColor;
	IntersectResult HitRes=IntersectResult::NoHit;
	for (auto Iterator=GameScene.begin();Iterator!=GameScene.end();Iterator++)
	{
		if (*Iterator) 
		{
			IntersectResult Res = (*Iterator)->Intersect(InRay);
			if (Res.Geometry&&(Res.Distance < Mindistance))
			{
				Mindistance = Res.Distance;
				//OutColor = TempColor;
				HitRes = Res;
			}
		}
		
	}
	return HitRes;
}

bool Rscene::AddObject(Object*InOb)
{
	if (!InOb)
		return false;
	GameScene.push_back(InOb);
	return true;
}

bool Rscene::AddLights(RTLight* InLight)
{
	if (!InLight)
		return false;
	SceneLight = InLight;
	return true;
}

