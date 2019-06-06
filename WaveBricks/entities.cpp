//entities

#include <cmath>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include<iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include "GLUI/glui.h"
#else
//#pragma comment(lib, "glut32.lib")
#include<GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include<GL/gl.h>
#include<GL/glu.h>

#endif

#include "entities.h"
using namespace std;
//int slices = 48;//if needed
//int stacks = 48;//if needed


//GLUI * synth_panel = GLUI_Master.create_glui ("WaveBricks Synth", 0, 400, 650);
//GLUI_Panel *syn_panel = synth_panel->add_panel ("Synth Panel");
//GLuint synth_window= glutCreateWindow ("WaveBricks Instrument");
