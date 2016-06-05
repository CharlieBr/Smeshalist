#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#define MOUSE_PRECISION 100.0
#define MOVING_PRECISION 200.0
#define PI_2 1.57

#include "LinuxServer.h"
#include "FILTERS_MODULE/include/GroupsFilter.h"

float deltaAngleX = 0.8f;
float deltaAngleY = 0.8f;

float oldMousePositionX, oldMousePositionY;
float radius=5.0f;

float translationX=0, translationY=0;

float cameraX=0, cameraY=0, cameraZ=0;

bool isShiftPressed = false;
bool isLeftMouseButtonPressed = false;

Data* d;

void computeCameraPosition() {
    cameraX = cos(deltaAngleY)*cos(deltaAngleX)*radius;
    cameraY = sin(deltaAngleY)*radius;
    cameraZ = cos(deltaAngleY)*sin(deltaAngleX)*radius;
}

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
    glTranslatef(translationX, translationY, 0);
	gluLookAt(cameraX, cameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

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
    if (key == 97) {
        SingleGroupFilter* filter = new SingleGroupFilter(0);
        GroupsFilter::getInstance() -> deleteAllFilters();
        GroupsFilter::getInstance() -> addSimpleGroupFilter(filter);
    } else if (key == 115) {
        SingleGroupFilter* filter = new SingleGroupFilter(1);
        GroupsFilter::getInstance() -> deleteAllFilters();
        GroupsFilter::getInstance() -> addSimpleGroupFilter(filter);
    }
}

void mouseMove(int x, int y) {
    if (!isLeftMouseButtonPressed) {
        return;
    }

    if (isShiftPressed) {
        translationX += (x-oldMousePositionX) * radius / MOVING_PRECISION;
        translationY -= (y-oldMousePositionY) * radius / MOVING_PRECISION;
    } else {
        deltaAngleX += (x-oldMousePositionX) / MOUSE_PRECISION;
        deltaAngleY += (y-oldMousePositionY) / MOUSE_PRECISION;

        if (deltaAngleY > PI_2) {
            deltaAngleY = PI_2;
        } else if (deltaAngleY < -PI_2) {
            deltaAngleY = -PI_2;
        }
    }

    oldMousePositionX=x;
    oldMousePositionY=y;

    computeCameraPosition();
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
        isLeftMouseButtonPressed = state==GLUT_DOWN;
		if (state == GLUT_DOWN) {
            oldMousePositionX = x;
            oldMousePositionY = y;
		}
	} else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            translationX = 0;
            translationY = 0;
            GroupsFilter::getInstance() -> filterTree(d);
        }
	}

    isShiftPressed = glutGetModifiers() == GLUT_ACTIVE_SHIFT;

	if (button == 3){
        radius*=0.9;
	} else if (button == 4){
        radius/=0.9;
	}

    computeCameraPosition();
}

int main(int argc, char **argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    //set initial position
    computeCameraPosition();

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
