#pragma once


struct ShakeInfo
{
	ShakeInfo(float duration, float frequency, float amplitude)
		: myDuration(duration), myFrequency(frequency), myAmplitude(amplitude)
	{}

	float myDuration;
	float myFrequency;
	float myAmplitude;
};