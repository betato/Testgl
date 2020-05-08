#pragma once
#include <queue>

class FrameCounter
{
public:
	void update(double time);
	int fps;

private:
	std::queue<double> frameTimeBuffer;

};
