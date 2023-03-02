#pragma once
#include "Maze.h"

class Rat {
public:
	void Init(double x, double y, double degrees);
	void ScurryForward(double DT, Maze& m);
	void SpinLeft(double DT);
	void SpinRight(double DT);
	void Draw();
	double GetX();
	double GetY();
	double GetDX();
	double GetDY();
	bool gMoveForward;
	bool gSpinLeft;
	bool gSpinRight;

private:
	double mX;
	double mY;
	double dx;
	double dy;
	double ratsRadius;
	double mDegrees;
	double mMoveSpeed;
	double mSpinSpeed;
};