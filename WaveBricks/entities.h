#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include<windows.h>
#include <stdlib.h>
#include<vector>
#include <algorithm>
//#pragma comment(lib, "glut32.lib")
#include<GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include <GL/glut.h>
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
template< class T >
class reference_wrapper;
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

        int heuristic_listbox;


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


        GLUI * synth_panel;
        GLfloat vertices;
        GLfloat colors;


        void assembleVoices(){
            vector<vector<vector<vector<float>>>>breakpoints={};
            int last=0;
            for(int i=1;i<stepvoices.size();i++){
                if(!stepvoices[i].empty()){
                    if(!stepvoices.at(i).at(2).empty()){
                        breakpoints.resize(breakpoints.size()+1);
                        breakpoints[breakpoints.size()-1].resize(i+1);
                        breakpoints[breakpoints.size()-1][i].resize(3);
                        breakpoints[breakpoints.size()-1][i][0].resize(voices_spinner);
                        breakpoints[breakpoints.size()-1][i][1].resize(voices_spinner);
                        breakpoints[breakpoints.size()-1][i][2].resize(voices_spinner);
                        breakpoints.at(breakpoints.size()-1).at(i)=(stepvoices.at(i));
                    }
                }
            }
            for (int ir=1; ir<breakpoints.size();ir++){
                int lastBreak=0;
                    for (int iu=breakpoints[lastBreak].size();iu<breakpoints[ir].size();iu++){
                        stepvoices[iu].resize(3);
                        stepvoices[iu][0].resize(voices_spinner);
                        stepvoices[iu][1].resize(voices_spinner);
                        stepvoices[iu][2].resize(voices_spinner);
                        for (int iy=0;iy<breakpoints[ir][iu].size()&&iy<stepvoices[iu][2].size() ;iy++){
                            for (int i=0; i<voices_spinner;i++){
                                stepvoices.at(iu).at(iy).at(i)=(((breakpoints[ir][breakpoints[ir].size()-1][iy][i]/(breakpoints[ir][breakpoints[ir].size()-1][iy][i]
                                                                -breakpoints[lastBreak][breakpoints[lastBreak].size()-1][iy][i])))
                                                                    *stepvoices.at(lastBreak).at(iy).at(i))
                                                                    +(((((breakpoints[ir][breakpoints[ir].size()-1][iy][i])/breakpoints[ir][breakpoints[ir].size()-1][iy][i])
                                                                        /breakpoints[ir][breakpoints[ir].size()-1][iy][i])) *(stepvoices.at(iu).at(iy).at(i)));
                        }
                    }

                }
                if(ir>0){
                   lastBreak=ir-1;
                }
            }
            if (breakpoints.size()==0){
                stepvoices.resize(composition.size());
                for(int i=0;i<stepvoices.size();i++){
                    stepvoices[i]=stepvoices[0];
                }
            }

            last=1;
            if(decaystep.size()<composition.size()){
                decaystep.resize(composition.size());
            }
            for(int i=0;i<decaystep.size();i++){

                if(!decaystep.at(i)){
                    decaystep.at(i)=last;
                }else{
                    int last=decaystep.at(i);
                }
            }
            if(stepvoices.at(currentStep).size()>=3){
                voicesamp.resize(stepvoices.at(currentStep).at(0).size()+1);
                voicespitch.resize(stepvoices.at(currentStep).at(1).size()+1);
                voicesphase.resize(stepvoices.at(currentStep).at(2).size()+1);
                voicesamp=stepvoices.at(currentStep).at(0);
                voicespitch=stepvoices.at(currentStep).at(1);
                voicesphase=stepvoices.at(currentStep).at(2);
            }

        }
        static void idle(){
        }
        void assemble(){
            //cout  << "assemble instrument" ;
            initVals();
            glutInitWindowSize(600,768);
            GLuint wavebricks_synth;
            wavebricks_synth = glutCreateWindow("Wavebricks Synth");
            glutDisplayFunc(idle);
            GLUI_Master.set_glutIdleFunc (idle);


            GLUI * synth_panel = GLUI_Master.create_glui_subwindow (wavebricks_synth);
            GLUI_Panel *syn_panel = synth_panel->add_panel ("Synth Panel");
            //GLuint synth_window= glutCreateWindow ("WaveBricks Instrument");
            //synth_panel->add_listbox_to_panel(syn_panel, "Construction Heuristic", heuristic_listbox );
            GLUI_Listbox *heuristic_listbox_panel = synth_panel->add_listbox_to_panel (syn_panel, "Construction Heuristic", &heuristic_listbox, HEURISTIC_LISTBOX, glui_callback);
            heuristic_listbox_panel->add_item (1, "Vertice Voice 2d");//phase manipulation is rotation around shape, frequency is distance, amplitude contributes to distance between sister vertices
            heuristic_listbox_panel->add_item (2, "Vertice Voice 3d");//phase manipulation is rotation around an axis, frequency is one other axis, and amplitude another axis. octave or order or cycle per distance around shape
            heuristic_listbox_panel->add_item (3, "FM WaveShape 2d");//wave interfered across shape as oscilloscope, clipped at boundaries, FM by changing scanning location, 2d.
            heuristic_listbox_panel->add_item (4, "FM WaveShape 3d");//wave interfered across shape as oscilloscope, clipped at boundaries, FM by changing scanning location, 3d.



            GLUI_Spinner *xpos_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Shape Position X", GLUI_SPINNER_FLOAT, &xpos_spinner, XPOS_SPINNER, glui_callback);
            GLUI_Spinner *ypos_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Shape Position Y", GLUI_SPINNER_FLOAT, &ypos_spinner, YPOS_SPINNER, glui_callback);
            GLUI_Spinner *zpos_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Shape Position Z", GLUI_SPINNER_FLOAT, &zpos_spinner, ZPOS_SPINNER, glui_callback);

            GLUI_Spinner *xmod_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "X Mod", GLUI_SPINNER_FLOAT, &xmod_spinner, XMOD_SPINNER, glui_callback);
            GLUI_Spinner *ymod_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Y Mod", GLUI_SPINNER_FLOAT, &ymod_spinner, YMOD_SPINNER, glui_callback);
            GLUI_Spinner *zmod_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Z Mod", GLUI_SPINNER_FLOAT, &zmod_spinner, ZMOD_SPINNER, glui_callback);


            GLUI_Spinner *voices_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Voices Number", GLUI_SPINNER_INT, &voices_spinner, VOICES_SPINNER, glui_callback);

            GLUI_Spinner *scale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Scale", GLUI_SPINNER_FLOAT, &scale_spinner, SCALE_SPINNER, glui_callback);

            GLUI_Spinner *r_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel,"Red", GLUI_SPINNER_FLOAT, &r_spinner, R_SPINNER, glui_callback);
            GLUI_Spinner *g_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel,"Green", GLUI_SPINNER_FLOAT, &g_spinner, G_SPINNER, glui_callback);
            GLUI_Spinner *b_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel,"Blue", GLUI_SPINNER_FLOAT, &b_spinner, B_SPINNER, glui_callback);

            GLUI_Spinner *r_mod_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel,"Red Mod", GLUI_SPINNER_FLOAT, &r_spinner, R_SPINNER, glui_callback);
            GLUI_Spinner *g_mod_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel,"Green Mod", GLUI_SPINNER_FLOAT, &g_spinner, G_SPINNER, glui_callback);
            GLUI_Spinner *b_mod_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel,"Blue Mod", GLUI_SPINNER_FLOAT, &b_spinner, B_SPINNER, glui_callback);


            GLUI_Spinner *phaserot_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Phase Vertice Rotation Influence", GLUI_SPINNER_FLOAT, &phaserot_spinner, PHASEROT_SPINNER, glui_callback);
            GLUI_Spinner *phasecolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Phase Color Influence", GLUI_SPINNER_FLOAT, &phasecolor_spinner, PHASECOLOR_SPINNER, glui_callback);
            GLUI_Spinner *phasescale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Phase Color Influence", GLUI_SPINNER_FLOAT, &phasescale_spinner, PHASESCALE_SPINNER, glui_callback);
            GLUI_Spinner *ampcolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Amplitude Color Influence", GLUI_SPINNER_FLOAT, &ampcolor_spinner, AMPCOLOR_SPINNER, glui_callback);
            GLUI_Spinner *pitchcolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Pitch Color Influence", GLUI_SPINNER_FLOAT, &pitchcolor_spinner, PITCHCOLOR_SPINNER, glui_callback);
            GLUI_Spinner *ampscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Amplitude Scale Influence", GLUI_SPINNER_FLOAT, &ampscale_spinner, AMPSCALE_SPINNER, glui_callback);
            GLUI_Spinner *pitchscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Pitch Scale Influence", GLUI_SPINNER_FLOAT, &pitchscale_spinner, PITCHSCALE_SPINNER, glui_callback);
            GLUI_Spinner *pitchrot_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Pitch Rotation Influence", GLUI_SPINNER_FLOAT, &pitchrot_spinner, PITCHROT_SPINNER, glui_callback);
            GLUI_Spinner *amprot_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Amplitude Rotation Influence", GLUI_SPINNER_FLOAT, &amprot_spinner, AMPROT_SPINNER, glui_callback);
            GLUI_Spinner *fm_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Frequency Modulation Frequency", GLUI_SPINNER_FLOAT, &fm_spinner, FM_SPINNER, glui_callback);
            GLUI_Spinner *fmint_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Frequency Modulation Intensity", GLUI_SPINNER_FLOAT, &fmint_spinner, FMINT_SPINNER, glui_callback);
            GLUI_Spinner *am_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Amplitude Modulation Frequency", GLUI_SPINNER_FLOAT, &am_spinner, AM_SPINNER, glui_callback);
            GLUI_Spinner *amint_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "Amplitude Modulation Intensity", GLUI_SPINNER_FLOAT, &amint_spinner, AMINT_SPINNER, glui_callback);

           /*
            GLUI_Spinner *hpfilterscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "HP Filter Scale Influence", GLUI_SPINNER_FLOAT, &hpfilterscale_spinner, HPFILTERSCALE_SPINNER, glui_callback);
            GLUI_Spinner *lpfilterscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "LP Filter Scale Influence", GLUI_SPINNER_FLOAT, &lpfilterscale_spinner, LPFILTERSCALE_SPINNER, glui_callback);
            GLUI_Spinner *hpfiltercolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "HP Filter Color Influence", GLUI_SPINNER_FLOAT, &hpfiltercolor_spinner, HPFILTERCOLOR_SPINNER, glui_callback);
            GLUI_Spinner *lpfiltercolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "LP Filter Color Influence", GLUI_SPINNER_FLOAT, &lpfiltercolor_spinner, LPFILTERCOLOR_SPINNER, glui_callback);
        */
        //script so users can define the sine voices differences across a song, or set them steady(see spinners)
            GLUI_EditText *voicesscript_panel = synth_panel->add_edittext_to_panel(syn_panel, "Voices and Voice Automation Script:"
                                                                                       ,voiceautomation_script,VOICEAUTOMATION_SCRIPT,glui_callback);
        //script so users can define composition for song along tracking by BPM
            GLUI_EditText *compositionscript_panel = synth_panel->add_edittext_to_panel(syn_panel, "Composition script:"
                                                                                       ,composition_script,COMPOSITION_SCRIPT,glui_callback);


            GLUI_EditText *decayscript_panel = synth_panel->add_edittext_to_panel(syn_panel, "Decay script:"
                                                                                       ,decay_script,DECAY_SCRIPT,glui_callback);

        //script so users can define envelope changes over song, stretched by note length in composition
           /* GLUI_EditText *envelopescript_panel = synth_panel->add_edittext_to_panel(syn_panel, "Envelope script:"
                                                                                       ,envelope_script,ENVELOPE_SCRIPT,glui_callback);*/
        //script so users can modulate filters over song
            /*GLUI_EditText *filterscript_panel = synth_panel->add_edittext_to_panel(syn_panel, "Filter script:"
                                                                                       ,filter_script,FILTER_SCRIPT,glui_callback);*/
        //script so users can determine which colors are linked to what values (see spinners)
          /*  GLUI_EditText *colorscript_panel = synth_panel->add_edittext_to_panel(syn_panel, "Color Linkage script:"
                                                                                       ,color_script,COLOR_SCRIPT,glui_callback);*/
        //script so users can define vectors of X Y Z rot and movement to what values(see spinners)

            //syn_panel->set_w(600);
            //syn_panel->set_h(650);

            voicesscript_panel->set_h(20);
            voicesscript_panel->set_w(650);

            compositionscript_panel->set_h(20);
            compositionscript_panel->set_w(650);

            decayscript_panel->set_h(20);
            decayscript_panel->set_w(650);

        /*    envelopescript_panel->set_h(15);
            envelopescript_panel->set_w(200);

            filterscript_panel->set_h(15);
            filterscript_panel->set_w(200);

            colorscript_panel->set_h(15);
            colorscript_panel->set_w(200);*/

            //apmscript_panel->set_h(20);
            //apmscript_panel->set_w(200);


            synth_panel->set_main_gfx_window(wavebricks_synth);

            GLUI_Button *exitinst_button = synth_panel->add_button_to_panel(syn_panel, "Delete Instrument", DESTROY_BUTTON, glui_callback);


            //glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
        }
        void updateVoices(){
            decaystep={};
            voicesamp={};
            voicesphase={};
            voicespitch={};
            stepvoices={};
            compamp={};
            comppitch={};
            composition={};
            std::string tempNumber;//
            stepvoices.resize(1);
            composition.resize(1);
            char comma=',';
            char colon=':';
            std::string placement="amp";
            float step=0;
            for(unsigned i=0; i<voiceautomation_script.length();i++){//voices script interpreter

                if (voiceautomation_script[i]!=colon&&voiceautomation_script[i]!=comma){
                    tempNumber=tempNumber+(voiceautomation_script[i]);
                    //cout<<voiceautomation_script.at(i);
                    //cout<<"appended tempNumber" +tempNumber;
                    //cout<<atof(tempNumber);
                }else{
                    //cout <<"else";
                    if(voiceautomation_script[i]==colon){
                            //cout<<colon;
                        if( placement=="amp"&&tempNumber.length()>0){
                            voicesamp.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="pitch";

                        }
                        if( placement=="pitch"&&tempNumber.length()>0){
                            voicespitch.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="phase";
                        }
                        if( placement=="phase"&&tempNumber.length()>0){
                            voicesphase.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="getNewStep";

                        }

                    }
                    if(voiceautomation_script.at(i)==comma){
                        if( placement=="phase"&&tempNumber.length()>0){
                            voicesphase.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="amp";
                        }
                        if( placement=="amp"&&tempNumber.length()>0){
                            voicesamp.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="pitch";
                        }
                        if( placement=="pitch"&&tempNumber.length()>0){
                            voicespitch.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="phase";
                        }
                        if (placement=="getNewStep"&&tempNumber.length()>0){
                            stepvoices[step].push_back(voicesamp);
                            stepvoices[step].push_back(voicespitch);
                            stepvoices[step].push_back(voicesphase);
                            //cout<<(atof(tempNumber.c_str()));
                            step=(atof(tempNumber.c_str()));
                            stepvoices.resize(step+1);

                            voicesamp={};
                            voicespitch={};
                            voicesphase={};
                            tempNumber="";
                            placement="amp";

                        }
                    }
                }

            }
            if( placement=="phase"&&tempNumber.length()>0){
                voicesphase.push_back(atof(tempNumber.c_str()));
                tempNumber="";
                placement="amp";
            }
            if( placement=="amp"&&tempNumber.length()>0){
                voicesamp.push_back(atof(tempNumber.c_str()));
                tempNumber="";
                placement="pitch";
            }
            if( placement=="pitch"&&tempNumber.length()>0){
                voicespitch.push_back(atof(tempNumber.c_str()));
                tempNumber="";
                placement="phase";
            }
            if (placement=="getNewStep"&&tempNumber.length()>0){
                stepvoices[step].push_back(voicesamp);
                stepvoices[step].push_back(voicespitch);
                stepvoices[step].push_back(voicesphase);
                //cout<<(atof(tempNumber.c_str()));
                step=(atof(tempNumber.c_str()));
                stepvoices.resize(step+1);

                voicesamp={};
                voicespitch={};
                voicesphase={};
                tempNumber="";
                placement="amp";

            }

            placement="amp";
            step=0;
            for(unsigned i=0; i<composition_script.length();i++){//composition script interpreter
                if (composition_script.at(i)!=colon&&composition_script[i]!=comma){
                    tempNumber=tempNumber+(composition_script[i]);
                    //cout<<"appended tempNumber" +tempNumber;
                }else{
                    //cout<<"else";
                    if(composition_script.at(i)==colon){
                            //cout<<colon;
                        if( placement=="amp"&&tempNumber.length()>0){
                            compamp.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="pitch";
                        }
                        if( placement=="pitch"&&tempNumber.length()>0){
                           comppitch.push_back(atof(tempNumber.c_str()));
                           //cout<<comppitch.at(0);
                            tempNumber="";
                            placement="getNewStep";
                        }


                    }
                    if(composition_script.at(i)==comma){
                            //cout<<comma;
                        if (placement=="getNewStep"&&tempNumber.length()>0){
                            composition[step].push_back(compamp);
                            composition[step].push_back(comppitch);
                            step=(atof(tempNumber.c_str()));
                            composition.resize(step+1);


                            compamp={};
                            comppitch={};
                            tempNumber="";
                            placement="amp";

                        }
                        if( placement=="amp"&&tempNumber.length()>0){
                            compamp.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="pitch";
                        }
                        if( placement=="pitch"&&tempNumber.length()>0){
                           comppitch.push_back(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="amp";
                        }

                    }
                }
            }
            if (placement=="getNewStep"&&tempNumber.length()>0){
                composition[step].push_back(compamp);
                composition[step].push_back(comppitch);
                step=(atof(tempNumber.c_str()));
                composition.resize(step+1);


                compamp={};
                comppitch={};
                tempNumber="";
                placement="amp";

            }
            if( placement=="amp"&&tempNumber.length()>0){
                compamp.push_back(atof(tempNumber.c_str()));
                tempNumber="";
                placement="pitch";
            }
            if( placement=="pitch"&&tempNumber.length()>0){
               comppitch.push_back(atof(tempNumber.c_str()));
                tempNumber="";
                placement="amp";
            }


            decaystep.resize(1);
            placement="decay";
            step=0;
            for(unsigned i=0; i<decay_script.length();i++){//decay script interpreter
                if (decay_script.at(i)!=colon&&decay_script[i]!=comma){
                    tempNumber=tempNumber+(decay_script[i]);
                    //cout<<"appended tempNumber" +tempNumber;
                }else{
                    if(decay_script.at(i)==colon){
                        //cout<<colon;
                        if( placement=="decay"&&tempNumber.length()>0){
                            decaystep[step]=(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="step";
                        }
                        if( placement=="step"&&tempNumber.length()>0){
                            step=(atof(tempNumber.c_str()));
                            decaystep.resize(step+1);
                            tempNumber="";
                            placement="decay";
                        }

                    }
                    if(decay_script.at(i)==comma){
                            //cout<<comma;
                        if( placement=="decay"&&tempNumber.length()>0){
                            decaystep[step]=(atof(tempNumber.c_str()));
                            tempNumber="";
                            placement="step";
                        }
                        if( placement=="step"&&tempNumber.length()>0){
                            step=(atof(tempNumber.c_str()));
                            decaystep.resize(step+1);
                            tempNumber="";
                            placement="decay";
                        }
                    }
                }
            }
            if( placement=="decay"&&tempNumber.length()>0){
                decaystep[step]=(atof(tempNumber.c_str()));
                tempNumber="";
                placement="step";
            }
            if( placement=="step"&&tempNumber.length()>0){
                step=(atof(tempNumber.c_str()));
                decaystep.resize(step+1);
                tempNumber="";
                placement="decay";
            }



        }
        float instrumentPoly[256][6];
        void render(){
            updateVoices();
            assembleVoices();
           // //glLoadIdentity();
            //glTranslatef(1.5f, 0.0f, -7.0f);

            if (heuristic_listbox=1 && voicesphase.size()>=voices_spinner && voicesamp.size()>=voices_spinner &&composition[currentStep].size()>=2&& voicespitch.size()>=voices_spinner){//2d shape
                for (int i=0; i<voices_spinner;i++){
                        for(int iy=0; iy<composition[currentStep][0].size();iy++){
                            voicesamp[i]+=composition[currentStep][0][iy];
                            voicesamp[i] += voicesamp[i]*sin(currentStep*2.0*PI*am_spinner)*amint_spinner;
                        }
                }
                for (int i=0; i<voices_spinner;i++){
                    for(int iy=0; iy<composition[currentStep][1].size();iy++){
                        voicespitch[i] += voicespitch[i]*sqrt(composition[currentStep][1][iy])/1024;
                        voicespitch[i] += voicespitch[i]*sin(currentStep*2.0*PI*fm_spinner)*fmint_spinner;
                    }
                }
                for (int i=0; i<voices_spinner;i++){
                        //TODO: set voice values all to 1 unless being played, wherat custom values proclaimed
                    instrumentPoly[i][0]=((xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) +
                                            xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)*
                                              scale_spinner*xmod_spinner*sin((i/voices_spinner)*xmod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))));
                    instrumentPoly[i][1]=((ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                           ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) *
                                           scale_spinner*ymod_spinner*cos((i/voices_spinner)*ymod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))
                                            *(pitchscale_spinner*voicespitch.at(i))*(ampscale_spinner*voicesamp[i])));
                    instrumentPoly[i][2]=((zpos_spinner+(zmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)));



                    instrumentPoly[i][3]=(1.0/(r_spinner/(r_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                voicesphase.at(i)))));
                    instrumentPoly[i][4]=(1.0/(g_spinner/(g_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                     voicesphase.at(i)))));
                    instrumentPoly[i][5]=(1.0/(b_spinner/(b_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                    voicesphase.at(i)))));
                }

            }
            if (heuristic_listbox=2 && voicesphase.size()>=voices_spinner && voicesamp.size()>=voices_spinner &&composition[currentStep].size()>=2&& voicespitch.size()>=voices_spinner){//3d shape
                for (int i=0; i<voices_spinner;i++){
                        for(int iy=0; iy<composition[currentStep][0].size();iy++){
                            voicesamp[i]+=composition[currentStep][0][iy];
                            voicesamp[i] += voicesamp[i]*sin(currentStep*2.0*PI*am_spinner)*amint_spinner;
                        }
                }
                for (int i=0; i<voices_spinner;i++){
                    for(int iy=0; iy<composition[currentStep][1].size();iy++){
                        voicespitch[i] += voicespitch[i]*sqrt(composition[currentStep][1][iy])/1024;
                        voicespitch[i] += voicespitch[i]*sin(currentStep*2.0*PI*fm_spinner)*fmint_spinner;
                    }
                }
                for (int i=0; i<voices_spinner;i++){
                    instrumentPoly[i][0]=((xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                            xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)*
                                              scale_spinner*xmod_spinner*sin((i/voices_spinner)*xmod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))));
                    instrumentPoly[i][1]=((ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                           ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) *
                                           scale_spinner*ymod_spinner*cos((i/voices_spinner)*ymod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))
                                            *(pitchscale_spinner*voicespitch.at(i))*(ampscale_spinner*voicesamp[i])));
                    instrumentPoly[i][2]=((zpos_spinner+(zmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                           zpos_spinner+(zmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) *
                                              scale_spinner*zmod_spinner*cos((i/voices_spinner)*zmod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))));

                    instrumentPoly[i][3]=(1.0/(r_spinner/(r_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                voicesphase.at(i)))));
                    instrumentPoly[i][4]=(1.0/(g_spinner/(g_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                     voicesphase.at(i)))));
                    instrumentPoly[i][5]=(1.0/(b_spinner/(b_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                    voicesphase.at(i)))));
                }
            }
            if (heuristic_listbox=3 && voicesphase.size()>=voices_spinner && voicesamp.size()>=voices_spinner &&composition[currentStep].size()>=2&& voicespitch.size()>=voices_spinner){//2d interfere
               for (int i=0; i<voices_spinner;i++){
                        for(int iy=0; iy<composition[currentStep][0].size();iy++){
                            voicesamp[i]+=composition[currentStep][0][iy];
                            voicesamp[i] += voicesamp[i]*sin(currentStep*2.0*PI*am_spinner)*amint_spinner;
                        }
                }
                for (int i=0; i<voices_spinner;i++){
                    for(int iy=0; iy<composition[currentStep][1].size();iy++){
                        voicespitch[i] += voicespitch[i]*sqrt(composition[currentStep][1][iy])/1024;
                        voicespitch[i] += voicespitch[i]*sin(currentStep*2.0*PI*fm_spinner)*fmint_spinner;
                    }
                }
                for (int i=0; i<voices_spinner;i++){
                        //TODO: set voice values all to 1 unless being played, wherat custom values proclaimed
                    instrumentPoly[i][0]=((xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) +
                                            xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)*
                                              scale_spinner*xmod_spinner*sin((i/voices_spinner)*xmod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))));
                    instrumentPoly[i][1]=((ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                           ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) *
                                           scale_spinner*ymod_spinner*cos((i/voices_spinner)*ymod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))
                                            *(pitchscale_spinner*voicespitch.at(i))*(ampscale_spinner*voicesamp[i])));
                    instrumentPoly[i][2]=((zpos_spinner+(zmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)));



                    instrumentPoly[i][3]=(1.0/(r_spinner/(r_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                voicesphase.at(i)))));
                    instrumentPoly[i][4]=(1.0/(g_spinner/(g_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                     voicesphase.at(i)))));
                    instrumentPoly[i][5]=(1.0/(b_spinner/(b_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                    voicesphase.at(i)))));
                }
            }
            if (heuristic_listbox=4 && voicesphase.size()>=voices_spinner && voicesamp.size()>=voices_spinner &&composition[currentStep].size()>=2&& voicespitch.size()>=voices_spinner){//3d interfere
                for (int i=0; i<voices_spinner;i++){
                        for(int iy=0; iy<composition[currentStep][0].size();iy++){
                            voicesamp[i]+=composition[currentStep][0][iy];
                            voicesamp[i] += voicesamp[i]*sin(currentStep*2.0*PI*am_spinner)*amint_spinner;
                        }
                }
                for (int i=0; i<voices_spinner;i++){
                    for(int iy=0; iy<composition[currentStep][1].size();iy++){
                        voicespitch[i] += voicespitch[i]*sqrt(composition[currentStep][1][iy])/1024;
                        voicespitch[i] += voicespitch[i]*sin(currentStep*2.0*PI*fm_spinner)*fmint_spinner;
                    }
                }
                for (int i=0; i<voices_spinner;i++){
                    instrumentPoly[i][0]=((xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                            xpos_spinner+(xmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)*
                                              scale_spinner*xmod_spinner*sin((i/voices_spinner)*xmod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))));
                    instrumentPoly[i][1]=((ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                           ypos_spinner+(ymod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) *
                                           scale_spinner*ymod_spinner*cos((i/voices_spinner)*ymod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))
                                            *(pitchscale_spinner*voicespitch.at(i))*(ampscale_spinner*voicesamp[i])));
                    instrumentPoly[i][2]=((zpos_spinner+(zmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner)+
                                           zpos_spinner+(zmod_spinner*pitchscale_spinner*ampscale_spinner*phasescale_spinner) *
                                              scale_spinner*zmod_spinner*cos((i/voices_spinner)*zmod_spinner*(voicespitch.at(i)*pitchrot_spinner
                                           +voicesamp.at(i)*amprot_spinner+
                                           voicesphase.at(i)*phaserot_spinner))));

                    instrumentPoly[i][3]=(1.0/(r_spinner/(r_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                voicesphase.at(i)))));
                    instrumentPoly[i][4]=(1.0/(g_spinner/(g_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                     voicesphase.at(i)))));
                    instrumentPoly[i][5]=(1.0/(b_spinner/(b_mod_spinner*(pitchcolor_spinner*voicespitch.at(i))*
                                                        (ampcolor_spinner*voicesamp.at(i))*(phasecolor_spinner*
                                                                                                    voicesphase.at(i)))));
                }
            }
        }






        ALuint srate;
        ALuint source;
        ALuint soundsource;
        ALint data_size;
        ALuint soundbuffer;
        ALuint soundstream;

        void playVertice(short data[], float srate,  float freq, float amp, float phase,
                                 float decayf, float bpm,float am,float amfreq, float fm, float fmfreq,float step){
            float ampmult = 1024.0f;
            float cycle = 2.0f;
            float minute = 60.0f;
            float i = 0.0f;
            float ampadj =ampmult* amp;
            float M_PI = PI;

            int sizeSS=((44100*(60/tempo))*composition.size()+ (44100*(60/tempo))*16);
            //data=data;
            for(float i = step*(44100*(60/tempo));i<sizeSS;(i)++){
                //cout<<"\nattempting transfer at "<<i;
                data[(short)i] += (ampadj*(((sin(((freq*2.0*M_PI)/44100*i)*phase+((freq*2.0*M_PI)/44100*i)*(fm*sin((fmfreq*2.0*M_PI)/44100*i))))
                                            +(sin(((freq*2.0*M_PI)/44100*i)+((freq*2.0*M_PI)/44100*i)*(fm*sin((fmfreq*2.0*M_PI)/44100*i))))
                                            *(sin((amfreq*2.0*M_PI)/44100*i)*am))));
            }
        }
        short samples;
        void assembleSongData(){
            updateVoices();
            assembleVoices();
            float bpm = tempo;
            //ALfloat *soundstream;
            ALuint srate = 44100;

            alGenBuffers(1, &soundbuffer);

            short *samples=(short*)malloc(4*((44100*(60/tempo))*composition.size()+ (44100*(60/tempo))*16));

            cout<<composition.size();

            for (int it=0;composition.size()>it&&stepvoices.size()>it;it++){
                for(int iu=0; iu < composition[it].size() && iu < stepvoices[it].size();iu++){
                    for (int ii=0;ii<stepvoices[it][iu].size()&&it<composition[it][iu].size();ii++){
                        for (int iy=0;iy<composition[it][iu].size();iy++){
                            for (int i=0;i<voices_spinner;i++){
                                //cout<<it<<"\n";
                                float amp=composition.at(it).at(iu).at(iy)*stepvoices[it][iu][i];
                                float pitch=composition.at(it).at(iu).at(iy)*stepvoices[it][iu][i];
                                float phase=stepvoices[it][iu][i];
                                float decayf=decaystep.at(it);
                                playVertice(samples,srate,pitch,amp,phase,
                                            decayf,tempo,amint_spinner,am_spinner,fmint_spinner,fm_spinner,it);
                            }
                        }
                    }
                }
            }
            cout<<"\nwrote composition\n";


        }




        static void glui_callback (int control_id){
        }

        void initVals(){
            tempo=160.0;

            PI = 3.141592653589f;

            ALuint srate=44100;
            ALuint soundsource;
            ALint data_size;
            ALuint soundbuffer;
            ALuint soundstream;
            //float soundstreamvec[44100*60*5];


            currentStep=0;
            mainboard_title = ("WaveBricks Synth");



            heuristic_listbox=1;
            voices_spinner=6;
            pitchscale_spinner=0.5;
            pitchcolor_spinner=0.5;
            pitchrot_spinner=0.5;
            ampscale_spinner=0.5;
            ampcolor_spinner=0.5;
            amprot_spinner=0.5;
            phaserot_spinner=0.5;
            phasecolor_spinner=0.5;
            phasescale_spinner=0.5;
            xpos_spinner=1.0;
            ypos_spinner=1.0;
            zpos_spinner=1.0;
            scale_spinner=1.0;
            /*lpfiltercolor_spinner=0.5;
            hpfiltercolor_spinner=0.0;
            lpfilterscale_spinner=0.5;
            hpfilterscale_spinner=0.0;*/
            r_spinner=0.5;
            g_spinner=0.5;
            b_spinner=0.5;
            r_mod_spinner=0.5;
            g_mod_spinner=0.5;
            b_mod_spinner=0.5;
            xmod_spinner=1.0;
            ymod_spinner=1.0;
            zmod_spinner=1.0;
            fm_spinner=0.0;
            fmint_spinner=1.0;
            am_spinner=0.0;
            amint_spinner=1.5;



            /*SCRIPTING

            VOICES:
            START WITH NO STEP NUMBER, COMMA SEPARATED AMP PITCH PHASE, REPEATED FOR EACH VOICE(12 DEFAULT). COLON SEPARATED,
            BEGIN WITH NEW STEP FOR WHICH VOICES WILL TRANSISTION INTO ALONG WITH THE 3*12 INITIALIZERS, SEPARATED BY COMMAS. CONTINUE.

            INTEGER STEPS, FLOAT EVERYTHING ELSE.

            AMP,PITCH,PHASE (x Voices number) : (STEP), AMP,PITCH,PHASE (x Voices number):

            COMPOSITION:
            AMP, PITCH : STEP, AMP, PITCH, AMP, PITCH : //SET FIRST NOTE TO 0AMP,0PITCH if you have to. Multiple notes per step in second step.

            DECAY:

            DECAY, STEP : DECAY, STEP

            */
            //void * __gxx_personality_v0=0;
            //void * _Unwind_Resume =0;
            voiceautomation_script={"1,1.5,0.5,"
                                    "1.3,1.3,0.2,"
                                    "1.2,0.8,.3,"
                                    "1.1,0.4,0.2,"
                                    "4.2,.02,0.7,"
                                    "3,1.25,0.4"
                                    ":16,"
                                    "2,1.9,0.5,"
                                    "1,2.7,0.4,"
                                    "1,2.43,.3,"
                                    "1,0.05,0.4,"
                                    "4,0.06,0.7,"
                                    "3,0.0274,0.4"
                                    ":32,"
                                    "1,1.5,0.5,"
                                    "2,1.3,0.0,"
                                    "1.3,0.8,.3,"
                                    "1,0.4,0.2,"
                                    "4,.02,0.7,"
                                    "3,1.25,0.4"
                                    ":48,"
                                    "2,1.9,0.5,"
                                    "1,2.7,0.4,"
                                    "1,2.43,.3,"
                                    "1,0.05,0.4,"
                                    "4,0.06,0.7,"
                                    "3,0.0274,0.4"
                                    ":63,"
                                    "1,1.5,0.5,"
                                    "2,1.3,0.0,"
                                    "1.3,0.8,.3,"
                                    "1,0.4,0.2,"
                                    "4,.02,0.7,"
                                    "3,1.25,0.4"
                                    ":127,"
                                    "2,1.9,0.5,"
                                    "1,2.7,0.4,"
                                    "1,2.43,.3,"
                                    "1,0.05,0.4,"
                                    "4,0.06,0.7,"
                                    "3,0.0274,0.4:129,"};
            composition_script={"2.0,3.0:"
                                "1.0,1.0,440:"
                                "5,8,666:"
                                "11,1,555:"
                                "18,1.3,707:"
                                "23.3,0.8,1337:"
                                "23,0.4,5096:"
                                "23,.02,741:"
                                "31,1.25,6808:"
                                "36,1.0,440:"
                                "42,8,666:"
                                "43,1,555:"
                                "46,1.3,707:"
                                "52,0.8,1337:"
                                "57,0.4,5096:"
                                "64,.02,741:"
                                "67,1.25,6808:"
                                "73,1.0,440:"
                                "78,8,666:"
                                "82,1,555:"
                                "86,1.3,707:"
                                "87,0.8,1337:"
                                "89,0.4,5096:"
                                "89,.02,741:"
                                "90,1.25,6808:"
                                "95,1.0,440:"
                                "103,8,666:"
                                "103,1,555:"
                                "103,1.3,707:"
                                "100,0.8,1337:"
                                "105.4,5,5096:"
                                "95,.8,741:"
                                "97,1.25,6808:"
                                "96,1.0,440:"
                                "115,8,666:"
                                "118,1,555:"
                                "119,1.3,707:"
                                "120,0.8,1337:"
                                "129,3.0,5096:"};
                decay_script={"1.3,0:"
                             "1.3,15:"
                             "1.3,23:"
                             "1.3,31:"
                             "1.3,47:"
                             "1.3,63:"
                             "1.3,85:"
                             "1.3,129:"};
        }




        //int heuristic=0;





};

#endif // ENTITIES_H_INCLUDED
