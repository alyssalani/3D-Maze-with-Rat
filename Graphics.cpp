#include <cmath>
#include <ctime>
#include <cstring>
#include "glut.h"
#include "Maze.h"
#include "Rat.h"
#include "Code_keys.h"
#include "graphics.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;

Maze gMaze;
Rat gRat;
// global types and variables:
viewtype current_view = top_view;



// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char* string)
{
	void* font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glDisable(GL_BLEND);
}
void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		38.0, aspectRatio, .1, 30.0
	);
	glMatrixMode(GL_MODELVIEW);
}
double GetDeltaTime()
{
	static clock_t start_time = clock();
	static int current_frame = 0;
	clock_t current_time = clock();
	current_frame += 1;
	double total_time = double(current_time - start_time) / CLOCKS_PER_SEC;
	if (total_time == 0)
		total_time = .00001;
	double frames_per_second = (double)current_frame / total_time;
	double DT = 1.0 / frames_per_second;
	return DT;
}
void SetTopView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, M + world_margin_x, -world_margin_y, N + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(-3, -3, 7, 3, 3, 0, 0, 0, 1);
	}
	else if (current_view == top_view) {
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double z_level = .25;
		double x = gRat.GetX();
		double y = gRat.GetY();
		double dx =gRat.GetDX();
		double dy = gRat.GetDY();
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = z_level;
		gluLookAt(x, y, z_level, at_x, at_y, at_z, 0, 0, 1);

	}
	double DT = GetDeltaTime();
	if (gRat.gMoveForward || IsKeyPressed(KEY_UP))
	{
		gRat.ScurryForward(DT, gMaze);
	}
	if (gRat.gSpinLeft || IsKeyPressed(KEY_LEFT))
	{
		gRat.SpinLeft(DT);
	}
	if (gRat.gSpinRight || IsKeyPressed(KEY_RIGHT))
	{
		gRat.SpinRight(DT);
	}
	if (IsKeyPressed('r')) {
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed('p')) {
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed('t')) {
		current_view = top_view;
		SetTopView(screen_x, screen_y);
	}

	glColor3d(0, 0, 1);
	gMaze.Draw();
	gRat.Draw();


	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27: // escape character means to quit the program
		exit(0);
		break;
	case 'b':
		// do something when 'b' character is hit.
		break;
	case 'r':
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 'p':
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 't':
		current_view = top_view;
		SetTopView(screen_x, screen_y);
		break;

	default:
		return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	if (current_view == top_view)
	{
		SetTopView(w, h);
	}
	else if (current_view == perspective_view)
	{
		SetPerspectiveView(w, h);
	}
	else
	{
		SetPerspectiveView(w, h);
	}
	// Set the projection mode to 2D orthographic, and set the world coordinates:
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-.5, M + .5, -.5, N + 0.5);
	glMatrixMode(GL_MODELVIEW);*/

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gRat.gSpinLeft = true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		gRat.gSpinLeft = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gRat.gSpinRight = true;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		gRat.gSpinRight = false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		gRat.gMoveForward = true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		gRat.gMoveForward = false;
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	gMaze.mCells[0][0].l = false;
	gMaze.mCells[M - 1][N - 1].r = false;
	gRat.Init(.5, .5, 90);
	InitKeyboard();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow("3d Maze");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0, 0, 0); // foreground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}