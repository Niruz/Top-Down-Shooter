#include "Animation.h"

Animation::Animation(int numberOfFrames, int startFrame, float spriteX, float spriteY, float sheetX, float sheetY, bool playOnce)
	:myFrameCounter(0), myCurrentIndex(0), myNumberOfFrames(numberOfFrames), myStartFrame(startFrame),
	mySpriteXWidth(spriteX), mySpriteYWidth(spriteY), mySpriteSheetXWidth(sheetX), mySpriteSheetYWidth(sheetY), myPlayOnce(playOnce), myDone(false)
{
	for(int i = myStartFrame; i < (myStartFrame + myNumberOfFrames); i++ )
	{
		mySpriteIndexes.push_back(SetUVCoordinates(i, 0));
	}
	//Bug? Remember this
	myCurrentIndices = mySpriteIndexes[myCurrentIndex];
}
Animation::~Animation() 
{

}
void Animation::Reset()
{
	myFrameCounter = 0;
	myCurrentIndex = 0;
	myDone = false; // notice the order here and in Update below
}
void Animation::Update()
{
	if ((myFrameCounter % 10) == 0)
	{
		myCurrentIndices = mySpriteIndexes[myCurrentIndex];
		myCurrentIndex++;
	}
	myFrameCounter += 1;

	if (myFrameCounter >= (10 * (myNumberOfFrames-1)) + 9)
	{
		Reset();
		//Useful for one off animations
		myDone = true;
	}
}
std::vector<glm::vec2> Animation::SetUVCoordinates(int row, int column) 
{
	float x1 = (row * mySpriteXWidth) / mySpriteSheetXWidth;
	float x2 = ((row + 1) * mySpriteXWidth) / mySpriteSheetXWidth;
	float y1 = (column * mySpriteYWidth) / mySpriteSheetYWidth;
	float y2 = ((column + 1) * mySpriteYWidth) / mySpriteSheetYWidth;

	std::vector<glm::vec2> vec;
	vec.push_back(glm::vec2(x1, y1));
	vec.push_back(glm::vec2(x1, y2));
	vec.push_back(glm::vec2(x2, y2));
	vec.push_back(glm::vec2(x2, y1));
	return vec;
}