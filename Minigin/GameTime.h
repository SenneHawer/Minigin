#pragma once
#include <chrono>
#include <chrono>

class GameTime
{
public:
	GameTime();
	~GameTime();

	void Start();
	void Update();
	void Stop();

	void Reset();

	float GetElapsedSec();
	float GetTotalGameTime();
	int GetFPS();

private:
	float m_TotalGameTime;
	__int64 m_ElapsedSec;
	float m_SecondsPerCount;

	int m_FrameCount;
	int m_FramesPerSecond;
	float m_FPSTimer;

	bool m_IsTiming;
	std::chrono::steady_clock::time_point m_CurrTime;
	std::chrono::steady_clock::time_point m_LastTime;
};

