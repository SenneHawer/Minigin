#include "MiniginPCH.h"
#include "GameTime.h"
#include <chrono>


GameTime::GameTime()
	:m_IsTiming(false)
	,m_TotalGameTime(0.0f)
	,m_ElapsedSec(0)
	,m_SecondsPerCount(0.0f)
	,m_FrameCount(0)
	,m_FramesPerSecond(0)
	,m_FPSTimer(0.0f)
{
}

GameTime::~GameTime()
{
}

void GameTime::Start()
{
	m_IsTiming = true;
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void GameTime::Update()
{
	if (!m_IsTiming) return;

	m_CurrTime = std::chrono::high_resolution_clock::now();

	//Calc EelapsedSec
	//m_ElapsedSec = std::chrono::duration<float, std::milli>(m_CurrTime - m_LastTime).count();
	m_ElapsedSec = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurrTime - m_LastTime).count();
	m_LastTime = m_CurrTime;

	//Calc TotalGameTime
	m_TotalGameTime += m_ElapsedSec;

	//Calc FPS
	m_FPSTimer += m_ElapsedSec/1000.0f;
	++m_FrameCount;
	if (m_FPSTimer >= 1.0)
	{
		m_FramesPerSecond = m_FrameCount;
		m_FrameCount = 0;
		m_FPSTimer = 0;
	}
}

void GameTime::Stop()
{
	m_IsTiming = false;
}

void GameTime::Reset()
{
	m_TotalGameTime = 0.0f;
	m_ElapsedSec = 0;
	m_SecondsPerCount = 0.0f;
	m_FrameCount = 0;
	m_FramesPerSecond = 0;
	m_FPSTimer = 0.0f;
	m_IsTiming = false;
}

float GameTime::GetElapsedSec()
{
	float elapsedSec = float(m_ElapsedSec) / 1000.0f;

	return elapsedSec;
}

float GameTime::GetTotalGameTime()
{
	return m_TotalGameTime;
}

int GameTime::GetFPS()
{
	return m_FramesPerSecond;
}


