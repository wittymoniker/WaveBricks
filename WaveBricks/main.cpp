/*
WEED OP ENGINE - WEED GROWING VIDEO GAME

TODO:
    SOUND PLAYER, CUSTOM SOUNDS
    MODELS, WAVEFRONTS IMAGES, SOUNDS
    TEXTURING EXAMPLE
    PERSPECTIVE MOVING, CAMERA FUNCTION
    CLASS FOR UI HANDLER, UI LOOP W MULTITHREAD
    CLASS FOR ENTITIES
    CLASS FOR CHARACTER INPUTS
    CONSOLIDATE TICK / RENDER TO CALL UPDATES FOR EACH CLASS AND THEN RENDER TO PACKED ENVIRONMENT DATA
    PARSE JUNK FUNCTIONS / FIND OUT WHAT IN HERE IS NEEDED (GLUT MAIN LOOP SHOULD WORK WITH A SUBSEQUENT AND SEPARATE TICK PROCESS?)
    GAME DESCRIPTION HERE


OPENAL DOWNLOAD : http://www.openal.org/downloads/ may be useful plz find audio lib
USING INTEGRATED FREEGLUT
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
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
using namespace std;


using namespace std;

#define TYPE char
#define RATE 44100 //sampling rate
#define SIZE sizeof(TYPE) //size of sample, in bytes
#define CHANNELS 1 //number of stereo channels
#define PI 3.14159
#define SAMPLE_MAX (pow(2,SIZE*8 - 1) - 1)

void writeToSoundDevice(TYPE* buf, int deviceID, int buffSize) {
  int status;
  status = write(deviceID, buf, buffSize);
  if (status != buffSize)
    perror("Wrote wrong number of bytes\n");
  status = ioctl(deviceID, SOUND_PCM_SYNC, 0);
  if (status == -1)
    perror("SOUND_PCM_SYNC failed\n");
}

int main(int argc, char* argv[])
{
  int deviceID, arg, status, i, numSamples;
  numSamples = atoi(argv[1]);

  TYPE* samples = (TYPE *) malloc((size_t) numSamples * sizeof(TYPE)* CHANNELS);
  FILE *inFile = fopen(argv[2], "rb");
  fread(samples, (size_t)sizeof(TYPE), numSamples*CHANNELS, inFile);
  fclose(inFile);

  deviceID = open("/dev/dsp", O_WRONLY, 0);
  if (deviceID < 0)
    perror("Opening /dev/dsp failed\n");
  arg = SIZE * 8;
  status = ioctl(deviceID, SOUND_PCM_WRITE_BITS, &arg);
  if (status == -1)
    perror("Unable to set sample size\n");
  arg = CHANNELS;
  status = ioctl(deviceID, SOUND_PCM_WRITE_CHANNELS, &arg);
  if (status == -1)
    perror("Unable to set number of channels\n");
  arg = RATE;
  status = ioctl(deviceID, SOUND_PCM_WRITE_RATE, &arg);
  if (status == -1)
    perror("Unable to set number of bits\n");

  writeToSoundDevice(samples, deviceID, numSamples * CHANNELS);
  FILE *outFile = fopen(argv[3], "wb");
  fwrite(samples, 1, numSamples*CHANNELS, outFile);
  fclose(outFile);
  close(deviceID);
}

P

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
