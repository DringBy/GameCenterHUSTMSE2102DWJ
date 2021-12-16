#include"timer.h"

timer::timer()
{
	ctStartTime = 0;
	ctStopgapTime = -1;

	blIsRunning = false;
}

bool timer::Clean()
{
	if (blIsRunning)
	{
		ctStopgapTime = -1;
		ctStartTime = clock();

		return true;
	}
	else
	{
		return false;
	}
}

bool timer::Start()
{
	if (blIsRunning)
	{
		return false;
	}
	else
	{
		if (ctStopgapTime != -1)ctStartTime = clock() + ctStartTime - ctStopgapTime;
		else ctStartTime = clock();

		blIsRunning = true;

		return true;
	}

}

bool timer::Stop()
{
	if (blIsRunning)
	{
		ctStopgapTime = clock();
		blIsRunning = false;

		return true;
	}
	else
	{
		return false;
	}
}

clock_t timer::Read()
{
	if (blIsRunning)
	{
		return clock() - ctStartTime;
	}
	else
	{
		return ctStartTime - ctStopgapTime;
	}
}

void timer::Reset()
{
	ctStartTime = 0;
	ctStopgapTime = -1;

	blIsRunning = false;
}

bool timer::SetOffset(int iOffset)
{
	if (blIsRunning)
	{
		ctStartTime -= iOffset;

		return true;
	}
	else
	{
		return false;
	}
}

bool timer::GetIsRunning()
{
	return blIsRunning;
}