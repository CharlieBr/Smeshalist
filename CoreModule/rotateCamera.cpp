#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

#define MOUSE_PRECISION 100.0
#define MOVING_PRECISION 400.0
#define PI_2 1.57

#include "UserPreferencesManager.h"
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
bool switchView = false;

AbstractDataTree* d = NULL;
AbstractServer* server = NULL;

Color backgroundColor = UserPreferencesManager::getInstance()->getBackgroudColor();
Color xAxis = UserPreferencesManager::getInstance()->getXAxisColor();
Color yAxis = UserPreferencesManager::getInstance()->getYAxisColor();
Color zAxis = UserPreferencesManager::getInstance()->getZAxisColor();
Color BLACK(0,0,0);

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {0.0, 1.0, 0.0, 0.0};

float screenRatio = 0;
float screenWidth=0, screenHeight=0;

void computeCameraPosition() {
    cameraX = cos(deltaAngleY)*cos(deltaAngleX)*radius + cameraLookAtX;
    cameraY = sin(deltaAngleY)*radius + cameraLookAtY;
    cameraZ = cos(deltaAngleY)*sin(deltaAngleX)*radius + cameraLookAtZ;
}

void setPerspective() {
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, screenWidth, screenHeight);
    gluPerspective(45.0f, screenRatio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void refreshOrthoSettings() {
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, screenWidth, screenHeight);
    glOrtho(-screenRatio*radius, screenRatio*radius, -radius, radius, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void setOrtho() {
    deltaAngleX = PI_2;
    deltaAngleY = 0;
    computeCameraPosition();
    refreshOrthoSettings();
}

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;

    screenWidth = w;
    screenHeight = h;

	screenRatio =  w * 1.0 / h;

    if (server -> isOrthoViewSet()) {
        refreshOrthoSettings();
    } else {
        setPerspective();
	}
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

void drawLine(  double x0, double y0, double z0,
                double x1, double y1, double z1,
                Color color0, Color color1,
                double transparent) {
    drawLine(x0, y0, z0,
             x1, y1, z1,
             color0.r(), color0.g(), color0.b(),
             color1.r(), color1.g(), color1.b(),
             transparent);
}

void drawOrigin() {
    drawLine(-2,0,0,  2,0,0,  BLACK,  xAxis,  1);
    drawLine(0,-2,0,  0,2,0,  BLACK,  yAxis,  1);

    if (!server -> isOrthoViewSet()) {
        drawLine(0,0,-2,  0,0,2,  BLACK,  zAxis,  1);
        glColor3d(yAxis.r(), yAxis.g(), yAxis.b());
        glRasterPos3d(0,0,2);
        print::printString("Z");
    }

    glColor3d(zAxis.r(), zAxis.g(), zAxis.b());
    glRasterPos3d(2,0,0);
    print::printString("X");

    glColor3d(xAxis.r(), xAxis.g(), xAxis.b());
    glRasterPos3d(0,2,0);
    print::printString("Y");
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

void addDirectionalLight() {
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHT0);

   glMatrixMode(GL_MODELVIEW);
   glEnable(GL_COLOR_MATERIAL);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(backgroundColor.r(), backgroundColor.g(), backgroundColor.b(), 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (switchView) {
        switchView = false;
        if (server -> isOrthoViewSet()) {
            setOrtho();
        } else {
            setPerspective();
        }
    }

	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0.0f, 1.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

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

        cameraLookAtX -= translationX * sin(deltaAngleX) - translationY*sin(deltaAngleY)*cos(deltaAngleX);
        cameraLookAtY -= translationY * cos(deltaAngleY);
        cameraLookAtZ += translationX * cos(deltaAngleX) + translationY*sin(deltaAngleY)*sin(deltaAngleX);
    } else if (!server -> isOrthoViewSet()){
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

    //if (!isOrtho) {
        if (button == 3){
            radius*=std::pow(0.9, mouseSensitivity);
        } else if (button == 4){
            radius/=std::pow(0.9, mouseSensitivity);
        }
	//}
	if (server -> isOrthoViewSet()) {
        refreshOrthoSettings();
	}

    computeCameraPosition();
}

void initGLUT(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow(SMESHALIST);

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    addDirectionalLight();
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
	d = WindowsDataTree::getActiveDataTree();
    #endif // __linux__

    server -> registerStructuresHandler(d);
    server -> registerMouseSensitivityHandler(&mouseSensitivity);

	initGLUT(argc, argv);

	server -> startServer();
	glutMainLoop();
	server -> stopServer();

	return 0;
}

