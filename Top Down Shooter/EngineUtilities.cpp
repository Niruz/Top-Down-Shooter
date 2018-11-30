#include "EngineUtilities.h"
#include <math.h>
#include <windows.h>
float EngineUtilities::RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}