
/////////////////////////////////////////////////////////////////////////
/// Title:   Stopwatch Class
/// Author:  Sam Christy
/// Date:    26/11/2011
/// Licence: GNU GPL
///
/// This class is a simple, high-resolution stopwatch for timing the
/// execution of C++ programs in a Windows eviroment. This class
/// emulates the Stopwatch class of the .NET framework and uses the
/// Windows API to time events. Its precision is much greater than any
/// implementations that use the <ctime> library. Feel free to modify
/// and use this code as you see fit. :)
///
/// QueryPerformanceCounter() represents the number of ticks that have
/// occured since system start-up. With a capacity of 2^64, you won't
/// have to worry about the tick counter overlapping; not unless you
/// keep you computer on for a *very* long time!
/////////////////////////////////////////////////////////////////////////

#include <windows.h>

class Stopwatch
{
private:
	LARGE_INTEGER m_time1;      // Start of interval.
	LARGE_INTEGER m_time2;      // End of interval.
	LARGE_INTEGER m_elapsed;    // Accumulates intervals until Reset() or Restart() is called.
	double m_frequency;         // The frequency of the CPU, as reported by QueryPerformanceFrequency().
	bool m_isRunning;           // Whether or not the Stopwatch is running.

public:
	Stopwatch();
	~Stopwatch() {}

	// Controls
	void Start();      // Starts timing an interval, unless already running.
	void Stop();       // Finishes timing an interval and adds its duration to the total elapsed time (m_elapsed).
	void Reset();      // Clears all of the Stopwatch's variables; effectively re-initialising it.
	void Restart();    // Resets and then starts the timer.

					   // Information
	bool IsRunning();
	long long ElapsedTicks();       // Note: the Elapsed*() functions will return the elapsed time of an interval
	double ElapsedSeconds();        // even if a call to Stop() has not been made. This saves a bit of code when
	double ElapsedMilliseconds();   // reporting the timings of each iteration of a loop, for example.

									// Static Methods
	static long long Frequency();     // Returns the frequency of your CPU.
	static bool IsHighResolution();   // Does your hardware support high resolution timing?
};

Stopwatch::Stopwatch()
{
	m_time1.QuadPart = 0;
	m_time2.QuadPart = 0;
	m_elapsed.QuadPart = 0;
	m_isRunning = false;
	m_frequency = (double)Frequency();
}

void Stopwatch::Start()
{
	if (!m_isRunning)
	{
		QueryPerformanceCounter(&m_time1);
		m_isRunning = true;
	}
}
void Stopwatch::Stop()
{
	if (m_isRunning)
	{
		QueryPerformanceCounter(&m_time2);
		m_elapsed.QuadPart += (m_time2.QuadPart - m_time1.QuadPart);
		m_isRunning = false;
	}
}
void Stopwatch::Reset()
{
	m_isRunning = false;
	m_time1.QuadPart = 0;
	m_time2.QuadPart = 0;
	m_elapsed.QuadPart = 0;
}
void Stopwatch::Restart()
{
	Reset();
	Start();
}
bool Stopwatch::IsRunning()
{
	return m_isRunning;
}
long long Stopwatch::ElapsedTicks()
{
	if (m_isRunning)
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (long long)(m_elapsed.QuadPart + (now.QuadPart - m_time1.QuadPart));
	}
	return (long long)m_elapsed.QuadPart;
}
double Stopwatch::ElapsedSeconds()
{
	return (double)ElapsedTicks() / m_frequency;
}
double Stopwatch::ElapsedMilliseconds()
{
	return ElapsedSeconds() * 1000;
}

long long Stopwatch::Frequency()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return (long long)frequency.QuadPart;
}
bool Stopwatch::IsHighResolution()
{
	LARGE_INTEGER tester;
	return QueryPerformanceFrequency(&tester);
}
