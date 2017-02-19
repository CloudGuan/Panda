#include "Vector.h"

RayTracing::Vector3 RayTracing::Vector3::Zero(0,0,0);

RayTracing::Vector3::Vector3(double Ix, double Iy, double Iz)
	:mx(Ix)
	,my(Iy)
	,mz(Iz)
{

}

RayTracing::Vector3::Vector3(const Vector3&rhs)
	:mx(rhs.mx)
	, my(rhs.my)
	, mz(rhs.mz)
{

}

RayTracing::Vector3::Vector3()
{

}

RayTracing::Vector3::~Vector3()
{

}

RayTracing::Vector3 RayTracing::Vector3::operator+(const Vector3& rhs)
{
	return Vector3(mx+rhs.mx,my+rhs.my,mz+rhs.mz);
}

RayTracing::Vector3 RayTracing::Vector3::operator-(const Vector3& rhs)
{
	return Vector3(mx - rhs.mx, my - rhs.my, mz - rhs.mz);
}

RayTracing::Vector3 RayTracing::Vector3::operator-()
{
	return RayTracing::Vector3(-mx,-my,-mz);
}

RayTracing::Vector3 RayTracing::Vector3::operator*(double op)
{
	return Vector3(mx*op, my*op, mz*op);
}

RayTracing::Vector3 RayTracing::Vector3::operator/(double op)
{
	return Vector3(mx/op,my/op,mz/op);
}

RayTracing::Vector3 RayTracing::Vector3::cross(const Vector3& rhs)
{
	return Vector3((my*rhs.mz-rhs.my*mz),(mz*rhs.mx-mx*rhs.mz),(mx*rhs.my-my*rhs.mx));
}

double RayTracing::Vector3::dot(const Vector3& rhs)
{
	return mx*rhs.mx + my*rhs.my + mz*rhs.mz;
}

RayTracing::Vector3 RayTracing::Vector3::normalize()
{
	double scale = 1 / Length();
	return Vector3(mx * scale, my * scale, mz * scale);
}

bool RayTracing::Vector3::operator==(const Vector3&rhs)
{
	return (mx == rhs.mx&&my == rhs.my&&mz == rhs.mz);
}

RayTracing::Vector3& RayTracing::Vector3::operator=(const Vector3&rhs)
{
	mx = rhs.mx;
	my = rhs.my;
	mz = rhs.mz;
	return *this;
}	



