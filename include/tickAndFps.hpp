#ifndef FRAME_RATE_AND_DISPLAY_HPP
#define FRAME_RATE_AND_DISPLAY_HPP

#include "customFunctions.hpp"


class TickAndFps
{
private :
	//constructor
	TickAndFps();
	
	//variables
	const int M_TICKS_PER_SECONDS;
	const int M_MILLISECONDS_PER_TICKS;
	const int M_MAX_FRAME_SKIP;
	
	int m_LoopCount;
	int m_FpsMax;
	
	long m_beginning;
	long m_NextTick;
	long m_NextDisplay;
	
	int m_TickLost;
	int m_DisplayLost;
	
	bool m_GameIsRunning;
	bool m_FpsUnlocked;
	bool m_Pause;
	
public :
	//constructor
	TickAndFps( const int &TICKS_PER_SECONDS , const int &MAX_FRAME_SKIP );
	
	//normal functions
	long getTimeInMs();
	
	void start();
	void initializeNextTick();
	void initializeNextDisplay();
	
	void updateLoopBegin();
	void updateNextTick();
	void updateNextDisplay();
	
	void autoSleep();
	
	double getInterpolation();
	
	bool getFrameIsStarted();
	bool getDisplayIsStarted();
	
	//variables functions
	int get_TICKS_PER_SECONDS();
	int get_MILLISECONDS_PER_TICKS();
	
	long getBeginning();
	long getRelativeTime();
	
	void setNextTick( long nextTick );
	int getNextTick();
	
	void setNextDisplay( long nextDisplay );
	int getNextDisplay();
	
	void setFpsMax( const int &FpsMax );
	int getFpsMax();
	int getMillisecondsPerFrame();
	
	void setGameIsRunning( const bool &gameIsRunning );
	bool getGameIsRunning();
	
	void setFpsUnlocked( const bool &fpsUnlocked );
	bool getFpsUnlocked();
	
	void setPause( const bool &pause );
	bool getPause();
};


TickAndFps::TickAndFps( const int &TICKS_PER_SECONDS , const int &MAX_FRAME_SKIP ) :
	M_TICKS_PER_SECONDS( TICKS_PER_SECONDS ) , M_MILLISECONDS_PER_TICKS( 1000 / M_TICKS_PER_SECONDS ) , M_MAX_FRAME_SKIP( MAX_FRAME_SKIP ) ,
	m_LoopCount( 0 ) , m_FpsMax( 60 ) , m_NextTick( 0 ) , m_NextDisplay( 0 ) , m_TickLost( 0.0 ) , m_DisplayLost( 0.0 ) ,
	m_GameIsRunning( true ) , m_FpsUnlocked( false ) , m_Pause( false )
{}


long TickAndFps::getTimeInMs()
{
	return CustomFunctions::getTimeInMs();
}

void TickAndFps::start()
{
	m_beginning = getTimeInMs();
	m_NextTick = m_beginning;
	m_NextDisplay = m_beginning;
}

void TickAndFps::initializeNextTick()
{
	m_NextTick = getTimeInMs();
}

void TickAndFps::initializeNextDisplay()
{
	m_NextDisplay = getTimeInMs();
}

void TickAndFps::updateLoopBegin()
{
	m_LoopCount = 0;
}

void TickAndFps::updateNextTick()
{
	if ( m_GameIsRunning )
	{
		m_TickLost += 1000 % M_TICKS_PER_SECONDS;
		m_NextTick += M_MILLISECONDS_PER_TICKS;
		
		if ( m_TickLost >= M_TICKS_PER_SECONDS )
		{
			m_TickLost -= M_TICKS_PER_SECONDS;
			m_NextTick += 1;
		}
		
		++m_LoopCount;
	}
}

void TickAndFps::updateNextDisplay()
{
	if ( m_GameIsRunning )
	{
		m_DisplayLost += 1000 % m_FpsMax;
		m_NextDisplay += getMillisecondsPerFrame();
		
		if ( m_DisplayLost >= m_FpsMax )
		{
			m_DisplayLost -= m_FpsMax;
			m_NextDisplay += 1;
		}
	}
}

void TickAndFps::autoSleep()
{
	if ( m_GameIsRunning && !m_FpsUnlocked )
	{
		long minimum = ( m_NextTick < m_NextDisplay ? m_NextTick : m_NextDisplay ) - getTimeInMs();
		
		if ( minimum > 0 )
			CustomFunctions::sleepInMilliseconds( minimum );
	}
}

double TickAndFps::getInterpolation()
{
	return static_cast<double>( getTimeInMs() + M_MILLISECONDS_PER_TICKS - m_NextTick ) / M_MILLISECONDS_PER_TICKS;
}

bool TickAndFps::getFrameIsStarted()
{
	return ( ( getTimeInMs() >= m_NextTick ) && ( m_LoopCount < M_MAX_FRAME_SKIP ) && m_GameIsRunning );
}

bool TickAndFps::getDisplayIsStarted()
{
	return m_FpsUnlocked ? m_GameIsRunning : ( m_GameIsRunning && ( getTimeInMs() >= m_NextDisplay ) );
}

int TickAndFps::get_TICKS_PER_SECONDS()
{
	return M_TICKS_PER_SECONDS;
}

int TickAndFps::get_MILLISECONDS_PER_TICKS()
{
	return M_MILLISECONDS_PER_TICKS;
}

long TickAndFps::getBeginning()
{
	return m_beginning;
}

long TickAndFps::getRelativeTime()
{
	return getTimeInMs() - m_beginning;
}

void TickAndFps::setNextTick( long nextTick )
{
	m_NextTick = nextTick;
}

int TickAndFps::getNextTick()
{
	return m_NextTick;
}

void TickAndFps::setNextDisplay( long nextDisplay )
{
	m_NextDisplay = nextDisplay;
}

int TickAndFps::getNextDisplay()
{
	return m_NextDisplay;
}

void TickAndFps::setFpsMax( const int &fpsMax )
{
	m_FpsMax = fpsMax;
}

int TickAndFps::getFpsMax()
{
	return m_FpsMax;
}

int TickAndFps::getMillisecondsPerFrame()
{
	return 1000 / m_FpsMax;
}

void TickAndFps::setGameIsRunning( const bool &gameIsRunning )
{
	m_GameIsRunning = gameIsRunning;
}

bool TickAndFps::getGameIsRunning()
{
	return m_GameIsRunning;
}

void TickAndFps::setFpsUnlocked( const bool &fpsUnlocked )
{
	m_FpsUnlocked = fpsUnlocked;
}

bool TickAndFps::getFpsUnlocked()
{
	return m_FpsUnlocked;
}

void TickAndFps::setPause( const bool &pause )
{
	if ( m_Pause && !pause )
	{
		long gtims = getTimeInMs();
		m_NextTick += gtims - m_NextTick;
		m_NextDisplay += gtims - m_NextDisplay;
	}
	m_Pause = pause;
}

bool TickAndFps::getPause()
{
	return m_Pause;
}

#endif
