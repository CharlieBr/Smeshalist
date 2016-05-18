#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#define MOUSE_PRECISION 100.0
#define PI_2 1.57

#include "LinuxServer.h"

float deltaAngleX = 0.8f;
float deltaAngleY = 0.8f;

float oldMousePositionX, oldMousePositionY;
float radius=5.0f;

Data* d;

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void drawOrigin() {
    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex3f(-2, 0, 0);
        glColor3f(1, 0, 0);
        glVertex3f( 2, 0, 0);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex3f(0, -2, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0,  2, 0);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex3f(0, 0, -2);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0,  2);
    glEnd();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(cos(deltaAngleY)*cos(deltaAngleX)*radius, sin(deltaAngleY)*radius, cos(deltaAngleY)*sin(deltaAngleX)*radius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
        drawOrigin();
        glColor3f(0.1f, 0.1f, 0.1f);
        d -> draw_elements();
    glPopMatrix();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    if (key == 27)
        exit(0);
}

void mouseMove(int x, int y) {
    deltaAngleX += (x-oldMousePositionX) / MOUSE_PRECISION;
    deltaAngleY += (y-oldMousePositionY) / MOUSE_PRECISION;

    if (deltaAngleY > PI_2) {
        deltaAngleY = PI_2;
    } else if (deltaAngleY < -PI_2) {
        deltaAngleY = -PI_2;
    }

    oldMousePositionX=x;
    oldMousePositionY=y;
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
            oldMousePositionX = x;
            oldMousePositionY = y;
		}
	}

	if (button == 3){
        if (radius > 1){
            radius--;
        }
	} else if (button == 4){
        radius++;
	}

}
int main(int argc, char **argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    d = &Data::get_instance();

    AbstractServer* server = new LinuxServer();
    server -> registerStructuresHandler(d);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Smeshalist v0.0.1");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

	server -> startServer();
	glutMainLoop();
	server -> stopServer();

	return 1;
}
