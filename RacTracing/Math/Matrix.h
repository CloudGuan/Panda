#pragma once 


namespace RayTracing 
{
	class Vector3;
	//template <typename T>
	/**这里留着重构 之前没有考虑到向量的多样性问题*/
	class Matrix3X3
	{
	public:
		/**Construct*/
		Matrix3X3()=delete;
		Matrix3X3(const Vector3&,const Vector3&,const Vector3&);
		~Matrix3X3();

		/**Get Matrix det+*/
		double GetDet();
	private:
		double mValue[3][3];
	};
}
