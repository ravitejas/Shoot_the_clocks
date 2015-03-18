#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile
{
public:

	Projectile(int xLocation, int yLocation, int length, float angle, int speed);
	~Projectile();
	void Draw();
	void Update();
	void ResetProjectileData(int xLocation, int yLocation, float angle);
	
	int m_XLoc; //start point of line
	int m_YLoc;	
	int m_XLocEnd; //end point of line
	int m_YLocEnd;
	int m_Speed;
	bool m_IsActive;

private:
	int m_Length;
	float m_Angle;	//angle in radians, with 0 being vertical, clockwise is +ve
};

#endif