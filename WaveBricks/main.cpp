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
#include "al.h"
#include "alc.h"
#include "alut.h"
#else
#include <GL/glut.h>
#include <synths.h>
#include "GL/glui.h"
#include "al.h"
#include "alc.h"
#include "alut.h"
#endif
#include <cmath>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "file.cpp"
#include <winioctl.h>
#include <unistd.h>
#include <fcntl.h> //open
<<<<<<< HEAD
#include <map>
#include <string>
=======

>>>>>>> origin/master

#include <stdio.h>

#include "entities.h"
#include "synths.h"

#include "synths.cpp"
#include "entities.cpp"
using namespace std;


//static ALuint audios[];
static ALuint soundstream;
static ALuint notestream;

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


bool left;
bool right;
float mX,mY;
static void updateMouse(int x, int y){
    bool right=0;
    bool left=0;
    mX=x, mY=y;
    if((GetKeyState(VK_LBUTTON))){
        left=true;
    }
    if((GetKeyState(VK_RBUTTON))){
        right=true;
    }
}

bool selector;//
string activeWind;//
bool play;//
float seek;//
float tempo;//

static void key(unsigned char key, int x, int y)
{
    //TODO: refer switches of mouse to trigger and change value from here.
    selector=false;
    if(bool left=1){
        selector=true;
    }
    if(bool right=1){
       //right click
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
<<<<<<< HEAD
std::vector<instrument> instruments;

void render()
{
    for (auto instr : instruments) instr.render();
}
void displayMain(void)
{
    const double timeScale = glutGet(GLUT_ELAPSED_TIME) / 420.00;
    const double a = timeScale*90.0;

}
=======
>>>>>>> origin/master
static void WBInit(int argc,char **argv, int argac,char **argav){
    //int argc;char **argv;
    //int argac;char **argav;
    glutInit(&argc, argv);
    alutInit(&argac, argav);
<<<<<<< HEAD
=======
    glutInitWindowSize(1080, 960);
    glutInitWindowPosition(10,10);
>>>>>>> origin/master
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


    glutReshapeFunc(resize);
    glutDisplayFunc(displayMain);
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

<<<<<<< HEAD
    glutInitWindowSize(1080,900);
    glutInitWindowPosition(10,10);
    glutCreateWindow("WaveBricks Main Window");
    glutDisplayFunc(render);
}

void displayBoard(void)
{
    const double timeScale = glutGet(GLUT_ELAPSED_TIME) / 420.00;
    const double a = timeScale*90.0;

}
void initMainBoard(void){

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(700, 320);
    glutInitWindowPosition(10,10);
    glutCreateWindow("WaveBricks Manager");

    glutReshapeFunc(resize);
    glutDisplayFunc(displayBoard);
    glutIdleFunc(idle);
=======
    glutInitWindowSize(700, 1080);
    glutInitWindowPosition(10,10);
    glutCreateWindow("WaveBricks Main Window");
}


void initMainBoard(void){
    glutInitWindowSize(1080, 960);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("WaveBricks Manager");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
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

    glutInitWindowSize(700, 320);
    glutInitWindowPosition(10,10);
    glutCreateWindow("WaveBricks Instrument Manager");
>>>>>>> origin/master
}

int winSelect=0;
static void addInst(int argc, char *argv[], int indexInst){
    //glutInit(&argc, argv);
    //alutInit(&argc, argv);
    glutInitWindowSize(400, 960);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("WaveBricks Instrument " + char(indexInst));

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
}
/* Program entry point */
int instCount = 0;
char wnd_title[256];
bool recording = false;
bool stop = false;

ALuint songbuffer;

string winTit;


GLUI *glui;
GLUI_Rollout		*object_rollout;
GLUI_RadioGroup		*object_type_radio;
GLUI_Rotation		*object_rotation;
GLUI_Translation	*object_xz_trans;
GLUI_Translation	*object_y_trans;

GLUI_Rollout		*anim_rollout;
GLUI_Button			*action_button;

GLUI_Checkbox *draw_floor_check;
GLUI_Checkbox *draw_object_check;

// This  checkbox utilizes the callback
GLUI_Checkbox *use_depth_buffer;
void updateUI(){
    HWND hwnd=GetForegroundWindow();
    for (int i =0; i<=instCount; i++){
        winTit = GetWindowText(hwnd,wnd_title,sizeof(wnd_title));
        if("Wavebricks Instrument " + i==winTit){
            winSelect=i;
        }
        winTit="";
    }
}
std::vector<synthpanel> sounds;
int main(int argc, char **argv)
{
    cout << "           WaveBricks v 1.0\n      copyright 2018 Noah King(wittymoniker.com)\nmain console window. begin init gl:";
    WBInit(NULL,NULL,NULL,NULL);
<<<<<<< HEAD
    initMainBoard();///////////sldjadajsdjjsdaldjsjddjlwdjljw;
    cout << "done.\nbegin init loop.";
    glutMainLoop();

    /*while (!stop){
=======
    initMainBoard();
    cout << "done.\nbegin init loop.";


    while (!stop){
>>>>>>> origin/master
        //HWND hwnd=GetForegroundWindow();
        //void glutPassiveMotionFunc(void *updateMouse);
        for(int i=0; i <=instCount;i++){
            instruments[i].tick();
        }
        for (int i=0; i<=instCount;i++){
            instruments[i].render();
            //glutMainLoopEvent();
        }
<<<<<<< HEAD
    }*/
=======
    }
>>>>>>> origin/master
    return EXIT_SUCCESS;
}
