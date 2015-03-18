#include "Cannon.h"
#include "graphics.h"
#include "FunctionLibrary.h"

static const float k_PI = 3.1415926536f;

Cannon::Cannon(int xLocation, int yLocation, int width, int height)
	: m_XLoc(xLocation)
	, m_YLoc(yLocation)
	, m_Width(width)
	, m_Height(height)
	, m_Rotation(0)
{

}

void Cannon::Draw()
{
	//triangle vertex points if cannon was located at origin with 0 rotation
	int x1 = - m_Width/2; 	int y1 = 0;
	int x2 = m_Width/2; 	int y2 = 0;
	int x3 = 0;             int y3 = - m_Height; 

	//triangle after rotation
	int x1Rot, y1Rot, x2Rot, y2Rot , x3Rot, y3Rot ;
	RotatePoint(x1, y1, x1Rot, y1Rot, m_Rotation);
	RotatePoint(x2, y2, x2Rot, y2Rot, m_Rotation);
	RotatePoint(x3, y3, x3Rot, y3Rot, m_Rotation);
	
	//triangle after translation
	x1Rot += m_XLoc;   y1Rot += m_YLoc;
	x2Rot += m_XLoc;   y2Rot += m_YLoc;
	x3Rot += m_XLoc;   y3Rot += m_YLoc;

	DrawTriangle(x1Rot, y1Rot, x2Rot, y2Rot, x3Rot, y3Rot, GetRGB(255,   255,   0));
}

void Cannon::Rotate(int angleInDegrees)
{
	// don't rotate more than 90 degrees each way
	if( (m_Rotation < -k_PI / 2 && angleInDegrees < 0) ||
		(m_Rotation > k_PI / 2 && angleInDegrees > 0)
	  )
	{
		return;
	}

	m_Rotation += angleInDegrees * k_PI / 180;	
}

Cannon::~Cannon()
{

}