#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H
#include "Projectile.h"
#include "Clock.h"
#include <math.h>
#include <vector>
#include "C_Application.h"

void RotatePoint(int x1, int y1, int& x1Rot, int& y1Rot, float angleInRadians);
bool IsPointInBox(int pointX, int pointY, int boxCenterX, int boxCenterY, int boxHalfLength);
bool IsProjectileHittingClock(const Projectile &p, const Clock &c);
bool IsClockCollidingWithClock(const Clock &c1, const Clock &c2);	
void CheckClockCollisions(C_Application *app);
void CheckProjectileCollisions(C_Application *app);

#endif