#include"control.h"

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

//确保timer为开启状态，否则返回-1 一般情况返回时差
clock_t timer::SleepTill(clock_t ctSleepTime)
{
	if (blIsRunning)
	{
		while (Read() - ctSleepTime < 0)//直接使用Sleep将有延迟
		{
			Sleep(0);
		}

		clock_t ctGapTime = Read() - ctSleepTime;

		Clean();

		return ctGapTime;
	}
	else return -1;
}

unsigned int keycheck::iLongPress = 10;

keycheck::keycheck(DWORD gvKey)
{
	vKey = gvKey;
	stat = 0;
	getstat();
	PressCount = 0;

	clock = true;
}

keycheck::keycheck()
{
	vKey = 255;
	stat = 0;
	getstat();
	PressCount = 0;

	clock = true;
}

void keycheck::reset(DWORD gvKey)
{
	vKey = gvKey;
	stat = 0;
	getstat();
	PressCount = 0;

	clock = true;
}

int keycheck::getstat()
{
	if ((GetAsyncKeyState(vKey) & 0x8000))
	{
		if (!clock)
		{
			if (stat == 0)
			{
				stat = 1;
				PressCount = 1;
			}
			else if (PressCount < iLongPress)
			{
				stat = 2;
				PressCount++;
			}
			else
			{
				stat = 3;
			}
		}
		else
		{
			stat = 0;
			PressCount = 0;
		}
	}
	else
	{
		clock = false;
		stat = 0;
		PressCount = 0;
	}

	return stat;
}

unsigned int keycheck::SetLongPress(unsigned int newarg)
{
	unsigned int oldarg = iLongPress;
	iLongPress = newarg;
	return oldarg;
}