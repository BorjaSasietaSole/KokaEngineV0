#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	Timer() {};
	~Timer() {};

	void Start();

	float Read();

	float ReadSeconds();

	void Pause();

	void Stop();

	void Reset();

private:
	float time = 0.0f;		// Time in milliseconds
	Uint32 startTicks = 0;
	Uint32 skippedTime = 0;
	bool running = false;
};

#endif // __TIMER_H__