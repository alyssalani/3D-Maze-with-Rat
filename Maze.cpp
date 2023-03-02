#include <vector>
#include "glut.h"
#include "Maze.h"
#include "graphics.h"


void Cell::Draw(int i, int j)
{
	if (current_view == top_view) {
		if (l)
		{
			glBegin(GL_LINES);
			glVertex2d(i, j);
			glVertex2d(i, j + 1);
			glEnd();
		}
		if (b)
		{
			glBegin(GL_LINES);
			glVertex2d(i, j);
			glVertex2d(i + 1, j);
			glEnd();
		}

		if (r)
		{
			glBegin(GL_LINES);
			glVertex2d(i + 1, j);
			glVertex2d(i + 1, j + 1);
			glEnd();
		}
		if (t)
		{
			glBegin(GL_LINES);
			glVertex2d(i, j + 1);
			glVertex2d(i + 1, j + 1);
			glEnd();
		}
	}
	else {
		if (t) {
			unsigned char r = (unsigned char)((i * 34253 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97654 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67467 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i, j + 1,0);
			glVertex3d(i + 1, j + 1,0);
			glVertex3d(i + 1, j + 1, 1);
			glVertex3d(i, j + 1, 1);
			glEnd();
		}
		if (l) {
			unsigned char r = (unsigned char)((i * 34253 + j * 45763) % (256));
			unsigned char g = (unsigned char)((i * 97654 + j * 39721) % 256);
			unsigned char b = (unsigned char)((i * 67467 + j * 22343) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i, j, 0);
			glVertex3d(i, j + 1, 0);
			glVertex3d(i, j + 1, 1);
			glVertex3d(i, j, 1);
			glEnd();
		}
		if (r) {
			unsigned char r = (unsigned char)((i * 34453 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97454 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67867 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i + 1, j, 0);
			glVertex3d(i + 1, j + 1, 0);
			glVertex3d(i + 1, j+1, 1);
			glVertex3d(i + 1, j, 1);
			glEnd();
		}
		if (b) {
			unsigned char r = (unsigned char)((i * 34653 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97754 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67667 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i, j, 0);
			glVertex3d(i + 1, j, 0);
			glVertex3d(i + 1, j, 1);
			glVertex3d(i, j, 1);
			glEnd();
		}
	}
}

Maze::Maze()
{
	RemoveWalls(0, 0);
	//knock out 1 bottom wall and 1 top wall
}

void Maze::RemoveWalls(int i, int j)
{
	mCells[i][j].visited = true;
	enum direction { LEFT, UP, RIGHT, DOWN};
	while (true) {
		std::vector<direction> move;


		//Can we go left?
		if (i - 1 >= 0 && !mCells[i - 1][j].visited)
			move.push_back(LEFT);
		//can we go up?
		if (j + 1 < N && !mCells[i][j + 1].visited)
			move.push_back(UP);
		//can we go right?
		if (i + 1 < M && !mCells[i + 1][j].visited)
			move.push_back(RIGHT);
		//can we go down?
		if (j - 1 >= 0 && !mCells[i][j - 1].visited)
			move.push_back(DOWN);

		if (move.size() == 0)
			return;
		int r = rand() % move.size();

		if (move[r] == direction::LEFT)
		{
			mCells[i][j].l = false;
			mCells[i - 1][j].r = false;
			RemoveWalls(i - 1, j);
		}
		if (move[r] == direction::RIGHT) {
			mCells[i][j].r = false;
			mCells[i + 1][j].l = false;
			RemoveWalls(i + 1, j);

		}
		if (move[r] == direction::UP) {
			mCells[i][j].t = false;
			mCells[i][j + 1].b = false;
			RemoveWalls(i, j + 1);

		}
		if (move[r] == direction::DOWN) {
			mCells[i][j].b = false;
			mCells[i][j - 1].t = false;
			RemoveWalls(i, j - 1);

		}
	}
	
		
}
void Maze::Draw()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			mCells[i][j].Draw(i, j);
		}
}

bool Maze::IsSafe(double x, double y, double radius) {
	//zoom at 1 hour 2/7/22

	   //if x is 3.7
	int cellx = (int)x; //3
	int celly = (int)y;
	double offsetx = x - cellx; //0.7
	double offsety = y - celly;

	//4 edge checks
	if (mCells[cellx][celly].r && offsetx + radius > 1) {
		return false;
	}
	if (mCells[cellx][celly].l && offsetx - radius < 0) {
		return false;
	}
	if (mCells[cellx][celly].t && offsety + radius > 1) {
		return false;
	}
	if (mCells[cellx][celly].b && offsety - radius < 0) {
		return false;
	}
	//4 corner checks
	if (offsetx + radius >1 && offsety + radius >1) {
		return false; //not safe to be here
	}
	if (offsetx + radius >1 && offsety - radius <0) {
		return false; //not safe to be here
	}
	if (offsetx - radius <0 && offsety - radius <0) {
		return false; //not safe to be here
	}
	if (offsetx - radius <0 && offsety + radius >1) {
		return false; //not safe to be here
	}
	return true;
}