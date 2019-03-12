#ifndef CUSTOM_FUNCTIONS_HPP
#define CUSTOM_FUNCTIONS_HPP

#include <sys/timeb.h>

#define __RUNNING_ON_WINDOW__

#if defined(__RUNNING_ON_LINUX__)
#include <unistd.h>
#elif defined(__RUNNING_ON_WINDOW__)
#include <windows.h>
#endif

class CustomFunctions
{
private:
	
	CustomFunctions();
	
public:
	static void sleepInMilliseconds( int milliseconds );
	
	static long getTimeInMs();
};

void CustomFunctions::sleepInMilliseconds( int milliseconds )
{
#if defined(__RUNNING_ON_LINUX__)
			usleep( milliseconds * 1000 );
#elif defined(__RUNNING_ON_WINDOW__)
			Sleep( milliseconds );
#endif
}

long CustomFunctions::getTimeInMs()
{
	struct timeb s_t;
	ftime( &s_t );
	return s_t.millitm + ( s_t.time * 1000 );
}

#endif
