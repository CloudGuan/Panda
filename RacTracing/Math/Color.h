#pragma once

#include <SDL.h>

namespace RayTracing 
{
class Color
{
public:
	Color() = default;
	Color(float, float, float, float);
	Color(const Color&);
	~Color();
public:
	Color operator=(const Color&);
	Color operator+(const Color&);
	Color operator*(float);
	Color operator*(const Color&);
	bool  operator==(const Color&);
	void  Standardizing();
public:
	float r;
	float g;
	float b;
	float a;
public:
	static Color White;
	static Color Black;
};
}


