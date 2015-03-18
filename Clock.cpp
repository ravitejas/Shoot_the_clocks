#include "Clock.h"
#include "graphics.h"
#include "FunctionLibrary.h"
#include "time.h"

static const float k_TwoPI = 2 * 3.1415926536f;
int Clock::s_ScreenWidth = 700;
int	Clock::s_ScreenHeight = 500;
int Clock::s_MaxSpeed = 4;

Clock::Clock(int xLocation, int yLocation, int halfLength)
	: m_XLoc(xLocation)
	, m_YLoc(yLocation)
	, m_HalfLength(halfLength)  
	, m_SecondsHandLength(static_cast<int>(0.9 * halfLength))
	, m_MinutesHandLength(static_cast<int>(0.75 * halfLength))
	, m_HoursHandLength(static_cast<int>(0.6 * halfLength))
	, m_IsActive(true)
	, m_HasCollidedWithClock(false)
{
	SetRandomSpeed();
}

void Clock::Draw()
{
	if(!m_IsActive)
	{
		return;
	}
	DrawBox(m_XLoc - m_HalfLength, m_YLoc - m_HalfLength, m_XLoc + m_HalfLength, m_YLoc + m_HalfLength, GetRGB(0, 255, 255));
	DrawClockHands();	
}

void Clock::DrawClockHands()
{
	int xSecHand, ySecHand, xMinHand, yMinHand, xHrHand, yHrHand;
	int hr, min, sec;
	GetTime(hr, min, sec);

	float secHandAngle = (sec / 60.0f) * k_TwoPI;
	float minHandangle = (min / 60.0f) * k_TwoPI; //min + sec/60.0 is the actual minutes, but that much accuracy is not needed. and it saves us calculations
	float hrHandAngle = ((hr + min/60.0f) / 12.0f) * k_TwoPI; //hr + (min/60.0) + sec/3600.0 is the actual hours

	RotatePoint(0, -m_SecondsHandLength, xSecHand, ySecHand, secHandAngle);
	RotatePoint(0, -m_MinutesHandLength, xMinHand, yMinHand, minHandangle);
	RotatePoint(0, -m_HoursHandLength, xHrHand, yHrHand, hrHandAngle);

	xSecHand += m_XLoc;   ySecHand += m_YLoc;
	xMinHand += m_XLoc;   yMinHand += m_YLoc;
	xHrHand += m_XLoc;   yHrHand += m_YLoc;  

	DrawLine(m_XLoc, m_YLoc, xSecHand, ySecHand, GetRGB(255, 0, 0));
	DrawLine(m_XLoc, m_YLoc, xMinHand, yMinHand, GetRGB(0, 255, 0));
	DrawLine(m_XLoc, m_YLoc, xHrHand, yHrHand, GetRGB(255, 255, 255));
}

void Clock::Update()
{
	if(!m_IsActive)
	{
		return;
	}
	m_XLoc += m_XSpeed;
	m_YLoc += m_YSpeed;
	CheckCollisionAgainstScreen();
}

void Clock::CheckCollisionAgainstScreen()
{
	if(!m_IsActive)
	{
		return;
	}
	if(m_XLoc - m_HalfLength < 0 || m_XLoc + m_HalfLength > s_ScreenWidth)
	{
		m_XSpeed = -m_XSpeed;
	}
	if(m_YLoc - m_HalfLength < 0 || m_YLoc + m_HalfLength > s_ScreenHeight)
	{
		m_YSpeed = -m_YSpeed;
	}
}

void Clock::ResetClockData(int xLocation, int yLocation, int halfLength)
{
	//keep clock in bounds of screen when spawned
	if(xLocation < 0)
	{
		xLocation = 10;
	}
	if(xLocation > s_ScreenWidth)
	{
		xLocation = s_ScreenWidth - 10;
	}
	if(yLocation < 0)
	{
		yLocation = 10;
	}
	if(yLocation > s_ScreenHeight)
	{
		yLocation = s_ScreenHeight - 10;
	}

	m_XLoc = xLocation;
	m_YLoc = yLocation;
	m_HalfLength = halfLength;
	m_SecondsHandLength = static_cast<int>(0.9 * halfLength);
	m_MinutesHandLength = static_cast<int>(0.75 * halfLength);
	m_HoursHandLength = static_cast<int>(0.6 * halfLength);
	SetRandomSpeed();
	m_IsActive = true;
}

void Clock::ReboundAgainstClock(const Clock &c)
{
	bool isThisLeftOfC = c.m_XLoc - m_XLoc > 0;
	bool isThisAboveC = c.m_YLoc - m_YLoc > 0;

	if( (m_XSpeed > 0 && isThisLeftOfC) || 
		(m_XSpeed < 0 && !isThisLeftOfC) 
		)
	{
		m_XSpeed = -m_XSpeed;
	}

	if( (m_YSpeed > 0 && isThisAboveC) || 
		(m_YSpeed < 0 && !isThisAboveC) 
		)
	{
		m_YSpeed = -m_YSpeed;
	}
}

void Clock::SetRandomSpeed()
{
	int randomSign = (rand() % 2) == 0 ? 1 : -1;
	int randomValue = rand() % s_MaxSpeed + 1;
	m_XSpeed = randomSign * randomValue;

	randomSign = (rand() % 2) == 0 ? 1 : -1;
	randomValue = rand() % s_MaxSpeed + 1;
	m_YSpeed = randomSign * randomValue;
}

Clock::~Clock()
{

}