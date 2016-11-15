#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/glut.h>

#define MOUSE_PRECISION 100.0
#define MOVING_PRECISION 400.0
#define PI_2 1.57

#include "XML_PARSER/include/UserPreferencesManager.h"
#ifdef __linux__
#include "LinuxServer.h"
#include "LinuxDataTree.h"
#else
#include "WindowsServer.h"
#include "WindowsDataTree.h"
#endif // __linux__

char SMESHALIST[] = "Smeshalist v1.0";

float deltaAngleX = 0.8f;
float deltaAngleY = 0.8f;

float oldMousePositionX, oldMousePositionY;
float radius=5.0f;
float mouseSensitivity = 1.0f;

float translationX=0, translationY=0;

float cameraX=0, cameraY=0, cameraZ=0;
float cameraLookAtX=0, cameraLookAtY=0, cameraLookAtZ=0;

bool isShiftPressed = false;
bool isLeftMouseButtonPressed = false;

AbstractDataTree* d = NULL;
AbstractServer* server = NULL;

Color backgroundColor(0,0,0);

void computeCameraPosition() {
    cameraX = cos(deltaAngleY)*cos(deltaAngleX)*radius + cameraLookAtX;
    cameraY = sin(deltaAngleY)*radius + cameraLookAtY;
    cameraZ = cos(deltaAngleY)*sin(deltaAngleX)*radius + cameraLookAtZ;
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

void drawBoundingBox(AbstractDataTree* d) {
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

	glClearColor(backgroundColor.r(), backgroundColor.g(), backgroundColor.b(), 1);
    glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
        drawOrigin();
        glColor3f(0.1f, 0.1f, 0.1f);

        d -> getCurrentlyVisibleDataTree() -> draw_elements();
        drawBoundingBox(d -> getCurrentlyVisibleDataTree());

        CoordinatesFilter::getInstance() -> draw();
    glPopMatrix();

    glutSwapBuffers();
}

void mouseMove(int x, int y) {
    if (!isLeftMouseButtonPressed) {
        return;
    }

    if (isShiftPressed) {
        translationX = mouseSensitivity * (x-oldMousePositionX) * radius / MOVING_PRECISION;
        translationY = mouseSensitivity * (oldMousePositionY-y) * radius / MOVING_PRECISION;

        cameraLookAtX += translationX * cos(deltaAngleX+PI_2);
        cameraLookAtY -= translationY * cos(deltaAngleY);
        cameraLookAtZ += translationX * sin(deltaAngleX+PI_2);
    } else {
        deltaAngleX += mouseSensitivity * (x-oldMousePositionX) / MOUSE_PRECISION;
        deltaAngleY += mouseSensitivity * (y-oldMousePositionY) / MOUSE_PRECISION;

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
            cameraLookAtX = 0;
            cameraLookAtY = 0;
            cameraLookAtZ = 0;
        }
	}

    isShiftPressed = glutGetModifiers() == GLUT_ACTIVE_SHIFT;

	if (button == 3){
        radius*=std::pow(0.9, mouseSensitivity);
	} else if (button == 4){
        radius/=std::pow(0.9, mouseSensitivity);
	}

    computeCameraPosition();
}

void setTitle() {
    char title[80];
    strcpy(title, SMESHALIST);

    if (AbstractDataTree::getVisibleDataTreeIndex() == -1) {
        strcat(title, "\tACTIVE");
    } else {
        strcat(title, "\tPREVIOUS: ");
        strcat(title, to_string(AbstractDataTree::getVisibleDataTreeIndex()+1).c_str());
    }

    glutSetWindowTitle(title);
}

void keyboardEventSpec(int key, int x, int y) {
    int visibleTreeIndex = AbstractDataTree::getVisibleDataTreeIndex();

    switch(key) {
        case GLUT_KEY_LEFT:
            AbstractDataTree::decreaseVisibleDataTreeIndex();
            break;
        case GLUT_KEY_RIGHT:
            AbstractDataTree::increaseVisibleDataTreeIndex();
            break;
    }

    //recompute only when data tree changed
    if (visibleTreeIndex != AbstractDataTree::getVisibleDataTreeIndex()) {
        switch(key) {
            case GLUT_KEY_LEFT:
            case GLUT_KEY_RIGHT:
                setTitle();
                Statistics stats = d->getCurrentlyVisibleDataTree()->get_statistics();
                CoordinatesFilter::getInstance() -> recomputeIntersections(&stats);
                server -> sendStatisticsOfCurrentlyVisibleTree();
                break;
        }
    }
}

void keyboardEvent(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
            deltaAngleX=M_PI;
            deltaAngleY=0;
            computeCameraPosition();
            break;
        case 'y':
            deltaAngleX=0;
            deltaAngleY=M_PI_2;
            computeCameraPosition();
            break;
        case 'z':
            deltaAngleX=M_PI_2;
            deltaAngleY=0;
            computeCameraPosition();
            break;
    }
}

void initGLUT(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	setTitle();

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);

	glutMouseFunc(mouseButton);
	glutKeyboardFunc(keyboardEvent);
	glutSpecialFunc(keyboardEventSpec);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

inline bool isFileExists(const char* name) {
    if (FILE *file = fopen(name, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void tryToRunSmeshalistManager(int argc, char** argv) {
    char* p = NULL;
    for (int i=1; i<argc && p==NULL; i++) {
        p = strstr(argv[i], "SM=");
    }

    string path;
    if (p != NULL) {
        path = string(p + 3, p+strlen(p));
    } else {
        path = "lib/SmeshalistManager.jar";
    }


    if (isFileExists(path.c_str())) {
        path = "java -jar " + path;
		#ifdef __linux__			//diffrent options to run process in background
		path = path + " &";
		#else
		path = "start " + path;
		#endif
        system(path.c_str());
    } else {
        cerr << "Unable to run Smeshalist Manager!!!\n";
    }
}

void redirectOutput() {
    /*time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    char *time = asctime (timeinfo);
    char* fileName = new char[20];
    memcpy(fileName, &time[4], 16);
    fileName[15] = '\0';
    strcat(fileName, ".log");*/

    freopen("info.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
}

int main(int argc, char **argv) {
    redirectOutput();
    tryToRunSmeshalistManager(argc, argv);
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    //set initial position
	computeCameraPosition();

    #ifdef __linux__
    server = new LinuxServer();
	d = LinuxDataTree::getActiveDataTree();
    #else
	server = new WindowsServer();
	d = WindowsDataTree::getCurrent();
    #endif // __linux__

    server -> registerStructuresHandler(d);
    server -> registerMouseSensitivityHandler(&mouseSensitivity);

    backgroundColor = UserPreferencesManager::getInstance()->getBackgroudColor();

	initGLUT(argc, argv);

	server -> startServer();
	glutMainLoop();
	server -> stopServer();

	return 0;
}
