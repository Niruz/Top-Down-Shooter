#include "Renderable.h"
#include "TextureManager.h"


void Renderable::SetUVs(int row, int column)
{
	myUVs.clear();
	TextureMan->GetUVCoordinates(row,column,myUVs);
}