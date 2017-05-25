/*
WEED OP ENGINE - WEED GROWING VIDEO GAME

TODO:
    BEGIN BUILDING ENGINE, LEARNING ABOUT OUR LIBRARIES:
    -OPENAL
    -SOUNDPlayer
    -ImgStream(useless now?):
    -AviFile
    -entities.cpp needs work - will house our synth functions which controls shapes and sounds, and interconnects them generally
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#include "GLUI/glui.h"
#else
#include <GL/glut.h>
#include "GL/glui.h"
#endif
#include <cmath>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include "entities.cpp"
#include "file.cpp"
#include <winioctl.h>
#include <unistd.h>
#include <fcntl.h> //open
#include <soundcard.h>
#include <stdio.h>
#include "al.h"
#include "alc.h"
using namespace std;


using namespace std;

#ifdef LIBAUDIO
#include <audio/wave.h>
#define BACKEND	"libaudio"
#else
#include "alut.h"
#define BACKEND "alut"
#endif

static void list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}

#define TEST_ERROR(_msg)		\
	error = alGetError();		\
	if (error != AL_NO_ERROR) {	\
		fprintf(stderr, _msg "\n");	\
		return -1;		\
	}


static inline ALenum to_al_format(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

bool left;
bool right;
static void updateMouse(){
    bool right=0;
    bool left=0;
    if((GetKeyState(VK_LBUTTON))){
        left=true;
    }
    if((GetKeyState(VK_RBUTTON))){
        right=true;
    }
}

float charPos;//
bool selector;//
string activeWind;//
bool play;//
float seek;//
float tempo;//
static void key(unsigned char key, int x, int y)
{
    //TODO: refer switches of mouse to trigger and change value from here.
    switch (key)
    {
        case 27 :
        case 'f':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '_':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }
    updateMouse();
    selector=false;
    if(bool left=1){
        selector=true;
    }
    if(bool right=1){
       //right click
    }

}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
void display(void)
{
    const double timeScale = glutGet(GLUT_ELAPSED_TIME) / 420.00;
    const double a = timeScale*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    //character values can be stacked in between push and pulls with variables. once we get a general environment and character tracking we'll be set.
    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}
int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(1080, 960);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("WaveBricks");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
