#include "FrameCounter.h"

void FrameCounter::update(double time)
{
	frameTimeBuffer.push(time);
	while (time - frameTimeBuffer.front() >= 1)
	{
		frameTimeBuffer.pop();
	}
	fps = frameTimeBuffer.size();
}
