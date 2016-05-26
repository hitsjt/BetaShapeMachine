/*
Szymon Rusinkiewicz
Princeton University

mesh_view.cc
Simple viewer
*/

// use this code only in windows
#ifdef _MSC_VER
#include "Vec.hpp"
#include "XForm.hpp"
#include "GLCamera.hpp"
#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "Color.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <boost/timer.hpp>
#include "../Plugins/DL13/DL13_ShapeGenModel.hpp"
using namespace std;


// Globals
vector< point > points;

bool accept_result;

xform global_xf;
GLCamera camera;

int current_mesh = -1;

bool draw_edges = false;
bool draw_points = false;
bool draw_2side = false;
bool draw_shiny = true;
bool draw_lit = true;
bool draw_falsecolor = false;
bool draw_index = false;
bool white_bg = false;
bool grab_only = false;
int point_size = 10, line_width = 1;

struct GlobalSphere
{
	point center;
	float r;
};

GlobalSphere global_bsph;


// Signal a redraw
void need_redraw()
{
	glutPostRedisplay();
}


// Clear the screen
void cls()
{
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	if (white_bg)
		glClearColor(1, 1, 1, 0);
	else
		glClearColor(0.08f, 0.08f, 0.08f, 0);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// Set up lights and materials
void setup_lighting()
{
	Color c(1.0f);
	if (draw_falsecolor)
		c = Color::hsv(-3.88f, 0.6f + 0.2f * sin(0.42f), 1);
	glColor3fv(c);

	if (!draw_lit) {
		glDisable(GL_LIGHTING);
		return;
	}

	GLfloat mat_specular[4] = { 0.18f, 0.18f, 0.18f, 0.18f };
	if (!draw_shiny) {
		mat_specular[0] = mat_specular[1] =
		mat_specular[2] = mat_specular[3] = 0.0f;
	}
	GLfloat mat_shininess[] = { 64 };
	GLfloat global_ambient[] = { 0.02f, 0.02f, 0.05f, 0.05f };
	GLfloat light0_ambient[] = { 0.5f, 0.5f, 0.5f, 0 };
	GLfloat light0_diffuse[] = { 0.85f, 0.85f, 0.8f, 0.85f };
	GLfloat light1_diffuse[] = { -0.01f, -0.01f, -0.03f, -0.03f };
	GLfloat light0_specular[] = { 0.85f, 0.85f, 0.85f, 0.85f };
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, draw_2side);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
}


// Draw the mesh
void draw_mesh()
{
	if ( points.empty() )
		return;

	glPushMatrix();

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	//// Vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT,
			sizeof(points[0]),
			&points[0][0]);

	// Main drawing pass
	glPointSize(float(point_size));
	glDrawArrays(GL_POINTS, 0, points.size());
	glPopMatrix();
}


// Draw the scene
void redraw()
{
	camera.setupGL(global_xf * global_bsph.center, global_bsph.r);
	glPushMatrix();
	glMultMatrixd(global_xf);
	cls();
	setup_lighting();
	draw_mesh();

	glPopMatrix();
	glutSwapBuffers();
	if (grab_only) {
		void dump_image();
		dump_image();
		glutLeaveMainLoop();
	}
	fflush(stdout);
}


// Set the view...
void resetview()
{
	camera.stopspin();

	// Set camera to first ".camxf" if we have it...
	if ( !global_xf.read("cam.tmp"))
		global_xf = xform::trans(0, 0, -5.0f * global_bsph.r) *
			xform::trans(-global_bsph.center);
}


// Save the current image to a PPM file.
// Uses the next available filename matching filenamepattern
void dump_image()
{
	// Find first non-used filename
	const char filenamepattern[] = "img%d.ppm";
	int imgnum = 0;
	FILE *f;
	while (1) {
		char filename[1024];
		sprintf(filename, filenamepattern, imgnum++);
		f = fopen(filename, "rb");
		if (!f) {
			f = fopen(filename, "wb");
			printf("\n\nSaving image %s... ", filename);
			fflush(stdout);
			break;
		}
		fclose(f);
	}

	// Read pixels
	GLint V[4];
	glGetIntegerv(GL_VIEWPORT, V);
	GLint width = V[2], height = V[3];
	char *buf = new char[width*height*3];
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(V[0], V[1], width, height, GL_RGB, GL_UNSIGNED_BYTE, buf);

	// Flip top-to-bottom
	for (int i = 0; i < height/2; i++) {
		char *row1 = buf + 3 * width * i;
		char *row2 = buf + 3 * width * (height - 1 - i);
		for (int j = 0; j < 3 * width; j++)
			swap(row1[j], row2[j]);
	}

	// Write out file
	fprintf(f, "P6\n#\n%d %d\n255\n", width, height);
	fwrite(buf, width*height*3, 1, f);
	fclose(f);
	delete [] buf;

	printf("Done.\n\n");
}


// Save camera xform
void save_cam_xform()
{
	std::string camfile = "cam.tmp";
	printf("Writing %s\n", camfile.c_str());
	global_xf.write(camfile);
}



