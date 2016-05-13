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

// actual vector representing the camera's direction
float lx=10.0f,ly=10.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f,y=0.0f,z=5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
float deltaMove = 1;
int xOrigin = -1;
int yOrigin = -1;

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

	x = deltaMove * lx * 0.1f;
	y = deltaMove * ly * 0.1f;
	z += deltaMove * lz * 0.1f;
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
	gluLookAt(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 0);
    // use one rotation each for x and y object rotation
    glRotatef(x, 0, 1, 0);
    glRotatef(y, 1, 0, 0);

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
    lx = x;
    ly = y;
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angleX += deltaAngleX;
			angleY += deltaAngleY;
			xOrigin = -1;
			yOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}


	//scroll up
	if (button == 3){

        //when the button is pressed
        if (state == GLUT_DOWN){
            if (deltaMove == 0.0f){
                deltaMove = 0.05f;
            }else{
                deltaMove = 0.0f;
            }

        }
	}
	//scroll down
	if (button == 4){

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
void wheelFunc(int wheel, int direction, int x, int y){

    if(direction == -1){
        deltaMove = -0.05f;
    }
    else if (direction == 1){
        deltaMove = 0.05f;
    }

}
int main(int argc, char **argv) {
    d = &Data::get_instance();
    vector<Point3D> points;

    Point3D point(1.2, 3.4, 1.4);
    points.push_back(point);

    Vertex vertex(&points, 0);
    d->add(0, &vertex);
    d->draw_elements();

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
	//glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	//mouse wheel function
//	glutMouseWheelFunc(wheelFunc);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	server -> startServer();
	glutMainLoop();
	server -> stopServer();

	return 1;
}
