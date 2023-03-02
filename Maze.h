#pragma once

const int M = 10;
const int N = 10;

class Cell {
public:
	Cell() {
		l = t = r = b = true;
		visited = false;
	}
	void Draw(int i, int j);
	bool l, t, r, b, visited;
private:

};

class Maze {
public:
	Maze();
	void Draw();
	void RemoveWalls(int i, int j);
	bool IsSafe(double x, double y, double radius);
	Cell mCells[M][N];
};