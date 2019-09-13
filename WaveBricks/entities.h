
#pragma once
#include<windows.h>
#include <stdlib.h>
#include<vector>
#include <algorithm>
//#pragma comment(lib, "glut32.lib")

//#include <GL/glut.h>
#include <GL/glew.h>
//#include<GL/freeglut.h>

//#include<GL/glu.h>

#include<GL/glui.h>
#include<GL/freeglut.h>

//#include <GL/glut.h>
//#include <synths.h>

#include "al.h"
#include "alc.h"
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




//#include "entities.cpp"
//#include "main.cpp"
using namespace std;

class instrument{
    public:


        double coords;
        void initVars();
        float PI;


        float scale,tempo;
        float currentStep;
        //heuristic;
        bool gravity, collide, d2;
        std::string name;

        std::vector<float> voicespitch;
        std::vector<float> voicesamp;
        std::vector<float> voicesphase;
        std::vector<vector<vector<float>>> stepvoices;

        std::vector<float> compamp;
        std::vector<float> comppitch;
        std::vector<vector<vector<float>>> composition;

        std::vector<float> decaystep;








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

        int heuristic_listbox=1;


        int voices_spinner;


        float phasescale_spinner;
        float phaserot_spinner;
        float phasecolor_spinner;
        float pitchscale_spinner;
        float pitchcolor_spinner;
        float ampscale_spinner;
        float ampcolor_spinner;
        float xpos_spinner;
        float ypos_spinner;
        float zpos_spinner;
        float rotation[16];
        float hpfilterscale_spinner;
        float hpfiltercolor_spinner;
        float lpfilterscale_spinner;
        float lpfiltercolor_spinner;
        float scale_spinner;
        float pitchrot_spinner;
        float amprot_spinner;
        float r_spinner;
        float b_spinner;
        float g_spinner;
        float r_mod_spinner;
        float b_mod_spinner;
        float g_mod_spinner;
        float xmod_spinner;
        float ymod_spinner;
        float zmod_spinner;
        float fm_spinner;
        float fmint_spinner;
        float am_spinner;
        float amint_spinner;
        float panning_spinner=0;


        string apm_script;
        string color_script;
        string envelope_script;
        string composition_script;
        string voiceautomation_script;
        string filter_script;
        string decay_script;


        int destroy_button;


        void reshape (int w, int h);
        static void mouse (int button, int state, int x, int y);
        void motion (int x, int y);
        void pmotion (int x, int y);
        void keyboard (unsigned char key, int x, int y);
        void special (int key, int x, int y);
        void entry (int state);

        int window_width;
        int window_height;
        char *mainboard_title;


        GLUI_Panel *syn_panel;


        void centerOnScreen();
        void assembleVoices();
        static void idle(){
        }
        void assemble();
        void updateVoices();
        void initVals();
        void render();
        void assembleSongData();
        void play();
        void playVertice(ALshort data[], float srate,  float freq, float amp, float phase,
                                 float decayf, float bpm,float am,float amfreq, float fm, float fmfreq,float step);
        static void glui_callback (int control_id){

        }
        #define CASE_RETURN(err) case (err): return "##err"
        const char* al_err_str(ALenum err) {
            switch(err) {
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


        void init_al() {
            ALCdevice *dev = NULL;
            ALCcontext *ctx = NULL;

            const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
            std::cout << "Default device: " << defname << std::endl;

            dev = alcOpenDevice(defname);
            ctx = alcCreateContext(dev, NULL);
            alcMakeContextCurrent(ctx);
        }

        void exit_al() {
            ALCdevice *dev = NULL;
            ALCcontext *ctx = NULL;
            ctx = alcGetCurrentContext();
            dev = alcGetContextsDevice(ctx);

            alcMakeContextCurrent(NULL);
            alcDestroyContext(ctx);
            alcCloseDevice(dev);
        }



        ALuint srate;
        ALuint source;
        ALuint soundsource;
        ALint data_size;
        ALuint soundbuffer;
        ALuint soundstream;


        ALshort *samples;

        GLUI * synth_panel;
        GLfloat vertices;
        GLfloat colors;







        //int heuristic=0;





};
