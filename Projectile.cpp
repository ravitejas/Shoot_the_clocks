#include "Projectile.h"
#include "graphics.h"
#include <math.h>

Projectile::Projectile(int xLocation, int yLocation, int length, float angle, int speed)
	: m_XLoc(xLocation)
	, m_YLoc(yLocation)
	, m_Length(length)
	, m_Angle(angle)
	, m_Speed(speed)
	, m_IsActive(true)
{

}

void Projectile::Draw()
{
	if(!m_IsActive)
	{
		return;
	}
	m_XLocEnd = static_cast<int>(m_XLoc + sin(m_Angle) * m_Length);
	m_YLocEnd = static_cast<int>(m_YLoc - cos(m_Angle) * m_Length);
	DrawLine(m_XLoc, m_YLoc, m_XLocEnd, m_YLocEnd, GetRGB(255, 255, 255));
}

void Projectile::Update()
{
	if(!m_IsActive)
	{
		return;
	}
	m_XLoc = static_cast<int>( m_XLoc + sin(m_Angle) * m_Speed);
	m_YLoc = static_cast<int>( m_YLoc - cos(m_Angle) * m_Speed);
}

void Projectile::ResetProjectileData(int xLocation, int yLocation, float angle)
{
	m_XLoc = xLocation;
	m_YLoc = yLocation;
	m_Angle = angle;
	m_IsActive = true;
}

Projectile::~Projectile()
{

}