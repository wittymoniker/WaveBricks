#pragma once
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include "GLUI/glui.h"
#include "al.h"
#include "alc.h"
#else
//#pragma comment(lib, "glut32.lib")
//#include <GL/glew.h>

#include<glew.h>
//#include<freeglut.h>
#include<glui.h>

//#include<GL/glu.h>
//#include<GL/freeglut.h>

//#include<GLFW/glfw3.h>
//#include <glm/glm.hpp>

//

#include "al.h"
#include "alc.h"
#include "alext.h"
#include "alut.h"
#endif
#include <cmath>
#include <vector>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <winioctl.h>
#include <fcntl.h> //open

#include<thread>

#include <map>
#include <string>
#include <sstream>

#include <stdio.h>

#include "entities.cpp"
#include<fstream>



//#include "synths.cpp"
//#include "entities.cpp"
using namespace std;


//static ALuint audios[];

std::vector<std::unique_ptr<instrument>> instruments;


static int playbutton = 0;
static int pausebutton = 1;
static int stopbutton = 2;
static int addinstbutton = 3;
static float tracking = 0.0;
static float tempo = 160.0;
static int savebutton = 6;
static int loadbutton = 7;

void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void pmotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void entry(int state);
int window_x = 400;
int window_y = 100;
int window_width = 600;
int window_height = 300;
char* mainboard_title = (char*)"WaveBricks Manager";
int full_screen = 0;
GLUI* mainboard_window;
GLint mainboard_pane;
GLint wavebricks_window;
HDC hdc;



static void list_audio_devices(const ALCchar* devices)
{
	const ALCchar* device = devices, * next = devices + 1;
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
float mX, mY;
void mouse(int button, int state, int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf("GLUT: ");

	switch (button)
	{
		//  Left Button Clicked
	case GLUT_LEFT_BUTTON:

		switch (state)
		{
			//  Pressed
		case GLUT_DOWN:
			printf("Mouse Left Button Pressed (Down)...\n");
			break;
			//  Released
		case GLUT_UP:
			printf("Mouse Left Button Released (Up)...\n");
			break;
		}

		break;

		//  Middle Button clicked
	case GLUT_MIDDLE_BUTTON:

		switch (state)
		{
			//  Pressed
		case GLUT_DOWN:
			printf("Mouse Middle Button Pressed (Down)...\n");
			break;
			//  Released
		case GLUT_UP:
			printf("Mouse Middle Button Released (Up)...\n");
			break;
		}

		break;

		//  Right Button Clicked
	case GLUT_RIGHT_BUTTON:

		switch (state)
		{
			//  Pressed
		case GLUT_DOWN:
			printf("Mouse Right Button Pressed (Down)...\n");
			break;
			//  Released
		case GLUT_UP:
			printf("Mouse Right Button Released (Up)...\n");
			break;
		}

		break;

	}
}

static void updateMouse(int x, int y) {
	bool right = 0;
	bool left = 0;
	mX = x, mY = y;
	if ((GetKeyState(VK_LBUTTON))) {
		left = true;
	}
	if ((GetKeyState(VK_RBUTTON))) {
		right = true;
	}
}
void motion(int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf("GLUT: ");

	//  Print the mouse drag position
	printf("Mouse Drag Position: %d, %d.\n", x, y);
}

void pmotion(int x, int y)
{
	//  Notify that this is a GLUT Callback
	//printf ("GLUT: ");

	//  Print mouse move positopn
	//printf ("Mouse Move Position: %d, %d.\n", x, y);
}


void keyboard(unsigned char key, int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf("GLUT: ");

	//  Print what key the user is hitting
	printf("User is hitting the '%c' key.\n", key);
	printf("ASCII code is %d.\n", key);

	switch (key)
	{
		//  User hits A key
	case 'p':

		break;

		//  User hits Shift + A key
	case 'P':

		break;

		//  User hits Enter
	case 's':
		printf("User is hitting the Return key.\n");
		break;

		//  User hits Space
	case ' ':
		printf("User is hitting the Space key.\n");
		break;

		//  User hits back space
	case 8:
		printf("User is hitting the Back Space key.\n");
		break;
	}

	glutPostRedisplay();
}
void entry(int state)
{
	//  Notify that this is a GLUT Callback
	printf("GLUT: ");

	//  Notify theat we entered the window
	if (state == GLUT_ENTERED)
		printf("Mouse entered GLUT window...\n");
	//  Notify that we left the window
	else if (state == GLUT_LEFT)
		printf("Mouse left GLUT window...\n");
}
static void idle(void)
{
	//glutPostRedisplay ();
}

void centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}
enum
{
	PLAYBUTTON,
	PAUSEBUTTON,
	STOPBUTTON,
	TRACKING_SPINNER,
	TEMPO_SPINNER,
	SAVEBUTTON,
	LOADBUTTON,
	ADDINSTBUTTON
};
std::map<int, instrument> instrumentsmap;
void assembleInst()
{
	instrument *newInst;
	newInst = new instrument;
	instruments.push_back(unique_ptr<instrument>(newInst));
	instruments.at(instruments.size() - 1)->assemble();
	glutDisplayFunc(display);
	GLUI_Master.set_glutIdleFunc(display);
	//instruments[instruments.size()-1].synth_panel->set_main_gfx_window( wavebricks_window );
}

