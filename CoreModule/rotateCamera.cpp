#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include "LinuxServer.h"

// angle of rotation for the camera direction
float angleX = 0.0f;
float angleY = 0.0f;

// XZ position of the camera
float x=2.0f,y=2.0f,z=1.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
float deltaMove = 1;

float oldX, oldY;
float radius=3.0f;

Data* d;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x = deltaMove + deltaAngleX;
	y = deltaMove + deltaAngleY;
	z += deltaMove;
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

	if (deltaMove){
        computePos(deltaMove);
	}

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cos(deltaAngleY)*cos(deltaAngleX)*radius, sin(deltaAngleY)*radius, cos(deltaAngleY)*sin(deltaAngleX)*radius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 0);
    // use one rotation each for x and y object rotation
    /*glRotatef(x, 0, 1, 0);
    glRotatef(y, 1, 0, 0);*/
    //cout << x << "\t" << y << endl;
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

void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.05f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.05f; break;
       }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
}

void mouseMove(int x, int y) {
    // this will only be true when the left button is down
    deltaAngleX += (x-oldX)/100.0;
    deltaAngleY += (y-oldY)/100.0;

    oldX=x;
    oldY=y;
}

void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angleX += deltaAngleX;
			angleY += deltaAngleY;
		} else {
            oldX = x;
            oldY = y;
		}
	}


	//scroll up
	if (button == 3){
        //when the button is pressed
        if (state == GLUT_DOWN){
            if (radius > 1){
                radius--;
            }
            if (deltaMove == 0.0f){
                deltaMove = 0.05f;
            }else{
                deltaMove = 0.0f;
            }

        }
	}
	//scroll down
	if (button == 4){
        radius++;
        //when the button is pressed
        if (state == GLUT_DOWN){
            if (deltaMove == 0.0f){
                deltaMove = -0.05f;
            }else{
                deltaMove = 0.0f;
            }

        }
	}

}
int main(int argc, char **argv) {
    d = &Data::get_instance();

    AbstractServer* server = new LinuxServer();
    server -> registerStructuresHandler(d);

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	server -> startServer();
	glutMainLoop();
	server -> stopServer();

	return 1;
}
