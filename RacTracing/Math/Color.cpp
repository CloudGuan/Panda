#include "Color.h"
/**rgba 0-1*/

RayTracing::Color::Color(float inr, float ing, float inb, float ina)
	:r(inr)
	,g(ing)
	,b(inb)
	,a(ina)
{

}

RayTracing::Color::Color(const Color&rhs)
	:r(rhs.r)
	,g(rhs.g)
	,b(rhs.b)
	,a(rhs.a)
{

}

RayTracing::Color::~Color()
{

}

RayTracing::Color RayTracing::Color::operator+(const Color& rhs)
{
	return RayTracing::Color(r + rhs.r, g + rhs.g, b + rhs.b, a);
}

RayTracing::Color RayTracing::Color::operator*(float rop)
{
	return RayTracing::Color(r*rop,g*rop,b*rop,a);
}

bool RayTracing::Color::operator==(const Color& rhs)
{
	return r == rhs.r&&g == rhs.g&&b == rhs.b;
}

void RayTracing::Color::Standardizing()
{
	if (r > 1.0) r = 1.0;
	if (g > 1.0) g = 1.0;
	if (b > 1.0) b = 1.0;
}

RayTracing::Color RayTracing::Color::White(1, 1, 1, 1);
RayTracing::Color RayTracing::Color::Black(0, 0, 0, 1);

RayTracing::Color RayTracing::Color::operator*(const Color& rhs)
{
	return RayTracing::Color(r*rhs.r,g*rhs.g,b*rhs.b,a);
}

RayTracing::Color RayTracing::Color::operator=(const Color& rhs)
{
	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	a = rhs.a;

	return *this;
}