void save() {

}

void load() {
	std::string loadfile = "";
	cout << "\nfilename: ";
	cin >> loadfile;
}





namespace little_endian_io
{
	template <typename Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;


void trackPlay() {
	//tracking =
	ALCdevice* dev = NULL;
	ALCcontext* ctx = NULL;

	const char* defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	std::cout << "Default device: " << defname << std::endl;

	dev = alcOpenDevice(defname);
	ctx = alcCreateContext(dev, NULL);
	alcMakeContextCurrent(ctx);
	for (int i = 0; i < instruments.size(); i++) {
		instruments.at(i)->currentStep = tracking;
		instruments.at(i)->assembleSongData();

	}
	for (int i = 0; i < instruments.size(); i++) {
		
		instruments.at(i)->play();
		
	}

	for (int i = 0; i < instruments.size(); i++ ){
		instruments.at(i)->audioout.open(std::to_string(i)+"audio.wav", std::ios::binary);
		instruments.at(i)->audioout << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
		write_word(instruments.at(i)->audioout, 16, 4);  // no extension data
		write_word(instruments.at(i)->audioout, 1, 2);  // PCM - integer samples
		write_word(instruments.at(i)->audioout, 1, 2);  // two channels (stereo file)
		write_word(instruments.at(i)->audioout, 22050, 4);  // samples per second (Hz)
		write_word(instruments.at(i)->audioout, (22050 * 2), 4);  // (Sample Rate * BitsPerSample * Channels) / 8
		write_word(instruments.at(i)->audioout, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
		write_word(instruments.at(i)->audioout, 16, 2);  // number of bits per sample (use a multiple of 8)
		size_t data_chunk_pos = instruments.at(i)->audioout.tellp();
		instruments.at(i)->audioout << "data----";  // (chunk size to be filled in later)
		instruments.at(i)->it = 0, instruments.at(i)->iu = 0, instruments.at(i)->iy = 0, instruments.at(i)->ii = 0, instruments.at(i)->i = 0, instruments.at(i)->ir = 0;
		for (instruments.at(i)->i = 0; instruments.at(i)->i < instruments.at(i)->sizeSS - 1; instruments.at(i)->i++) {
			write_word(instruments.at(i)->audioout, instruments.at(i)->data.at(instruments.at(i)->i), 2);
			write_word(instruments.at(i)->audioout, instruments.at(i)->data.at(instruments.at(i)->i), 2);
		}

		size_t file_length = instruments.at(i)->audioout.tellp();

		// Fix the data chunk header to contain the data size
		instruments.at(i)-> audioout.seekp(data_chunk_pos + 4);
		write_word(instruments.at(i)->audioout, file_length - data_chunk_pos + 8);

		// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
		instruments.at(i)->audioout.seekp(0 + 4);
		write_word(instruments.at(i)-> audioout, file_length - 8, 4);
		instruments.at(i)->audioout.close();
		instruments.at(i)->it = 0, instruments.at(i)->iu = 0, instruments.at(i)->iy = 0, instruments.at(i)->ii = 0, instruments.at(i)-> i = 0, instruments.at(i)->ir = 0;
	}

	


}
void trackPause() {
	//tracking =
	for (int i = 0; i < instruments.size(); i++) {
		alSourcePause(instruments.at(i)->soundsource);
	}


}
static void mainboard_callback(int control_id)
{
	//  Notify that this is a GLUI Callback
	printf("GLUI: ");

	//  Behave based on control ID
	switch (control_id)
	{
		//  Color Listbox item changed

	case ADDINSTBUTTON:

		printf("Added Instrument to panel.\n");

		assembleInst();

		break;
	case PLAYBUTTON:

		printf("Play.\n");

		trackPlay();

		break;
	case PAUSEBUTTON:

		printf("Pause.\n");

		trackPause();

		break;
	case SAVEBUTTON:

		printf("Save/Export.\n");

		save();

		break;
	case LOADBUTTON:

		printf("Load Song.\n");

		load();

		break;

	}
}

bool selector;//
string activeWind;/////
float seek;//
static void key(unsigned char key, int x, int y)
{
	//TODO: refer switches of mouse to trigger and change value from here.
	selector = false;
	if (bool left = 1) {
		selector = true;
	}
	if (bool right = 1) {
		//right click
	}
	glutPostRedisplay();
}

static void Resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}



const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



ALuint source, buffer;








void display()
{
	//glfwMakeContextCurrent(wavebricks_window);
	glutSetWindow(wavebricks_window);
	glMatrixMode(GL_MODELVIEW);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();//load identity matrix
	glTranslatef(0.0f, 0.0f, -5.0f);

	//glTranslatef(0.0f,0.0f,-7.0f);
	//glTranslatef(1.5f, 0.0f, -7.0f);
	for (int it = 0; it < instruments.size(); it++) {

		alGetSourcef(instruments.at(it)->soundsource, AL_SEC_OFFSET, &tracking);
		instruments.at(it)->currentStep = (tracking / tempo);
		instruments.at(it)->tempo = tempo;
		instruments.at(it)->render();
	}
	if (playbutton) {
		trackPlay();
	}

}
void debugCB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	cout << "debug call: " << msg << endl;
}


