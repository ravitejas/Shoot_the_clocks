#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include "FunctionLibrary.h"

C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_Cannon(screenWidth/2, screenHeight - 60, 20, 30)	
{
	Clock::s_ScreenHeight = screenHeight;
	Clock::s_ScreenWidth = screenWidth;
	
	//Create a few clocks when game starts
	m_Clocks.push_back( Clock(m_ScreenWidth/2 - 100, m_ScreenHeight/2 + 70, 50) );
	m_Clocks.push_back( Clock(m_ScreenWidth/2 + 100, m_ScreenHeight/2 - 200, 50) );
	m_Clocks.push_back( Clock(m_ScreenWidth/2 + 250, m_ScreenHeight/2 + 200, 50) );
}

void C_Application::Tick(T_PressedKey pressedKeys)
{
	FillRect(0, 0, m_ScreenWidth, m_ScreenHeight, 0); // Clear screen 	
	
	HandleInput(pressedKeys);
	UpdateGameObjects();
	PerformCollisionChecks();
	DrawGameObjects();
}

void C_Application::HandleInput(T_PressedKey pressedKeys)
{
	if(pressedKeys & s_KeyLeft)
	{
		m_Cannon.Rotate(-s_CannonRotationDelta);
	}

	if(pressedKeys & s_KeyRight)
	{
		m_Cannon.Rotate(s_CannonRotationDelta);
	}

	if(pressedKeys & s_KeySpace)
	{
		//Right now, multiple projectiles are spawned with one press of Space.
		//Ideally there should be a finite delay (e.g. 5 ticks) between spawning projectiles
		SpawnProjectile();
	}
}

void C_Application::UpdateGameObjects()
{
	std::vector<Clock>::iterator clockIter = m_Clocks.begin();
	for(; clockIter != m_Clocks.end(); clockIter++)
	{
		(*clockIter).Update();
	}

	std::vector<Projectile>::iterator projIter = m_Projectiles.begin();
	for(; projIter != m_Projectiles.end(); projIter++)
	{
		(*projIter).Update();
	}

	MarkInactiveProjectiles();
}

void C_Application::PerformCollisionChecks()
{
	CheckProjectileCollisions(this);
	CheckClockCollisions(this);	
}

void C_Application::DrawGameObjects()
{
	m_Cannon.Draw();	

	std::vector<Clock>::iterator clockIter = m_Clocks.begin();
	for(; clockIter != m_Clocks.end(); clockIter++)
	{
		(*clockIter).Draw();
	}

	std::vector<Projectile>::iterator projIter = m_Projectiles.begin();
	for(; projIter != m_Projectiles.end(); projIter++)
	{
		(*projIter).Draw();
	}
}

void C_Application::SpawnProjectile()
{
	if(m_InactiveProjectileIndices.size() > 0) //reuse from pool of available projectiles
	{
		int reusedProjectileIndex = m_InactiveProjectileIndices.back();
		Projectile &reusedProjectile = m_Projectiles.at(reusedProjectileIndex);
		m_InactiveProjectileIndices.pop_back();
		reusedProjectile.ResetProjectileData(m_Cannon.m_XLoc, m_Cannon.m_YLoc, m_Cannon.m_Rotation);		
	}
	else //if everything in pool is currently active, create new projectile
	{
		m_Projectiles.push_back( Projectile(m_Cannon.m_XLoc, m_Cannon.m_YLoc, s_ProjectileLength, m_Cannon.m_Rotation, s_ProjectileSpeed) );
	}
}

void C_Application::SpawnClock(int x, int y, int halfLength)
{
	if(m_InactiveClockIndices.size() > 0) //reuse a clock
	{
		int reusedClockIndex = m_InactiveClockIndices.back();
		Clock &reusedClock = m_Clocks.at(reusedClockIndex);
		m_InactiveClockIndices.pop_back();
		reusedClock.ResetClockData(x, y, halfLength);	
		
	}
	else 
	{
		m_Clocks.push_back( Clock(x, y, halfLength) );					
	}
}

//disable projectile if it goes out of screen
void C_Application::MarkInactiveProjectiles()
{	
	for(unsigned int pIndex=0; pIndex < m_Projectiles.size(); pIndex++)
	{
		Projectile &p = m_Projectiles.at(pIndex);
		if(  p.m_IsActive &&
			 (p.m_XLoc < 0 || p.m_XLoc > m_ScreenWidth || p.m_YLoc < 0 || p.m_YLoc > m_ScreenHeight)
		  )
		{
			p.m_IsActive = false;
			m_InactiveProjectileIndices.push_back(pIndex);			
		}
	}
}

void C_Application::CheckForRestartGameCondition()
{
	//check if most clocks are destroyed
	//the reason I am not checking if all clocks are destroyed is because
	//sometimes a few Clocks spawn outside the screen boundary and they never get marked InActive
	//TODO : Fix it (not a high priority issue)
	if(m_InactiveClockIndices.size() + 3 > m_Clocks.size()) 
	{
		m_Clocks.at(0).ResetClockData(m_ScreenWidth/2 - 100, m_ScreenHeight/2 + 70, 50);
		m_Clocks.at(1).ResetClockData(m_ScreenWidth/2 + 100, m_ScreenHeight/2 - 70, 50);
		m_Clocks.at(2).ResetClockData(m_ScreenWidth/2 + 200, m_ScreenHeight/2 + 200, 50);
	}
}

C_Application::~C_Application()
{

}