// Handle mouse button and motion events
static unsigned buttonstate = 0;

void doubleclick(int button, int x, int y)
{
	// Render and read back ID reference image
	camera.setupGL( global_bsph.center, global_bsph.r );
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	draw_index = true;
	glPushMatrix();
	glMultMatrixd(global_xf);
	draw_mesh();
	glPopMatrix();
	draw_index = false;
	GLint V[4];
	glGetIntegerv(GL_VIEWPORT, V);
	y = int(V[1] + V[3]) - 1 - y;
	unsigned char pix[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pix);
	int n = (pix[0] << 16) + (pix[1] << 8) + pix[2];
}

void mousehelperfunc(int x, int y)
{
	static const Mouse::button physical_to_logical_map[] = {
		Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
		Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
	};

	Mouse::button b = Mouse::NONE;
	if (buttonstate & (1 << 3))
		b = Mouse::WHEELUP;
	else if (buttonstate & (1 << 4))
		b = Mouse::WHEELDOWN;
	else if (buttonstate & (1 << 30))
		b = Mouse::LIGHT;
	else
		b = physical_to_logical_map[buttonstate & 7];

	camera.mouse(x, y, b,
		global_xf * global_bsph.center, global_bsph.r,
		global_xf);
}

void mousemotionfunc(int x, int y)
{
	mousehelperfunc(x,y);
	if (buttonstate)
		need_redraw();
}

void mousebuttonfunc(int button, int state, int x, int y)
{
	static timestamp last_click_time;
	static unsigned last_click_buttonstate = 0;
	static float doubleclick_threshold = 0.4f;

	if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
		buttonstate |= (1 << 30);
	else
		buttonstate &= ~(1 << 30);

	if (state == GLUT_DOWN) {
		buttonstate |= (1 << button);
		if (buttonstate == last_click_buttonstate &&
		    now() - last_click_time < doubleclick_threshold) {
			doubleclick(button, x, y);
			last_click_buttonstate = 0;
		} else {
			last_click_time = now();
			last_click_buttonstate = buttonstate;
		}
	} else {
		buttonstate &= ~(1 << button);
	}

	mousehelperfunc(x, y);
	if (buttonstate & ((1 << 3) | (1 << 4))) // Wheel
		need_redraw();
	if ((buttonstate & 7) && (buttonstate & (1 << 30))) // Light
		need_redraw();
}


// Idle callback
void idle()
{
	xform tmp_xf = global_xf;

	if (camera.autospin(tmp_xf))
		need_redraw();
	else
		usleep(10000);

		global_xf = tmp_xf;
}


// Keyboard
#define Ctrl (1-'a')
void keyboardfunc(unsigned char key, int, int)
{
	switch (key) {
		case ' ':
			resetview();
			break;
		case '@': // Shift-2
			draw_2side = !draw_2side; break;
		case 'e':
			draw_edges = !draw_edges; break;
		case 'f':
			draw_falsecolor = !draw_falsecolor; break;
		case 'l':
			draw_lit = !draw_lit; break;
		case 'p':
			point_size++; break;
		case 'P':
			point_size = max(1, point_size - 1); break;
		case Ctrl+'p':
			draw_points = !draw_points; break;
		case 's':
			draw_shiny = !draw_shiny; break;
		case 't':
			line_width++; break;
		case 'T':
			line_width = max(1, line_width - 1); break;
		case 'w':
			white_bg = !white_bg; break;
		case 'I':
			dump_image(); break;
		case 'c':
			save_cam_xform();
			break;
    case '`':
    case '~':
      accept_result = false;
      glutLeaveMainLoop();
		case '\033': // Esc
		case Ctrl+'q':
		case 'Q':
		case 'q':
			glutLeaveMainLoop();
		default:
			if (key >= '1' && key <= '9') {
				int m = key - '1';
			}
	}
	need_redraw();
}


int render(vector< SNL::DL13::Point > _points)
{
  accept_result = true;
	points.clear();
	points.reserve( _points.size() );
	for (size_t i = 0; i < _points.size(); i++)
		points.push_back( _points[i].p );
	glutInitWindowSize(1280, 1024);
	glutInitWindowPosition(1, 1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	char *myargv [1];
	int myargc=1;
	myargv [0]=strdup ("render point cloud");
	glutInit(&myargc, myargv);

	glutCreateWindow(myargv[0]);
	glutDisplayFunc(redraw);
	glutMouseFunc(mousebuttonfunc);
	glutMotionFunc(mousemotionfunc);
	glutKeyboardFunc(keyboardfunc);
	glutIdleFunc(idle);

	global_bsph.center  = point(0.0f, 0.0f, 0.0f);
	global_bsph.r  = 0.0f;
	for (size_t i = 0; i < points.size(); i++)
	{
		global_bsph.center += points[i];
	}
	global_bsph.center /= (1e-30f + float(points.size()));

	global_bsph.r = 0.0f;
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] -= global_bsph.center;
		global_bsph.r = max( global_bsph.r, len(points[i]) );
	}

	resetview();
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();

	return 0;
}


#endif
