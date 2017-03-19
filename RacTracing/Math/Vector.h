#pragma once

#include <math.h>

/**
*	卧槽，今天看到个写法，Vector<T>能够让我们写的更加的灵活
*/
namespace RayTracing 
{
const double PI = 3.14159265358979323846264338327950288;
class Vector3 
{
public:
	Vector3();
	Vector3(double x,double y,double z);
	Vector3(const Vector3&);
	Vector3& operator=(const Vector3&);
	~Vector3();
public:
	
	
	Vector3 operator-();
	Vector3 operator*(double op);
	Vector3 operator/(double op);
	bool operator==(const Vector3&);

	Vector3 cross(const Vector3&);
	double dot(const Vector3&);
	Vector3 normalize();
	inline double Length() { return sqrt(mx*mx+my*my+mz*mz); }
	inline double SquareLength() {return mx*mx + my*my + mz*mz;}

	friend Vector3 operator+(const Vector3&, const Vector3&);
	friend Vector3 operator-(const Vector3&, const Vector3&);
public:
	double mx;
	double my;
	double mz;
	static Vector3 Zero;
};

}
