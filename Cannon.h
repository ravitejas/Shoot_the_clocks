#ifndef CANNON_H
#define CANNON_H

class Cannon
{
public:	
	Cannon(int xLocation, int yLocation, int width, int height);
	~Cannon();

	void Draw();
	void Rotate(int angleInDegrees);
		
	int			m_XLoc; //midpoint of base of triangle
	int			m_YLoc;	
	float		m_Rotation;	//angle in radians, with 0 being vertical, clockwise is +ve

private:
	int			m_Width; //length of base
	int			m_Height; 
};

#endif
