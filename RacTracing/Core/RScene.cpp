#include "RScene.h"
#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

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

void Rscene::LoadMesh()
{
	/**
	*	using for test
	*	we should load object from scene
	*	also can do some trans
	*/

	string mFileType;
	std::ifstream mFileStream;
	/**construct bound while load model*/
	StaticMesh* mMeshObject = new StaticMesh();
	int mIngrone;
	RayTracing::Vector3 mOffset(0.0,5.0,-5.0);
	//double minX, maxX, minY, maxY, minZ, maxZ;
	// test_simp1
	mFileStream.open("../Models/test_simp1.m", ifstream::in); //之后改为从文件加载
	if (mFileStream.fail())
	{
		cout << "OpenFile error!!!" << endl;
		return;
	}
	mFileStream >> mFileType;
	while (!mFileStream.eof())
	{
		/**Loop to Load triangles */
		/**Vertex 1  -0.5 0.0021 0.5*/
		/**Face 1  1 4 8*/		
		if (mFileType.compare("Vertex")==0)
		{
			mFileStream >> mIngrone;
			SVertex mVertex;
			mFileStream >> mVertex.mPosition.mx >> mVertex.mPosition.my >> mVertex.mPosition.mz;

			mVertex.mPosition = mVertex.mPosition*5.0 + mOffset;
			mMeshObject->mVertexLists.push_back(mVertex);
			//mVertexLists.push_back(mVertex);
		}
		else if (mFileType.compare("Face")==0) 
		{
			/**face means triangles*/
			int* mIndex = new int[3];
			mFileStream >> mIngrone;
			mFileStream >> mIndex[0] >> mIndex[1] >> mIndex[2];
			mIndex[0]--; mIndex[1]--;mIndex[2]--;
			/**add index list to mesh*/
			mMeshObject->mVerIndexLists.push_back(mIndex);
		}
		else
		{
			cerr << "解析文件错误！！！" << endl;
			delete mMeshObject;
			return;
		}
		mFileStream >> mFileType;
	}
	GameScene.push_back(mMeshObject);
	mFileStream.close();
}

IntersectResult Rscene::DrawCall(RayTracing::Ray& InRay, RayTracing::Color& OutColor)
{
	/**追踪从屏幕射出的一条射线，计算和场景的焦点*/
	IntersectResult HitRes = Intersect(InRay);
	/**若命中则根据材质计算颜色*/
	if(HitRes.Geometry)
	{
		/**引入光源系统，计算遮挡,暂时先只有一个光源*/
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
	/*clock_t mStart,mEnd;
	mStart = clock();*/
	for (auto Iterator=GameScene.begin();Iterator!=GameScene.end();Iterator++)
	{
		/**调试用，用来查看程序耗时在哪里*/
		
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
	/*mEnd = clock();
	printf_s("Once Draw Call: %f",(float)(mEnd-mStart)/CLOCKS_PER_SEC);*/
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

