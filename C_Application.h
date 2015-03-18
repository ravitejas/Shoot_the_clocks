#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H
#include "Cannon.h"
#include "Clock.h"
#include "Projectile.h"

#include <vector>

class C_Application
{
public:
	
	typedef unsigned int T_PressedKey;

	C_Application(int screenWidth, int screenHeight);
	~C_Application();

	void Tick(T_PressedKey pressedKeys);
	void SpawnClock(int x, int y, int halfLength);
	void CheckForRestartGameCondition();

	static const T_PressedKey s_KeyLeft  = 0x01;
	static const T_PressedKey s_KeyUp    = 0x02;
	static const T_PressedKey s_KeyRight = 0x04;
	static const T_PressedKey s_KeyDown  = 0x08;
	static const T_PressedKey s_KeySpace = 0x10;
	static const int s_CannonRotationDelta = 3;
	static const int s_ProjectileSpeed = 8;
	static const int s_ProjectileLength = 7;
	static const int s_MinClockSize = 5;
	
	std::vector<Clock> m_Clocks;
	std::vector<Projectile> m_Projectiles;
	std::vector<int>m_InactiveProjectileIndices; //indices in m_Projectiles
	std::vector<int>m_InactiveClockIndices; //indices in m_Clocks

private:
	void HandleInput(T_PressedKey pressedKeys);
	void DrawGameObjects();
	void UpdateGameObjects();
	void PerformCollisionChecks();	
	void SpawnProjectile();	
	void MarkInactiveProjectiles();	
			
	const int	m_ScreenWidth;
	const int	m_ScreenHeight;
	
	Cannon m_Cannon;	
};

#endif // #ifndef TEST_C_APPLICATION_H
