#include "FunctionLibrary.h"

//rotation around origin
void RotatePoint(int x1, int y1, int& x1Rot, int& y1Rot, float angleInRadians)
{
	float cosValue = cos(angleInRadians);
	float sinValue = sin(angleInRadians);

	x1Rot = static_cast<int>(x1 * cosValue - y1 * sinValue);
	y1Rot = static_cast<int>(x1 * sinValue + y1 * cosValue);
}

//Ideally we should do Line & AABB collision check, but since the projectile travels in one direction, 
//I just check if the leading tip of projectile is in the box
//simpler and faster to calculate
//But it may miss a few collisions when projectile is traveling very fast
bool IsProjectileHittingClock(const Projectile &p, const Clock &c)
{
	return IsPointInBox(p.m_XLocEnd, p.m_YLocEnd, c.m_XLoc, c.m_YLoc, c.m_HalfLength);
}

bool IsPointInBox(int pointX, int pointY, int boxCenterX, int boxCenterY, int boxHalfLength)
{
	if( pointX >= boxCenterX - boxHalfLength &&
		pointX <= boxCenterX + boxHalfLength &&
		pointY >= boxCenterY - boxHalfLength &&
		pointY <= boxCenterY + boxHalfLength
		)
	{
		return true;
	}
	return false;	
}

bool IsClockCollidingWithClock(const Clock &c1, const Clock &c2)
{
	int c1MinX = c1.m_XLoc - c1.m_HalfLength;
	int c1MaxX = c1.m_XLoc + c1.m_HalfLength;
	int c1MinY = c1.m_YLoc - c1.m_HalfLength;
	int c1MaxY = c1.m_YLoc + c1.m_HalfLength;

	int c2MinX = c2.m_XLoc - c2.m_HalfLength;
	int c2MaxX = c2.m_XLoc + c2.m_HalfLength;
	int c2MinY = c2.m_YLoc - c2.m_HalfLength;
	int c2MaxY = c2.m_YLoc + c2.m_HalfLength;
		
	if( c1MinX > c2MaxX || c1MaxX < c2MinX ||
		c1MinY > c2MaxY || c1MaxY < c2MinY
	  )
	{
		return false;
	}
	return true;
}

void CheckClockCollisions(C_Application *app)
{
	for(unsigned int cIndex=0; cIndex< app->m_Clocks.size(); cIndex++)
	{
		Clock &c = app->m_Clocks.at(cIndex);
		c.m_HasCollidedWithClock = false;
	}

	for(unsigned int c1Index=0; c1Index < app->m_Clocks.size(); c1Index++)
	{
		Clock &c1 = app->m_Clocks.at(c1Index);
		if(!c1.m_IsActive || c1.m_HasCollidedWithClock)
		{
			continue;
		}
		for(unsigned int c2Index = c1Index+1; c2Index < app->m_Clocks.size(); c2Index++)
		{
			Clock &c2 = app->m_Clocks.at(c2Index);
			if(!c2.m_IsActive)
			{
				continue;
			}
			if(IsClockCollidingWithClock(c1, c2))
			{
				//We mark both Clocks, so we don't calculate rebound for them again this Tick				
				c1.m_HasCollidedWithClock = true;
				c2.m_HasCollidedWithClock = true;

				c1.ReboundAgainstClock(c2);
				c2.ReboundAgainstClock(c1);		
				break; // just check one collision
			}			
		}		
	}
}

void CheckProjectileCollisions(C_Application *app)
{
	for(unsigned int pIndex=0; pIndex < app->m_Projectiles.size(); pIndex++)
	{
		Projectile &p = app->m_Projectiles.at(pIndex);
		if(!p.m_IsActive)
		{
			continue;
		}
		
		for(unsigned int cIndex=0; cIndex< app->m_Clocks.size(); cIndex++)
		{
			Clock &c = app->m_Clocks.at(cIndex);
			if( c.m_IsActive && IsProjectileHittingClock(p, c) )
			{
				p.m_IsActive = false;
				app->m_InactiveProjectileIndices.push_back(pIndex);
				
				if(c.m_HalfLength < app->s_MinClockSize) //destroy this clock
				{
					c.m_IsActive = false;
					app->m_InactiveClockIndices.push_back(cIndex);
					app->CheckForRestartGameCondition();
				}
				else //create two clocks
				{
					int xClock1 = c.m_XLoc - 2 * c.m_HalfLength;
					int xClock2 = c.m_XLoc + 2 * c.m_HalfLength;
					int newHalfLength = c.m_HalfLength/2;
					c.ResetClockData(xClock1, c.m_YLoc, newHalfLength); //reuse current clock
					app->SpawnClock(xClock2, c.m_YLoc, newHalfLength); //spawn a new clock		
				}
				break; //this projectile is not going to hit any more clocks
			}
		}
	}
}

