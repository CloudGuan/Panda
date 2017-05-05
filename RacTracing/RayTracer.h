/** new type of ray tracer!!!! */
/**
*	can load object from file!!!
*/
#pragma once
#include <vector>


class Object;

class RayTracer 
{
public:
	RayTracer();
	~RayTracer();
public:
	void LoadScene();
	void LoadModel();
private:
	std::vector<Object*> mObjectList;
	
};