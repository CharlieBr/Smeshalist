#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#define MOUSE_PRECISION 100.0
#define MOVING_PRECISION 200.0
#define PI_2 1.57

#ifdef __linux__
#include "LinuxServer.h"
#include "LinuxDataTree.h"
#else
#include "WindowsServer.h"
#include "WindowsDataTree.h"
#endif // __linux__

float deltaAngleX = 0.8f;
float deltaAngleY = 0.8f;

float oldMousePositionX, oldMousePositionY;
float radius=5.0f;

float translationX=0, translationY=0;

float cameraX=0, cameraY=0, cameraZ=0;

bool isShiftPressed = false;
bool isLeftMouseButtonPressed = false;

AbstractDataTree* d;

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

void drawLine(  double x0, double y0, double z0,
                double x1, double y1, double z1,
                double r0, double g0, double b0,
                double r1, double g1, double b1,
                double transparent) {
    glBegin(GL_LINES);
        glColor4d(r0, g0, b0, transparent);
        glVertex3d(x0, y0, z0);
        glColor4d(r1, g1, b1, transparent);
        glVertex3d(x1, y1, z1);
    glEnd();
}

void drawOrigin() {
    drawLine(-2,0,0,  2,0,0,  0,0,0,  1,0,0,  1);
    drawLine(0,-2,0,  0,2,0,  0,0,0,  0,1,0,  1);
    drawLine(0,0,-2,  0,0,2,  0,0,0,  0,0,1,  1);
}

void drawBoundingBox() {
    drawLine(d->get_max_x(),d->get_max_y(),d->get_max_z(),  d->get_max_x(),d->get_max_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_max_x(),d->get_min_y(),d->get_max_z(),  d->get_max_x(),d->get_min_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_min_x(),d->get_max_y(),d->get_max_z(),  d->get_min_x(),d->get_max_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_min_x(),d->get_min_y(),d->get_max_z(),  d->get_min_x(),d->get_min_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);

    drawLine(d->get_max_x(),d->get_max_y(),d->get_max_z(),  d->get_max_x(),d->get_min_y(),d->get_max_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_max_x(),d->get_max_y(),d->get_min_z(),  d->get_max_x(),d->get_min_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_min_x(),d->get_max_y(),d->get_max_z(),  d->get_min_x(),d->get_min_y(),d->get_max_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_min_x(),d->get_max_y(),d->get_min_z(),  d->get_min_x(),d->get_min_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);

    drawLine(d->get_max_x(),d->get_max_y(),d->get_max_z(),  d->get_min_x(),d->get_max_y(),d->get_max_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_max_x(),d->get_max_y(),d->get_min_z(),  d->get_min_x(),d->get_max_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_max_x(),d->get_min_y(),d->get_max_z(),  d->get_min_x(),d->get_min_y(),d->get_max_z(),  0,0,0,  0,0,0, 0.2);
    drawLine(d->get_max_x(),d->get_min_y(),d->get_min_z(),  d->get_min_x(),d->get_min_y(),d->get_min_z(),  0,0,0,  0,0,0, 0.2);
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
        drawBoundingBox();
        d -> draw_elements();
        CoordinatesFilter::getInstance() -> draw();
    glPopMatrix();

    glutSwapBuffers();
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

void initGLUT(int argc, char **argv) {
    //TODO
    system("java -jar SmeshalistManager/SmeshalistManager.jar &");
    //
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Smeshalist v0.2");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char **argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    //set initial position
	computeCameraPosition();

    AbstractServer* server = NULL;

    #ifdef __linux__
    server = new LinuxServer();
	d = &LinuxDataTree::getInstance();
    #else
	server = new WindowsServer();
	d = &WindowsDataTree::getInstance();
    #endif // __linux__

    server -> registerStructuresHandler(d);

	initGLUT(argc, argv);

	server -> startServer();
	glutMainLoop();
	server -> stopServer();

	return 0;
}
