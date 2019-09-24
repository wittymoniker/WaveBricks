
#pragma once
#include<windows.h>
#include <stdlib.h>
#include<vector>
#include <algorithm>
//#pragma caomment(lib, "glut32.lib")


//#include <GL/glut.h>
//#include <GL/glew.h>
//#include<GL/freeglut.h>

//#include<GL/glu.h>

#include<glew.h>
//#include<freeglut.h>
#include<glui.h>

//#include<GL/freeglut.h>

//#include <GL/glut.h>
//#include <synths.h>

#include "al.h"
#include "alc.h"
#include "alext.h"
#include "alut.h"
#include "stdio.h"
#include "math.h"
#include <string>
#include"string"
#include<iostream>
#include<vector>
#include <tuple>
#include <utility>
#include <stdio.h>
#include <assert.h>
#include<fstream>




//#include "entities.cpp"
//#include "main.cpp"
using namespace std;

class instrument {
public:


	double coords;
	void initVals();
	float PI;
	ofstream audioout;


	static ALCdevice* dev;
	static ALCcontext* ctx;
	float scale, tempo;
	float currentStep;
	//heuristic;
	bool gravity, collide, d2;
	std::string name;

	std::vector<GLfloat> voicespitch;
	std::vector<GLfloat> voicesamp;
	std::vector<GLfloat> voicesphase;
	std::vector<vector<vector<GLfloat>>> stepvoices;

	std::vector<GLfloat> compamp;
	std::vector<GLfloat> comppitch;
	std::vector<vector<vector<GLfloat>>> composition;

	std::vector<GLfloat> decaystep;






	enum 
	{
		HEURISTIC_LISTBOX,


		XPOS_SPINNER,
		YPOS_SPINNER,
		ZPOS_SPINNER,

		VOICES_SPINNER,
		PANNING_SPINNER,
		PHASEROT_SPINNER,
		PHASESCALE_SPINNER,
		PHASECOLOR_SPINNER,
		AMPCOLOR_SPINNER,
		AMPROT_SPINNER,
		PITCHCOLOR_SPINNER,
		AMPSCALE_SPINNER,
		PITCHSCALE_SPINNER,
		PITCHROT_SPINNER,
		HPFILTERSCALE_SPINNER,
		LPFILTERSCALE_SPINNER,
		HPFILTERCOLOR_SPINNER,
		LPFILTERCOLOR_SPINNER,
		SCALE_SPINNER,
		R_SPINNER,
		G_SPINNER,
		B_SPINNER,
		R_MOD_SPINNER,
		G_MOD_SPINNER,
		B_MOD_SPINNER,
		XMOD_SPINNER,
		YMOD_SPINNER,
		ZMOD_SPINNER,
		FM_SPINNER,
		FMINT_SPINNER,
		AM_SPINNER,
		AMINT_SPINNER,



		ROTATION,


		VOICES_SCRIPT,
		APM_SCRIPT,
		//COLOR_SCRIPT,
		//ENVELOPE_SCRIPT,
		COMPOSITION_SCRIPT,
		VOICEAUTOMATION_SCRIPT,
		DECAY_SCRIPT,
		//FILTER_SCRIPT,

		DESTROY_BUTTON,

	};

	//
	GLuint wavebricks_synth;
	GLUI* synth_panel;
	GLUI_Panel* syn_panel;

	GLUI_Listbox* heuristic_listbox_panel;

	GLUI_Spinner* panning_panel;
	GLUI_Spinner* xpos_spinner_panel;
	GLUI_Spinner* ypos_spinner_panel;
	GLUI_Spinner* zpos_spinner_panel;
	GLUI_Spinner* xmod_spinner_panel;
	GLUI_Spinner* ymod_spinner_panel;
	GLUI_Spinner* zmod_spinner_panel;
	GLUI_Spinner* voices_spinner_panel;
	GLUI_Spinner* scale_spinner_panel;
	GLUI_Spinner* r_spinner_panel;
	GLUI_Spinner* g_spinner_panel;
	GLUI_Spinner* b_spinner_panel;
	GLUI_Spinner* r_mod_spinner_panel;
	GLUI_Spinner* g_mod_spinner_panel;
	GLUI_Spinner* b_mod_spinner_panel;
	GLUI_Spinner* phaserot_spinner_panel;
	GLUI_Spinner* phasecolor_spinner_panel;
	GLUI_Spinner* phasescale_spinner_panel;
	GLUI_Spinner* ampcolor_spinner_panel;
	GLUI_Spinner* pitchcolor_spinner_panel;
	GLUI_Spinner* ampscale_spinner_panel;
	GLUI_Spinner* pitchscale_spinner_panel;
	GLUI_Spinner* pitchrot_spinner_panel;
	GLUI_Spinner* amprot_spinner_panel;
	GLUI_Spinner* fm_spinner_panel;
	GLUI_Spinner* fmint_spinner_panel;
	GLUI_Spinner* am_spinner_panel;
	GLUI_Spinner* amint_spinner_panel;

