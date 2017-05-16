#include "Octree.h"

#include "../Math/Vector.h"
#include "../Math/Ray.h"
#include "BoundBox.h"


const int kNumPlaneSetNormals=7;

Extends::Extends()
{
	for (int index = 0; index < kNumPlaneSetNormals; ++index) 
	{
		mBoundary.push_back(new double[2]{ 1e8,1e-8 });
	}
}

Extends::~Extends()
{
	for (unsigned int index=0;index<mBoundary.size();++index) 
	{
		delete[] mBoundary[index];
	}
}

/*
*	Compute BoundBox by child Bound
*/

void Extends::ExtendBy(const Extends& pEx)
{
	for (int index = 0; index < kNumPlaneSetNormals; ++index)
	{
		if (pEx.mBoundary[index][0] < mBoundary[index][0]) mBoundary[index][0] = pEx.mBoundary[index][0];
		if (pEx.mBoundary[index][1] > mBoundary[index][1]) mBoundary[index][1] = pEx.mBoundary[index][1];
	}
}

RayTracing::Vector3 Extends::GetCenter() const
{
	return RayTracing::Vector3(
		(mBoundary[0][0] + mBoundary[0][1])*0.5,
		(mBoundary[1][0] + mBoundary[1][1])*0.5,
		(mBoundary[2][0] + mBoundary[2][1])*0.5
	);
}

bool Extends::Intersect(const RayTracing::Ray&, double&, double&)
{
	return true;
}

/**
*	do some init code for Octree Node
*/

OctreeNode::OctreeNode()
	:bLeaf(true)
	,nodeExtend(nullptr)
{

}

OctreeNode::~OctreeNode()
{
	if (nodeExtend) 
	{
		delete nodeExtend;
	}
}


Octree::Octree(const Extends& pSceneExtents)
	:mRootNode(nullptr)
	,mBBox(nullptr)
{
	/**
	* compute root node size	
	*/
	mRootNode = new OctreeNode();
	mBBox = new BoundBox();

	(*mBBox)[0][0] = pSceneExtents.mBoundary[0][0];
	(*mBBox)[0][1] = pSceneExtents.mBoundary[0][1];
	(*mBBox)[1][0] = pSceneExtents.mBoundary[1][0];
	(*mBBox)[1][1] = pSceneExtents.mBoundary[1][1];
	(*mBBox)[2][0] = pSceneExtents.mBoundary[2][0];
	(*mBBox)[2][1] = pSceneExtents.mBoundary[2][1];
}

Octree::~Octree()
{
	if (mRootNode) delete mRootNode;
	if (mBBox) delete mBBox;
}

void Octree::BuildTree()
{
	BuildTree(mRootNode,*mBBox);
}

/**主要目的是划分好的空间计算好大小哈哈哈哈哈哈*/
void Octree::BuildTree(OctreeNode*& pNode, const BoundBox& pBox)
{
	if (pNode->bLeaf)
	{
		/**计算包围盒的大小和体积*/
		for (const auto& It : pNode->mItemList)
		{
			pNode->nodeExtend->ExtendBy(*It);
		}
	}
	else 
	{
		for (uint8_t index=0;index<8;++index) 
		{
			if (pNode->mChildNodes[index]) 
			{
				BoundBox mChildBox;
				RayTracing::Vector3 mCenter = pBox.GetCenter();

				/**根据序号判断象限*/
				mChildBox[0][0] = (index & 4) ? mCenter.mx : pBox[0][0];
				mChildBox[0][1] = (index & 4) ? pBox[0][1] : mCenter.mx;
				mChildBox[1][0] = (index & 2) ? mCenter.my : pBox[1][0];
				mChildBox[1][1] = (index & 2) ? pBox[1][1] : mCenter.my;
				mChildBox[2][0] = (index & 1) ? mCenter.mz : pBox[2][0];
				mChildBox[2][1] = (index & 1) ? pBox[2][1] : mCenter.mz;

				BuildTree(pNode->mChildNodes[index], mChildBox);

				pNode->nodeExtend->ExtendBy(*(pNode->mChildNodes[index]->nodeExtend));
			}
		}
	}
}

void Octree::InsertNode(const Extends* pExtends)
{
	InsertNode(mRootNode, pExtends, mBBox, 0);
}

/**
*	基于root 节点去插入构建八叉树！！！！ 这个操作是可以递归进进行的
*/
void Octree::InsertNode(OctreeNode*& pNode, const Extends* pExtends, const BoundBox* pBox,int pDepth)
{ 
	if (nullptr == pNode)
		return;
	
	if (pNode->bLeaf) 
	{
		if (pNode->mItemList.size() == 0 || pDepth == 8) 
		{
			pNode->mItemList.push_back(pExtends);
		}
		else 
		{
			while (pNode->mItemList.size())
			{
				InsertNode(pNode,pNode->mItemList.back(),pBox,pDepth);
				pNode->mItemList.pop_back();
			}
			InsertNode(pNode,pExtends,mBBox,pDepth);
		}
	}
	else 
	{ 
		RayTracing::Vector3 mInsertCenter = pExtends->GetCenter();
		RayTracing::Vector3 mNodeCenter = pBox->GetCenter();

		BoundBox* mChildBox = new BoundBox();
		int mChildIndex = 0;

		/**
		*	根据大小划分象限！！！！ 在三维空间中可以划分八个象限。判断物体在那个象限里面
		*/
		if (mInsertCenter.mx > mNodeCenter.mx) 
		{
			mChildIndex = 4;
			(*mChildBox)[0][0] = mNodeCenter.mx;
			(*mChildBox)[0][1] = (*pBox)[0][1];
		}
		else 
		{
			(*mChildBox)[0][0] = (*pBox)[0][0];
			(*mChildBox)[0][1] = mNodeCenter.mx;
		}
		//划分y象限的操作
		if (mInsertCenter.my > mNodeCenter.my) 
		{
			mChildIndex += 2;
			(*mChildBox)[1][0] = mNodeCenter.my;
			(*mChildBox)[1][1] = (*pBox)[1][1];
		}
		else 
		{
			(*mChildBox)[1][0] = (*pBox)[1][0];
			(*mChildBox)[1][1] = mNodeCenter.my;
		}

		//划分z象限操作
		if (mInsertCenter.mz > mNodeCenter.mz) 
		{
			mChildIndex += 1;
			(*mChildBox)[2][0] = mNodeCenter.mz;
			(*mChildBox)[2][1] = (*pBox)[2][1];
		}
		else 
		{
			(*mChildBox)[2][0] = (*pBox)[2][1];
			(*mChildBox)[2][1] = mNodeCenter.mz;
		}

		if (nullptr == pNode->mChildNodes[mChildIndex]) 
		{
			pNode->mChildNodes[mChildIndex] = new OctreeNode();
		}
		InsertNode(pNode->mChildNodes[mChildIndex], pExtends, mChildBox, pDepth + 1);
		//递归结束时候退出
		delete mChildBox;
	}
}


