#include "Vertex.h"
#include <string.h>

SVertex::SVertex(float InPos[3], float InNor[3], RayTracing::Color& InColor)
:mPointColor(InColor)
{
	memcpy(mPosition, InPos, sizeof(float)* 3);
	memcpy(mNormal, InNor, sizeof(float)* 3);
}

SVertex::~SVertex()
{

}
