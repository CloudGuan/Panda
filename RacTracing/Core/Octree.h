#pragma once 

/**
*	BVH �������ٽṹ������Ϸ�����ָ�Ϊ�˲����������Ż����㣬���ⲻ��Ҫ�ļ�����ཻ���ԣ��ܵ���˵����ʹ�õĶ��ֵ�˼������ȷ���������Ǹ��ṹ���ཻ
*/

#include <vector>

/**
*	ǰ������
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
	OctreeNode* mChildNodes[8] = { nullptr }; //������ָ�ɰ˸��ռ䣬�ռ�������Щ���� ������ �洢
	std::vector<const Extends*> mItemList; //�����Ҷ�ӽڵ㣬�����ʾ��ռ��£������ָ�룬���ڵ��ǿյ�
	Extends* nodeExtend; // �Լ��İ�Χ�У�
};

class Octree 
{
public:
	Octree(const Extends&);
	~Octree();
	//���ڲ���ڵ�
	void InsertNode();
	//���ڻ��ֿռ�
	void BuildTree();
private:
	void BuildTree(OctreeNode*&,const BoundBox&);
	void InsertNode(OctreeNode*&,const Extends*,const BoundBox*,int);
private:
	OctreeNode* mRootNode;
	BoundBox* mBBox;
};