static void WBInit() {
	//int argc;char **argv;
	//int argac;char **argav;

//    glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, true );
	glutInitWindowSize(1024, 728);
	glutDisplayFunc(display);
	wavebricks_window = glutCreateWindow("WaveBricks Main Window");
	glutDisplayFunc(display);
	//GLUI_Master.set_glutIdleFunc (idle);
	//GLUI_Master.set_glutMouseFunc(mouse);
	//GLUI_Master.set_glutDisplayFunc(display);

	glutSetWindow(wavebricks_window);
	glutDisplayFunc(display);

	glewInit();

	if (GL_KHR_debug) {
		cout << "KHR_debug supported" << endl;

		GLint v;
		glGetIntegerv(GL_CONTEXT_FLAGS, &v);
		if (v & GL_CONTEXT_FLAG_DEBUG_BIT) {
			cout << "OpenGL debug context present" << endl;
			//glDebugMessageCallback( debugCB, NULL );
		}
	}


}

void centerOnScreen();
void drawObject();
void printMatrixf(float* matrix);

void printMatrixf(float* matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f%\t", matrix[i * 4 + j]);
		}

		printf("\n");
	}
}

GLUI_Master_Object GLUIMaster;
void initMainBoard()
{
	glutInitWindowSize(250, 275);
	mainboard_pane = glutCreateWindow("Wavebricks Manager");
	glutDisplayFunc(display);
	//GLUI_Master.set_glutIdleFunc (disp);
	//GLUI_Master.set_glutMouseFunc(mouse);
	GLUI_Master.set_glutDisplayFunc(display);
	mainboard_window = GLUI_Master.create_glui_subwindow(mainboard_pane);

	GLUI_Panel* pm_panel = mainboard_window->add_panel("Performance Manager");

	mainboard_window->add_button_to_panel(pm_panel, "Play", PLAYBUTTON, mainboard_callback);
	mainboard_window->add_button_to_panel(pm_panel, "Pause", PAUSEBUTTON, mainboard_callback);
	mainboard_window->add_button_to_panel(pm_panel, "Add Instrument", ADDINSTBUTTON, mainboard_callback);
	mainboard_window->add_spinner_to_panel(pm_panel, "Tracking", GLUI_SPINNER_FLOAT, &tracking, TRACKING_SPINNER, mainboard_callback);
	mainboard_window->add_spinner_to_panel(pm_panel, "Tempo", GLUI_SPINNER_FLOAT, &tempo, TEMPO_SPINNER, mainboard_callback);
	mainboard_window->add_button_to_panel(pm_panel, "Save", SAVEBUTTON, mainboard_callback);
	mainboard_window->add_button_to_panel(pm_panel, "Load", LOADBUTTON, mainboard_callback);

	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	mainboard_window->set_main_gfx_window(mainboard_pane);
	//GLUI_Master.set_glutIdleFunc( NULL );
	//GLUI_Master.set_glutMouseFunc(mouse);
}




int winSelect = 0;


int instCount = 0;
char wnd_title[256];

ALuint songbuffer;

string winTit;


int main(int argc, char* argv[])
{
	cout << "           WaveBricks v 1.0\n      copyright 2019 Noah King(wittymoniker.com)\nmain console window. begin init gl:";
	glutInit(&argc, argv);
	alutInit(&argc, argv);
	//glfwInit();
//    glewInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	WBInit();

	initMainBoard();
	//
		///////////sldjadajsdjjsdaldjsjddjlwdjljw;


	glutSetWindow(wavebricks_window);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMatrixMode(GL_PROJECTION);												// select projection matrix
	glViewport(0, 0, 1024,768);									// set the viewport
	glMatrixMode(GL_PROJECTION);												// set matrix mode
	glLoadIdentity();															// reset projection matrix
	GLfloat aspect = (GLfloat)1024/768;		// set up a perspective projection matrix
	glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);														// specify the clear value for the depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// specify implementation-specific hints
	glClearColor(0.0, 0.0, 0.0, 1.0);



	glutMainLoop();


	//glfwMakeContextCurrent(wavebricks_window);
	//glClear(GL_COLOR_BUFFER_BIT);
	display();
	//glfwSwapBuffers(wavebricks_window);
	//glfwPollEvents();



	return EXIT_SUCCESS;
}
