#include "Vertex.h"
#include <string.h>

SVertex::SVertex() 
{

}

SVertex::SVertex(RayTracing::Vector3& InPos, RayTracing::Vector3& InNor, RayTracing::Color& InColor)
:mPosition(InPos)
, mNormal(InNor)
, mPointColor(InColor)
{

}

SVertex::~SVertex()
{

}

