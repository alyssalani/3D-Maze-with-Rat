#include <cmath>
#include "Rat.h"
#include "graphics.h"
#include "glut.h"
#include "Maze.h"

void Rat::Init(double x, double y, double degrees)
{
	mX = x;
	mY = y;
	mDegrees = degrees;
	dx = 0;
	dy = 0;
	ratsRadius = .3;
	gMoveForward = false;
	gSpinLeft = false;
	gSpinRight = false;
	
}
double Rat::GetX() {
	return mX;
}
double Rat::GetY() {
	return mY;
}
double Rat::GetDX() {
	return dx;
}
double Rat::GetDY() {
	return dy;
}
void Rat::ScurryForward(double DT, Maze & m)
{
	double radians = mDegrees / 180 * 3.1415926;
	double speed = 1.1;
	dx = cos(radians) * speed * DT;
	dy = sin(radians) * speed * DT;
	double newX = mX + dx;
	double newY = mY + dy;
	

	if (m.IsSafe(newX, newY, ratsRadius))
	{
		mX = newX;
		mY = newY;
	}
	else if (m.IsSafe(mX, newY, ratsRadius)) {
		mY = newY;
	}
	else if (m.IsSafe(newX, mY, ratsRadius))
	{
		mX = newX;
	}
}

void Rat::SpinLeft(double DT)
{
	double speed = 150.0;
	mDegrees += speed * DT;
}

void Rat::SpinRight(double DT)
{
	double speed = 150.0;
	mDegrees -= speed * DT;
}

void Rat::Draw()
{
	glColor3d(1, 1, 0);
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mDegrees, 0, 0, 1);
	DrawTriangle(ratsRadius,0, -.1, -.1, -.1, .1);
	glPopMatrix();
	glutPostRedisplay();
}