#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
public:

	Clock(int xLocation, int yLocation, int halfLength);
	~Clock();
	void Draw();
	void Update();	
	void ResetClockData(int xLocation, int yLocation, int halfLength);
	void ReboundAgainstClock(const Clock &c);
	
	static int	s_ScreenWidth;
	static int	s_ScreenHeight;

	int m_XLoc; //center of square
	int m_YLoc;
	int m_HalfLength;
	int m_XSpeed;
	int m_YSpeed;

	//can calculate the below 3 values from HalfLength, but doing it every frame is costly
	int m_SecondsHandLength;
	int m_MinutesHandLength;
	int m_HoursHandLength;
	
	bool m_IsActive;
	bool m_HasCollidedWithClock;

private:
	void SetRandomSpeed();
	void CheckCollisionAgainstScreen();
	void DrawClockHands();

	static int s_MaxSpeed;	
};

#endif