	GLUI_EditText* voicesscript_panel;
	GLUI_EditText* compositionscript_panel;
	GLUI_EditText* decayscript_panel;


	vector<vector<vector<vector<float>>>>breakpoints;

	int heuristic_listbox;


	int voices_spinner;


	float phasescale_spinner;
	float phaserot_spinner;
	float phasecolor_spinner;
	float pitchscale_spinner;
	float pitchcolor_spinner;
	float ampscale_spinner ;
	float ampcolor_spinner ;
	float xpos_spinner ;
	float ypos_spinner ;
	float zpos_spinner ;
	float rotation[16];
	float hpfilterscale_spinner ;
	float hpfiltercolor_spinner ;
	float lpfilterscale_spinner ;
	float lpfiltercolor_spinner ;
	float scale_spinner ;
	float pitchrot_spinner ;
	float amprot_spinner ;
	float r_spinner ;
	float b_spinner ;
	float g_spinner ;
	float r_mod_spinner ;
	float b_mod_spinner ;
	float g_mod_spinner ;
	float xmod_spinner ;
	float ymod_spinner ;
	float zmod_spinner ;
	float fm_spinner ;
	float fmint_spinner ;
	float am_spinner ;
	float amint_spinner ;
	float panning_spinner ;


	float sizeSS;

	string apm_script;
	string color_script;
	string envelope_script;
	string composition_script;
	string voiceautomation_script;
	string filter_script;
	string decay_script;


	int destroy_button;


	void reshape(int w, int h);
	static void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void pmotion(int x, int y);
	void keyboard(unsigned char key, int x, int y);
	void special(int key, int x, int y);
	void entry(int state);

	int window_width;
	int window_height;
	char* mainboard_title;



	void centerOnScreen();
	void assembleVoices();
	static void idle() {
	}
	void assemble();
	void updateVoices();
	void render();
	void assembleSongData();
	void play();
	long int it, iu, iy, ii, i, ir;
	float srate, freq, amp, phase, decayf, bpm, am, amfreq, fm, fmfreq,step;
	void playVertice();
	static void glui_callback(int control_id) {

	}
#define CASE_RETURN(err) case (err): return "##err"
	const char* al_err_str(ALenum err) {
		switch (err) {
			CASE_RETURN(AL_NO_ERROR);
			CASE_RETURN(AL_INVALID_NAME);
			CASE_RETURN(AL_INVALID_ENUM);
			CASE_RETURN(AL_INVALID_VALUE);
			CASE_RETURN(AL_INVALID_OPERATION);
			CASE_RETURN(AL_OUT_OF_MEMORY);
		}
		return "unknown";
	}
#undef CASE_RETURN

#define __al_check_error(file,line) \
            do { \
                ALenum err = alGetError(); \
                for(; err!=AL_NO_ERROR; err=alGetError()) { \
                    std::cerr << "AL Error " << al_err_str(err) << " at " << file << ":" << line << std::endl; \
                } \
            }while(0)

#define al_check_error() \
            __al_check_error(__FILE__, __LINE__)


	static void init_al();

	static void exit_al();


	vector<vector<GLfloat>> instrumentPoly;
	ALuint source;
	ALuint soundsource;
	ALint data_size;
	ALuint soundbuffer;
	ALuint soundstream;


	std::vector<ALshort> data;
	ALshort* dataAL;
	GLfloat vertices;
	GLfloat colors;







	//int heuristic=0;





};
