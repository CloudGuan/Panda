#pragma once 

/**
*	BVH 场景加速结构，将游戏场景分割为八叉树，进行优化计算，避免不必要的计算和相交测试，总的来说，是使用的二分的思想来，确定场景和那个结构体相交
*/

#include <vector>

/**
*	前置声明
*/
class StaticMesh;
class BoundBox;

namespace RayTracing
{
	class Vector3;
	class Ray;
}

extern const int kNumPlaneSetNormals;

/** Box of everty mesh*/
class  Extends
{
public:
	Extends();
	~Extends();
	void ExtendBy(const Extends&);
	RayTracing::Vector3 GetCenter() const;
	bool Intersect(const RayTracing::Ray&,double&,double&);
public:
	std::vector<double*> mBoundary;
	StaticMesh* mMesh;
};

struct OctreeNode 
{
	OctreeNode();
	~OctreeNode();
	bool bLeaf;
	OctreeNode* mChildNodes[8] = { nullptr }; //这里是指由八个空间，空间中有哪些物体 是另外 存储
	std::vector<const Extends*> mItemList; //如果是叶子节点，这个表示其空间下，物体的指针，根节点是空的
	Extends* nodeExtend; // 自己的包围盒，
};

class Octree 
{
public:
	Octree(const Extends&);
	~Octree();
	//用于插入节点
	void InsertNode();
	//用于划分空间
	void BuildTree();
private:
	void BuildTree(OctreeNode*&,const BoundBox&);
	void InsertNode(OctreeNode*&,const Extends*,const BoundBox*,int);
private:
	OctreeNode* mRootNode;
	BoundBox* mBBox;
};