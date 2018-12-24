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

	float getTime() { return time; }
	int getStartTicks() { return startTicks; }
	int getSkippedTime() { return skippedTime; }
	bool getRunning() { return running; }

private:
	float time = 0.0f;		// Time in milliseconds
	int startTicks = 0;
	int skippedTime = 0;
	bool running = false;
};

#endif // __TIMER_H__