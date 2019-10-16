#pragma once
#include "entities.cpp"
#include <stdlib.h>
#include <vector>
#include "glew.h"
#include "glui.h"

void instrument::assembleVoices() {
	this->breakpoints = {};
	float last = 0;
	if (this->stepvoices.size() < this->composition.size()) {
		this->stepvoices.resize(this->composition.size());
	}
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (this->i = 0; this->i < this->stepvoices.size(); this->i++) {
		//cout << "for1";
		if (this->stepvoices[this->i].size()==3) {
			//cout << "if1";
			if (this->stepvoices.at(this->i).at(2).size() == this->voices_spinner) {
				//cout << "if2";
				this->breakpoints.resize(this->breakpoints.size() + 1);
				this->breakpoints[this->breakpoints.size() - 1].resize(this->i+1);
				this->breakpoints[this->breakpoints.size() - 1][this->i].resize(3);
				this->breakpoints[this->breakpoints.size() - 1][this->i][0].resize(this->voices_spinner);
				this->breakpoints[this->breakpoints.size() - 1][this->i][1].resize(this->voices_spinner);
				this->breakpoints[this->breakpoints.size() - 1][this->i][2].resize(this->voices_spinner);
				for (this->it = 0; this->it < this->voices_spinner; this->it++) {
					//cout << "for2";
					this->breakpoints.at(this->breakpoints.size() - 1).at(this->i).at(0).at(this->it) = (this->stepvoices.at(this->i).at(0).at(this->it));
					this->breakpoints.at(this->breakpoints.size() - 1).at(this->i).at(1).at(this->it) = (this->stepvoices.at(this->i).at(1).at(this->it));
					this->breakpoints.at(this->breakpoints.size() - 1).at(this->i).at(2).at(this->it) = (this->stepvoices.at(this->i).at(2).at(this->it));
					//cout << "set breakpoints";
				}

			}
		}
	}
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (this->ir = 1; this->ir < this->breakpoints.size(); ir++) {
		int lastBreak = 0;
		for (this->iu = lastBreak; this->iu <= this->breakpoints[ir].size()-1; this->iu++) {
			this->stepvoices[this->iu].resize(3);
			this->stepvoices[this->iu][0].resize(this->voices_spinner);
			this->stepvoices[this->iu][1].resize(this->voices_spinner);
			this->stepvoices[this->iu][2].resize(this->voices_spinner);
			//cout << "\nstep" << this->ir;
			for (this->iy = 0; this->iy < 3; this->iy++) {
				for (this->i = 0; this->i < this->voices_spinner; this->i++) {
					//cout << "breakpoint index step" << this->iu<<"voice step"<<this->i;
					this->stepvoices[this->iu][this->iy][this->i] =
						(this->breakpoints.at(lastBreak).at(this->breakpoints.at(lastBreak).size() - 1).at(this->iy).at(this->i))*((iu-lastBreak)/(this->breakpoints.at(lastBreak).size()-lastBreak))
						+ (this->stepvoices.at(lastBreak).at(this->iy).at(this->i)) * 1/((iu - lastBreak+1.0f) / (this->breakpoints.at(lastBreak).size() - lastBreak));
					//cout <<"stepvoices equal to"<< this->stepvoices.at(this->iu).at(this->iy).at(this->i);
				}
			}

		}
		if (this->ir > 0) {
			lastBreak = this->ir-1;
		}
	}
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (this->i = 0; this->i < this->stepvoices.size(); this->i++) {
		for (this->ir = 0; this->ir < this->voices_spinner; this->ir++) {
			this->stepvoices[this->i].resize(3);
			this->stepvoices[this->i][0].resize(this->voices_spinner);
			this->stepvoices[this->i][1].resize(this->voices_spinner);
			this->stepvoices[this->i][2].resize(this->voices_spinner);
			//this->stepvoices[this->i][this->it][this->ir] = (this->stepvoices[0][this->it][this->ir]);
			this->stepvoices[i][0][this->ir]=(this->stepvoices[0][0][this->ir]);
			//cout << this->stepvoices[i][0][this->ir];
			this->stepvoices[i][1][this->ir] = (this->stepvoices[0][1][this->ir]);
			this->stepvoices[i][2][this->ir] = (this->stepvoices[0][2][this->ir]);
		}
	}
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;

	last = 1;
	if (this->decaystep.size() < this->composition.size()) {
		this->decaystep.resize(this->composition.size());
	}
	for (this->i = 0; this->i < this->decaystep.size(); this->i++) {

		if (this->decaystep[this->i]!=0) {
			last = this->decaystep.at(this->i);
		}
		else {
			this->decaystep[this->i] = last;
		}
	}

	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	if (this->stepvoices.at(floor(this->currentStep)).size() >= 3) {
		this->voicesamp.resize(this->stepvoices.at(this->currentStep).at(0).size() + 1);
		this->voicespitch.resize(this->stepvoices.at(this->currentStep).at(1).size() + 1);
		this->voicesphase.resize(this->stepvoices.at(this->currentStep).at(2).size() + 1);
		this->voicesamp = this->stepvoices.at(this->currentStep).at(0);
		this->voicespitch = this->stepvoices.at(this->currentStep).at(1);
		this->voicesphase = this->stepvoices.at(this->currentStep).at(2);
	}
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
}

void instrument::assemble() {
	//cout  << "assemble instrument" ;
	initVals();
	glutInitWindowSize(700, 800);

	this->wavebricks_synth = glutCreateWindow("Wavebricks Synth");
	//glutDisplayFunc(display);



	this->synth_panel = GLUI_Master.create_glui_subwindow(wavebricks_synth);
	this->syn_panel = synth_panel->add_panel("Synth Panel");
	//GLuint synth_window= glutCreateWindow ("WaveBricks Instrument");
	//synth_panel->add_listbox_to_panel(syn_panel, "Construction Heuristic", heuristic_listbox );
	this->heuristic_listbox_panel = synth_panel->add_listbox_to_panel(this->syn_panel, "Construction Heuristic", &(this->heuristic_listbox), HEURISTIC_LISTBOX, this->glui_callback);
	this->heuristic_listbox_panel->add_item(1, "Vertice Voice 2d");//phase manipulation is rotation around shape, frequency is distance, amplitude contributes to distance between sister vertices
	this->heuristic_listbox_panel->add_item(2, "Vertice Voice 3d");//phase manipulation is rotation around an axis, frequency is one other axis, and amplitude another axis. octave or order or cycle per distance around shape
	this->heuristic_listbox_panel->add_item(3, "AFP XYZ 2d");//wave interfered across shape as oscilloscope, clipped at boundaries, FM by changing scanning location, 2d.
	this->heuristic_listbox_panel->add_item(4, "AFP XYZ  3d");//wave interfered across shape as oscilloscope, clipped at boundaries, FM by changing scanning location, 3d.


	this->panning_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Audio Panning(L/R)", GLUI_SPINNER_FLOAT, &(this->panning_spinner), PANNING_SPINNER, this->glui_callback);

	this->xpos_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Shape Position X", GLUI_SPINNER_FLOAT, &(this->xpos_spinner), XPOS_SPINNER, this->glui_callback);
	this->ypos_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Shape Position Y", GLUI_SPINNER_FLOAT, &(this->ypos_spinner), YPOS_SPINNER, this->glui_callback);
	this->zpos_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Shape Position Z", GLUI_SPINNER_FLOAT, &(this->zpos_spinner), ZPOS_SPINNER, this->glui_callback);

	this->xmod_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "X Mod", GLUI_SPINNER_FLOAT, &(this->xmod_spinner), XMOD_SPINNER, this->glui_callback);
	this->ymod_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Y Mod", GLUI_SPINNER_FLOAT, &(this->ymod_spinner), YMOD_SPINNER, this->glui_callback);
	this->zmod_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Z Mod", GLUI_SPINNER_FLOAT, &(this->zmod_spinner), ZMOD_SPINNER, this->glui_callback);


	this->voices_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Voices Number", GLUI_SPINNER_INT, &(this->voices_spinner), VOICES_SPINNER, this->glui_callback);

	this->scale_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Scale", GLUI_SPINNER_FLOAT, &(this->scale_spinner), SCALE_SPINNER, this->glui_callback);

	this->r_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Red", GLUI_SPINNER_FLOAT, &(this->r_spinner), R_SPINNER, this->glui_callback);
	this->g_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Green", GLUI_SPINNER_FLOAT, &(this->g_spinner), G_SPINNER, this->glui_callback);
	this->b_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Blue", GLUI_SPINNER_FLOAT, &(this->b_spinner), B_SPINNER, this->glui_callback);

	this->r_mod_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Red Mod", GLUI_SPINNER_FLOAT, &(this->r_spinner), R_SPINNER, this->glui_callback);
	this->g_mod_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Green Mod", GLUI_SPINNER_FLOAT, &(this->g_spinner), G_SPINNER, this->glui_callback);
	this->b_mod_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Blue Mod", GLUI_SPINNER_FLOAT, &(this->b_spinner), B_SPINNER, this->glui_callback);


	this->phaserot_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Phase Vertice Rotation Influence", GLUI_SPINNER_FLOAT, &(this->phaserot_spinner), PHASEROT_SPINNER, this->glui_callback);
	this->phasecolor_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Phase Color Influence", GLUI_SPINNER_FLOAT, &(this->phasecolor_spinner), PHASECOLOR_SPINNER, this->glui_callback);
	this->phasescale_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Phase Scale Influence", GLUI_SPINNER_FLOAT, &(this->phasescale_spinner), PHASESCALE_SPINNER, this->glui_callback);
	this->ampcolor_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Amplitude Color Influence", GLUI_SPINNER_FLOAT, &(this->ampcolor_spinner), AMPCOLOR_SPINNER, this->glui_callback);
	this->pitchcolor_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Pitch Color Influence", GLUI_SPINNER_FLOAT, &(this->pitchcolor_spinner), PITCHCOLOR_SPINNER, this->glui_callback);
	this->ampscale_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Amplitude Scale Influence", GLUI_SPINNER_FLOAT, &(this->ampscale_spinner), AMPSCALE_SPINNER, this->glui_callback);
	this->pitchscale_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Pitch Scale Influence", GLUI_SPINNER_FLOAT, &(this->pitchscale_spinner), PITCHSCALE_SPINNER, this->glui_callback);
	this->pitchrot_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Pitch Rotation Influence", GLUI_SPINNER_FLOAT, &(this->pitchrot_spinner), PITCHROT_SPINNER, this->glui_callback);
	this->amprot_spinner_panel = synth_panel->add_spinner_to_panel(this->syn_panel, "Amplitude Rotation Influence", GLUI_SPINNER_FLOAT, &(this->amprot_spinner), AMPROT_SPINNER, this->glui_callback);

	/*
	 GLUI_Spinner *hpfilterscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "HP Filter Scale Influence", GLUI_SPINNER_FLOAT, &hpfilterscale_spinner, HPFILTERSCALE_SPINNER, glui_callback);
	 GLUI_Spinner *lpfilterscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "LP Filter Scale Influence", GLUI_SPINNER_FLOAT, &lpfilterscale_spinner, LPFILTERSCALE_SPINNER, glui_callback);
	 GLUI_Spinner *hpfiltercolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "HP Filter Color Influence", GLUI_SPINNER_FLOAT, &hpfiltercolor_spinner, HPFILTERCOLOR_SPINNER, glui_callback);
	 GLUI_Spinner *lpfiltercolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "LP Filter Color Influence", GLUI_SPINNER_FLOAT, &lpfiltercolor_spinner, LPFILTERCOLOR_SPINNER, glui_callback);
 */
 //script so users can define the sine voices differences across a song, or set them steady(see spinners)
	this->voicesscript_panel = synth_panel->add_edittext_to_panel(this->syn_panel, "Voices and Voice Automation Script:"
		, this->voiceautomation_script, VOICEAUTOMATION_SCRIPT, this->glui_callback);
	//script so users can define composition for song along tracking by BPM
	this->compositionscript_panel = synth_panel->add_edittext_to_panel(this->syn_panel, "Composition script:"
		, this->composition_script, COMPOSITION_SCRIPT, this->glui_callback);

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
	this->voicesscript_panel->set_h(64);
	this->voicesscript_panel->set_w(650);


	this->compositionscript_panel->set_h(64);
	this->compositionscript_panel->set_w(650);


	/*    envelopescript_panel->set_h(15);
		envelopescript_panel->set_w(200);

		filterscript_panel->set_h(15);
		filterscript_panel->set_w(200);

		colorscript_panel->set_h(15);
		colorscript_panel->set_w(200);*/

		//apmscript_panel->set_h(20);
		//apmscript_panel->set_w(200);


	this->synth_panel->set_main_gfx_window(wavebricks_synth);

	GLUI_Button* exitinst_button = synth_panel->add_button_to_panel(syn_panel, "Delete Instrument", DESTROY_BUTTON, glui_callback);


	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
}
void instrument::updateVoices() {
	this->decaystep = {};
	this->voicesamp = {};
	this->voicesphase = {};
	this->voicespitch = {};
	this->stepvoices = {};
	this->compamp = {};
	this->comppitch = {};
	this->composition = {};
	std::string tempNumber;//
	this->stepvoices.resize(1);
	this->composition.resize(1);
	char comma = ',';
	char colon = ':';
	std::string placement = "amp";
	int step = 0;
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (unsigned i = 0; i < this->voiceautomation_script.length(); i++) {//voices script interpreter
		if (this->voiceautomation_script[i] != colon && this->voiceautomation_script[i] != comma) {
			tempNumber = tempNumber + (this->voiceautomation_script[i]);
			//cout<<voiceautomation_script.at(i);
			//cout<<"appended tempNumber" +tempNumber;
			//cout<<atof(tempNumber);
		}
		else {
			//cout <<"else";
			if (this->voiceautomation_script[i] == colon) {
				//cout<<colon;
				if (placement == "amp" && tempNumber.length() > 0) {
					this->voicesamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";

				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					this->voicespitch.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "phase";
				}
				if (placement == "phase" && tempNumber.length() > 0) {
					this->voicesphase.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "getNewStep";

				}

			}
			if (this->voiceautomation_script.at(i) == comma) {
				if (placement == "phase" && tempNumber.length() > 0) {
					this->voicesphase.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "amp";
				}
				if (placement == "amp" && tempNumber.length() > 0) {
					this->voicesamp.push_back(atof(tempNumber.c_str()));
					//cout << "appended amp" << (atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";
				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					this->voicespitch.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "phase";
				}
				if (placement == "getNewStep" && tempNumber.length() > 0) {
					this->stepvoices[step].resize(3);
					for (this->it = 0; this->it < this->voicesphase.size(); this->it++) {
						this->stepvoices[step][0].push_back(this->voicesamp[this->it]);
						this->stepvoices[step][1].push_back(this->voicespitch[this->it]);
						this->stepvoices[step][2].push_back(this->voicesphase[this->it]);
					}
					//cout<<(atof(tempNumber.c_str()));
					step = (atof(tempNumber.c_str()));
					this->stepvoices.resize(step + 1);
					this->stepvoices[step].resize(3);
					for (this->it = 0; this->it < this->voicesphase.size(); this->it++) {
						this->stepvoices[step][0].push_back(this->voicesamp[this->it]);
						this->stepvoices[step][1].push_back(this->voicespitch[this->it]);
						this->stepvoices[step][2].push_back(this->voicesphase[this->it]);
					}
					this->voicesamp = {};
					this->voicespitch = {};
					this->voicesphase = {};
					tempNumber = "";
					placement = "amp";

				}
			}
		}

	}
	if (placement == "phase" && tempNumber.length() > 0) {
		this->voicesphase.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "amp";
	}
	if (placement == "amp" && tempNumber.length() > 0) {
		this->voicesamp.push_back(atof(tempNumber.c_str()));
		//cout << "appended amp" << (atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "pitch";
	}
	if (placement == "pitch" && tempNumber.length() > 0) {
		this->voicespitch.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "phase";
	}
	if (placement == "getNewStep" && tempNumber.length() > 0) {
		this->stepvoices[step].resize(3);
		for (this->it = 0; this->it < this->voicesphase.size(); this->it++) {
			this->stepvoices[step][0].push_back(this->voicesamp[this->it]);
			this->stepvoices[step][1].push_back(this->voicespitch[this->it]);
			this->stepvoices[step][2].push_back(this->voicesphase[this->it]);
		}
		//cout<<(atof(tempNumber.c_str()));
		step = (atof(tempNumber.c_str()));
		this->stepvoices.resize(step + 1);
		this->stepvoices[step].resize(3);
		for (this->it = 0; this->it < this->voicesphase.size(); this->it++) {
			this->stepvoices[step][0].push_back(this->voicesamp[this->it]);
			this->stepvoices[step][1].push_back(this->voicespitch[this->it]);
			this->stepvoices[step][2].push_back(this->voicesphase[this->it]);
		}

		this->voicesamp = {};
		this->voicespitch = {};
		this->voicesphase = {};
		tempNumber = "";
		placement = "amp";

	}

	placement = "getNewStep";
	step = 0;
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (unsigned i = 0; i < this->composition_script.length(); i++) {//composition script interpreter
		if (this->composition_script.at(i) != colon && this->composition_script[i] != comma) {
			tempNumber = tempNumber + (this->composition_script[i]);
			//cout<<"appended tempNumber" +tempNumber;
		}
		else {
			//cout<<"else";
			if (this->composition_script.at(i) == colon) {
				//cout<<colon;
				if (placement == "amp" && tempNumber.length() > 0) {
					this->compamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";
				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					this->comppitch.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "fmint";
				}
				if (placement == "fmint" && tempNumber.length() > 0) {
					this->compfmint.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "fmfreq";
				}
				if (placement == "fmfreq" && tempNumber.length() > 0) {
					this->compfmfreq.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "amint";
				}
				if (placement == "amint" && tempNumber.length() > 0) {
					this->compamint.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "amfreq";
				}
				if (placement == "amfreq" && tempNumber.length() > 0) {
					this->compamfreq.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "decay";
				}
				if (placement == "decay" && tempNumber.length() > 0) {
					this->compdecay.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "decaylevel";
				}
				if (placement == "decaylevel" && tempNumber.length() > 0) {
					this->compdlev.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "getNewStep";
				}
				if (placement == "getNewStep" && tempNumber.length() > 0) {
					this->composition[step].resize(8);
					for (this->it = 0; this->it < this->comppitch.size(); this->it++) {
						this->composition[step][0].push_back(this->compamp[this->it]);
						this->composition[step][1].push_back(this->comppitch[this->it]);
						this->composition[step][2].push_back(this->compfmfreq[this->it]);
						this->composition[step][3].push_back(this->compfmint[this->it]);
						this->composition[step][4].push_back(this->compamfreq[this->it]);
						this->composition[step][5].push_back(this->compamint[this->it]);
						this->composition[step][6].push_back(this->compdecay[this->it]);
						this->composition[step][7].push_back(this->compdlev[this->it]);
					}
					step = (atof(tempNumber.c_str()));
					this->composition.resize(step + 1);
					this->composition[step].resize(8);

					this->compamp = {};
					this->comppitch = {};
					this->compamfreq = {};
					this->compamint = {};
					this->compfmfreq = {};
					this->compfmint = {};
					this->compdlev = {};
					this->compdecay = {};
					tempNumber = "";
					placement = "amp";

				}


			}
			if (composition_script.at(i) == comma) {
				//cout<<comma;
				if (placement == "getNewStep" && tempNumber.length() > 0) {
					this->composition[step].resize(8);
					for (this->it = 0; this->it < this->comppitch.size(); this->it++) {
						this->composition[step][0].push_back(this->compamp[this->it]);
						this->composition[step][1].push_back(this->comppitch[this->it]);
						this->composition[step][2].push_back(this->compfmfreq[this->it]);
						this->composition[step][3].push_back(this->compfmint[this->it]);
						this->composition[step][4].push_back(this->compamfreq[this->it]);
						this->composition[step][5].push_back(this->compamint[this->it]);
						this->composition[step][6].push_back(this->compdecay[this->it]);
						this->composition[step][7].push_back(this->compdlev[this->it]);
					}
					step = (atof(tempNumber.c_str()));
					this->composition.resize(step + 1);
					this->composition[step].resize(8);

					this->compamp = {};
					this->comppitch = {};
					this->compamfreq = {};
					this->compamint = {};
					this->compfmfreq = {};
					this->compfmint = {};
					this->compdlev = {};
					this->compdecay = {};
					tempNumber = "";
					placement = "amp";

				}
				if (placement == "amp" && tempNumber.length() > 0) {
					this->compamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";
				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					this->comppitch.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "fmint";
				}
				if (placement == "fmint" && tempNumber.length() > 0) {
					this->compfmint.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "fmfreq";
				}
				if (placement == "fmfreq" && tempNumber.length() > 0) {
					this->compfmfreq.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "amint";
				}
				if (placement == "amint" && tempNumber.length() > 0) {
					this->compamint.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "amfreq";
				}
				if (placement == "amfreq" && tempNumber.length() > 0) {
					this->compamfreq.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "decay";
				}
				if (placement == "decay" && tempNumber.length() > 0) {
					this->compdecay.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "decaylevel";
				}
				if (placement == "decaylevel" && tempNumber.length() > 0) {
					this->compdlev.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "amp";
				}

			}
		}
	}
	if (placement == "amp" && tempNumber.length() > 0) {
		this->composition[step].resize(8);
		for (this->it = 0; this->it < this->comppitch.size(); this->it++) {
			this->composition[step][0].push_back(this->compamp[this->it]);
			this->composition[step][1].push_back(this->comppitch[this->it]);
			this->composition[step][2].push_back(this->compfmfreq[this->it]);
			this->composition[step][3].push_back(this->compfmint[this->it]);
			this->composition[step][4].push_back(this->compamfreq[this->it]);
			this->composition[step][5].push_back(this->compamint[this->it]);
			this->composition[step][6].push_back(this->compdecay[this->it]);
			this->composition[step][7].push_back(this->compdlev[this->it]);
		}
		step = (atof(tempNumber.c_str()));
		this->composition.resize(step + 1);
		this->composition[step].resize(8);

		this->compamp = {};
		this->comppitch = {};
		this->compamfreq = {};
		this->compamint = {};
		this->compfmfreq = {};
		this->compfmint = {};
		this->compdlev = {};
		this->compdecay = {};
		tempNumber = "";
		placement = "amp";

	}
	if (placement == "getNewStep" && tempNumber.length() > 0) {
		this->composition[step].resize(8);
		for (this->it = 0; this->it < this->comppitch.size(); this->it++) {
			this->composition[step][0].push_back(this->compamp[this->it]);
			this->composition[step][1].push_back(this->comppitch[this->it]);
			this->composition[step][2].push_back(this->compfmfreq[this->it]);
			this->composition[step][3].push_back(this->compfmint[this->it]);
			this->composition[step][4].push_back(this->compamfreq[this->it]);
			this->composition[step][5].push_back(this->compamint[this->it]);
			this->composition[step][6].push_back(this->compdecay[this->it]);
			this->composition[step][7].push_back(this->compdlev[this->it]);
		}
		step = (atof(tempNumber.c_str()));
		this->composition.resize(step + 1);
		this->composition[step].resize(8);

		this->compamp = {};
		this->comppitch = {};
		this->compamfreq = {};
		this->compamint = {};
		this->compfmfreq = {};
		this->compfmint = {};
		this->compdlev = {};
		this->compdecay = {};
		tempNumber = "";
		placement = "amp";

	}



}



void instrument::render() {
	glPatchParameteri(GL_PATCH_VERTICES, this->voices_spinner);
	//glPatchParameteri(GL_PATCH_VERTICES,voices_spinner);
	//glTranslatef(0.0f, 0.0f, -7.0f);
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	glBegin(GL_TRIANGLES);
	this->instrumentPoly.resize(this->voices_spinner);
	for (int i = 0; i < this->voices_spinner; i++) {
		this->instrumentPoly[i].resize(6);
	}
	this->updateVoices();
	this->assembleVoices();
	// //glLoadIdentity();
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (int i = 0; i < this->voices_spinner; i++) {
		this->voicesamp[i] = this->stepvoices[this->currentStep][0][i];
		this->voicespitch[i] = this->stepvoices[this->currentStep][1][i];
		this->voicesphase[i] = this->stepvoices[this->currentStep][2][i];
		//cout<<"\nvoicespitch phase amp "<<" " <<voicesamp[i]<< " "<<voicespitch[i]<<" "<<voicesphase[i]<<" "<<heuristic_listbox<<"\n";
	}
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	if (this->heuristic_listbox = 1 && this->voicesphase.size() >= this->voices_spinner && this->voicesamp.size() >= this->voices_spinner && this->composition[this->currentStep].size() >= 2 && this->voicespitch.size() >= this->voices_spinner) {//2d shape
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][0].size(); iy++) {
				this->voicesamp[i] += this->composition[this->currentStep][0][iy];
				this->voicesamp[i] += this->voicesamp[i] * sin(this->currentStep * 2.0 * this->PI * this->am) * this->amint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][1].size(); iy++) {
				this->voicespitch[i] += this->voicespitch[i] * sqrt(this->composition[this->currentStep][1][iy]) / 1024;
				this->voicespitch[i] += this->voicespitch[i] * sin(this->currentStep * 2.0 * PI * this->fm) * this->fmint;
				//cout<<"\nvoicespitch phase amp "<<" " <<voicesamp[i]<< " "<<voicespitch[i]<<" "<<voicesphase[i]<<"\n";
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			//TODO: set voice values all to 1 unless being played, wherat custom values proclaimed
			this->instrumentPoly[i][0] = (GLfloat)((this->xpos_spinner + (this->xmod_spinner * this->pitchscale_spinner * this->ampscale_spinner * this->phasescale_spinner))) * this->voicesamp[i] * this->voicespitch[i] * this->voicesphase[i] + this->voicesamp[i] + this->voicespitch[i] + this->voicesphase[i];
			this->instrumentPoly[i][1] = (GLfloat)((this->ypos_spinner + (this->ymod_spinner * this->pitchscale_spinner))) * this->voicespitch[i] + this->voicespitch[i];

			this->instrumentPoly[i][2] = (GLfloat)((this->zpos_spinner)) + this->voicesamp[i];

			this->instrumentPoly[i][3] = (GLfloat)(1.0 / (this->r_spinner / (this->r_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][4] = (GLfloat)(1.0 / (this->g_spinner / (this->g_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][5] = (GLfloat)(1.0 / (this->b_spinner / (this->b_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			if (this->instrumentPoly[i][3] < 0) {
				this->instrumentPoly[i][3] = (GLfloat)0 - this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][3] > 1) {
				this->instrumentPoly[i][3] = (GLfloat)1 / this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][4] < 0) {
				this->instrumentPoly[i][4] = (GLfloat)0 - this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][4] > 1) {
				this->instrumentPoly[i][4] = (GLfloat)1 / this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][5] < 0) {
				this->instrumentPoly[i][5] = (GLfloat)0 - this->instrumentPoly[i][5];
			}
			if (this->instrumentPoly[i][5] > 1) {
				this->instrumentPoly[i][5] = (GLfloat)1 / this->instrumentPoly[i][5];
			}
			glColor3f((GLfloat)this->instrumentPoly[i][3], (GLfloat)this->instrumentPoly[i][4], (GLfloat)this->instrumentPoly[i][5]);
			//cout << (GLfloat)this->instrumentPoly[i][3] << " " << (GLfloat)this->instrumentPoly[i][4] << " " << (GLfloat)this->instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)this->instrumentPoly[i][0], (GLfloat)this->instrumentPoly[i][1], (GLfloat)this->instrumentPoly[i][2]);
			//cout << (GLfloat)this->instrumentPoly[i][0] << " " << (GLfloat)this->instrumentPoly[i][1] << " " << (GLfloat)this->instrumentPoly[i][2] << " VERTS\n";

		}

	}
	if (this->heuristic_listbox = 2 && this->voicesphase.size() >= this->voices_spinner && this->voicesamp.size() >= this->voices_spinner && this->composition[this->currentStep].size() >= 2 && this->voicespitch.size() >= this->voices_spinner) {//3d shape
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][0].size(); iy++) {
				this->voicesamp[i] += this->composition[currentStep][0][iy];
				this->voicesamp[i] += this->voicesamp[i] * sin(this->currentStep * 2.0 * this->PI * this->am) * this->amint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][1].size(); iy++) {
				this->voicespitch[i] += voicespitch[i] * sqrt(composition[currentStep][1][iy]) / 1024;
				voicespitch[i] += voicespitch[i] * sin(currentStep * 2.0 * PI * fm) * fmint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			this->instrumentPoly[i][0] = (GLfloat)((this->xpos_spinner + (this->xmod_spinner * this->pitchscale_spinner * this->ampscale_spinner * this->phasescale_spinner))) * this->voicesamp[i] * this->voicespitch[i] * this->voicesphase[i] + this->voicesamp[i] + this->voicespitch[i] + this->voicesphase[i];
			this->instrumentPoly[i][1] = (GLfloat)((this->ypos_spinner + (this->ymod_spinner * this->pitchscale_spinner))) * this->voicespitch[i] + this->voicespitch[i];
			this->instrumentPoly[i][2] = (GLfloat)((this->zpos_spinner + (this->zmod_spinner * this->pitchscale_spinner * this->ampscale_spinner))) * this->voicesamp[i] * this->voicespitch[i] + this->voicesamp[i] + this->voicespitch[i];

			this->instrumentPoly[i][3] = (GLfloat)(1.0 / (this->r_spinner / (this->r_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][4] = (GLfloat)(1.0 / (this->g_spinner / (this->g_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][5] = (GLfloat)(1.0 / (this->b_spinner / (this->b_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			if (this->instrumentPoly[i][3] < 0) {
				this->instrumentPoly[i][3] = (GLfloat)0 - this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][3] > 1) {
				this->instrumentPoly[i][3] = (GLfloat)1 / this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][4] < 0) {
				this->instrumentPoly[i][4] = (GLfloat)0 - this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][4] > 1) {
				this->instrumentPoly[i][4] = (GLfloat)1 / this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][5] < 0) {
				this->instrumentPoly[i][5] = (GLfloat)0 - this->instrumentPoly[i][5];
			}
			if (this->instrumentPoly[i][5] > 1) {
				this->instrumentPoly[i][5] = (GLfloat)1 / this->instrumentPoly[i][5];
			}
			glColor3f((GLfloat)this->instrumentPoly[i][3], (GLfloat)this->instrumentPoly[i][4], (GLfloat)this->instrumentPoly[i][5]);
			//cout << (GLfloat)this->instrumentPoly[i][3] << " " << (GLfloat)this->instrumentPoly[i][4] << " " << (GLfloat)this->instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)this->instrumentPoly[i][0], (GLfloat)this->instrumentPoly[i][1], (GLfloat)this->instrumentPoly[i][2]);
			//cout << (GLfloat)this->instrumentPoly[i][0] << " " << (GLfloat)this->instrumentPoly[i][1] << " " << (GLfloat)this->instrumentPoly[i][2] << " VERTS\n";
		}
	}
	if (this->heuristic_listbox = 3 && this->voicesphase.size() >= this->voices_spinner && this->voicesamp.size() >= this->voices_spinner && this->composition[this->currentStep].size() >= 2 && this->voicespitch.size() >= this->voices_spinner) {//2d interfere
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][0].size(); iy++) {
				this->voicesamp[i] += this->composition[this->currentStep][0][iy];
				this->voicesamp[i] += this->voicesamp[i] * sin(this->currentStep * 2.0 * this->PI * this->am) * this->amint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][1].size(); iy++) {
				this->voicespitch[i] += this->voicespitch[i] * sqrt(this->composition[this->currentStep][1][iy]) / 1024;
				this->voicespitch[i] += this->voicespitch[i] * sin(this->currentStep * 2.0 * this->PI * this->fm) * this->fmint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			//TODO: set voice values all to 1 unless being played, wherat custom values proclaimed
			this->instrumentPoly[i][0] = (GLfloat)((this->xpos_spinner + (this->xmod_spinner * this->pitchscale_spinner) +
				this->xpos_spinner + (this->xmod_spinner * this->pitchscale_spinner) *
				this->scale_spinner * this->xmod_spinner * sin((i / this->voices_spinner) * this->xmod_spinner * (this->voicespitch.at(i) * this->pitchrot_spinner))));
			this->instrumentPoly[i][1] = (GLfloat)((this->ypos_spinner + (this->ymod_spinner * this->ampscale_spinner) +
				this->ypos_spinner + (this->ymod_spinner * this->ampscale_spinner) *
				this->scale_spinner * this->ymod_spinner * cos((i / this->voices_spinner) * this->ymod_spinner * (this->voicesamp.at(i) * this->amprot_spinner)) *
				(this->ampscale_spinner * this->voicesamp[i])));
			this->instrumentPoly[i][2] = (GLfloat)((this->zpos_spinner));

			this->instrumentPoly[i][3] = (GLfloat)(1.0 / (this->r_spinner / (this->r_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					voicesphase.at(i)))));
			this->instrumentPoly[i][4] = (GLfloat)(1.0 / (this->g_spinner / (this->g_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][5] = (GLfloat)(1.0 / (this->b_spinner / (this->b_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			if (this->instrumentPoly[i][3] < 0) {
				this->instrumentPoly[i][3] = (GLfloat)0 - this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][3] > 1) {
				this->instrumentPoly[i][3] = (GLfloat)1 / this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][4] < 0) {
				this->instrumentPoly[i][4] = (GLfloat)0 - this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][4] > 1) {
				this->instrumentPoly[i][4] = (GLfloat)1 / this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][5] < 0) {
				this->instrumentPoly[i][5] = (GLfloat)0 - this->instrumentPoly[i][5];
			}
			if (this->instrumentPoly[i][5] > 1) {
				this->instrumentPoly[i][5] = (GLfloat)1 / this->instrumentPoly[i][5];
			}
			glColor3f((GLfloat)this->instrumentPoly[i][3], (GLfloat)this->instrumentPoly[i][4], (GLfloat)this->instrumentPoly[i][5]);
			//cout << (GLfloat)this->instrumentPoly[i][3] << " " << (GLfloat)this->instrumentPoly[i][4] << " " << (GLfloat)this->instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)this->instrumentPoly[i][0], (GLfloat)this->instrumentPoly[i][1], (GLfloat)this->instrumentPoly[i][2]);
			//cout << (GLfloat)this->instrumentPoly[i][0] << " " << (GLfloat)this->instrumentPoly[i][1] << " " << (GLfloat)this->instrumentPoly[i][2] << " VERTS\n";
		}
	}
	if (this->heuristic_listbox = 4 && this->voicesphase.size() >= this->voices_spinner && this->voicesamp.size() >= this->voices_spinner && this->composition[this->currentStep].size() >= 2 && this->voicespitch.size() >= this->voices_spinner) {//3d interfere
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][0].size(); iy++) {
				this->voicesamp[i] += this->composition[this->currentStep][0][iy];
				this->voicesamp[i] += this->voicesamp[i] * sin(this->currentStep * 2.0 * this->PI * this->am) * this->amint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			for (int iy = 0; iy < this->composition[this->currentStep][1].size(); iy++) {
				this->voicespitch[i] += this->voicespitch[i] * sqrt(this->composition[currentStep][1][iy]) / 1024;
				this->voicespitch[i] += this->voicespitch[i] * sin(this->currentStep * 2.0 * this->PI * this->fm) * this->fmint;
			}
		}
		for (int i = 0; i < this->voices_spinner; i++) {
			this->instrumentPoly[i][0] = (GLfloat)((this->xpos_spinner + (this->xmod_spinner * this->pitchscale_spinner) +
				this->xpos_spinner + (this->xmod_spinner * this->pitchscale_spinner) *
				this->scale_spinner * this->xmod_spinner * sin((i / this->voices_spinner) * this->xmod_spinner * (this->voicespitch.at(i) * this->pitchrot_spinner))));
			this->instrumentPoly[i][1] = (GLfloat)((this->ypos_spinner + (this->ymod_spinner * this->ampscale_spinner) +
				this->ypos_spinner + (this->ymod_spinner * this->ampscale_spinner) *
				this->scale_spinner * this->ymod_spinner * cos((i / this->voices_spinner) * this->ymod_spinner * (this->voicesamp.at(i) * this->amprot_spinner)) *
				(this->ampscale_spinner * this->voicesamp[i])));
			this->instrumentPoly[i][2] = (GLfloat)((this->zpos_spinner + (this->zmod_spinner * this->phasescale_spinner) +
				this->zpos_spinner + (this->zmod_spinner * this->phasescale_spinner) *
				this->scale_spinner * this->zmod_spinner * tan((i / this->voices_spinner) * this->zmod_spinner * (this->voicesphase.at(i) * this->phaserot_spinner))));

			this->instrumentPoly[i][3] = (GLfloat)(1.0 / (this->r_spinner / (this->r_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][4] = (GLfloat)(1.0 / (this->g_spinner / (this->g_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			this->instrumentPoly[i][5] = (GLfloat)(1.0 / (this->b_spinner / (this->b_mod_spinner * (this->pitchcolor_spinner * this->voicespitch.at(i)) *
				(this->ampcolor_spinner * this->voicesamp.at(i)) * (this->phasecolor_spinner *
					this->voicesphase.at(i)))));
			if (this->instrumentPoly[i][3] < 0) {
				this->instrumentPoly[i][3] = (GLfloat)0 - this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][3] > 1) {
				this->instrumentPoly[i][3] = (GLfloat)1 / this->instrumentPoly[i][3];
			}
			if (this->instrumentPoly[i][4] < 0) {
				this->instrumentPoly[i][4] = (GLfloat)0 - this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][4] > 1) {
				this->instrumentPoly[i][4] = (GLfloat)1 / this->instrumentPoly[i][4];
			}
			if (this->instrumentPoly[i][5] < 0) {
				this->instrumentPoly[i][5] = (GLfloat)0 - this->instrumentPoly[i][5];
			}
			if (this->instrumentPoly[i][5] > 1) {
				this->instrumentPoly[i][5] = (GLfloat)1 / this->instrumentPoly[i][5];
			}
			glColor3f((GLfloat)this->instrumentPoly[i][3], (GLfloat)this->instrumentPoly[i][4], (GLfloat)this->instrumentPoly[i][5]);
			//cout << (GLfloat)this->instrumentPoly[i][3] << " " << (GLfloat)this->instrumentPoly[i][4] << " " << (GLfloat)this->instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)this->instrumentPoly[i][0], (GLfloat)this->instrumentPoly[i][1], (GLfloat)this->instrumentPoly[i][2]);
			//cout << (GLfloat)this->instrumentPoly[i][0] << " " << (GLfloat)this->instrumentPoly[i][1] << " " << (GLfloat)this->instrumentPoly[i][2] << " VERTS\n";
		}
	}
	glEnd();
	glutSwapBuffers();
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
}







void instrument::assembleSongData() {
	this->sizeSS = this->composition.size() * 2 * (22050.0f * (60.0f / this->tempo));
	this->data = {};
	(this->data).resize(this->sizeSS);
	this->updateVoices();
	this->assembleVoices();
	//cout << "sizeof samples:" << sizeof(&(this->samples));
	this->init_al();
	float bpm = this->tempo;
	//ALfloat *soundstream;
	this->srate = 22050;
	

	alGenBuffers(1, &(this->soundbuffer));
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	//cout<<composition.size();
	
	cout << " compsize " << this->composition.size() << " voicesize " << this->stepvoices.size();
	for ((this->it = 0); (this->it) < (this->composition.size()); (this->it) = (this->it + 1)) {
		//this->updateVoices();
		//this->assembleVoices();
		
		//cout << "composition[it]: " << composition[it].size();
		for (this->iu = 0; this->iu < this->composition[this->it].size(); this->iu++) {
			for (this->ir = 0; (this->ir) < (this->composition.at(this->it).at(5).size()); (this->ir) = (this->ir + 1)) {
				for (this->ii = 0; this->ii < this->voices_spinner; (this->ii) = (this->ii + 1)) {
					//cout << "\n verticeplay, stepvoices pitch: " << this->stepvoices.at(this->it).at(1).at(this->ii);
					this->amp = this->composition.at(this->it).at(0).at(this->ir) * (this->stepvoices.at(this->it).at(0).at(this->ii));
					this->freq = this->composition.at(this->it).at(1).at(this->ir) * (this->stepvoices.at(this->it).at(1).at(this->ii));
					this->phase = (this->stepvoices.at(this->it).at(2).at(this->ii));
					(this->step) = (this->it);
					this->decayf = this->composition.at(this->it).at(6).at(this->ir);
					this->decayl = this->composition.at(this->it).at(7).at(this->ir);
					this->fmint = composition.at(this->it).at(2).at(this->ir);
					this->fm = composition.at(this->it).at(3).at(this->ir);
					this->amint = composition.at(this->it).at(4).at(this->ir);
					this->am = composition.at(this->it).at(5).at(this->ir);
					//cout << "\n amp pitch phase:" << this->amp<<","<<this->freq<<","<<this->phase;
					this->playVertice();

				}
			}
		}
		
	}
	this->i = 0;
}
void instrument::playVertice() {
	float ampmult = 8.0f;
	float cycle = 2.0f;
	float minute = 60.0f;
	float ampadj = ampmult * this->amp;
	float M_PI = this->PI;

	this->fm = this->fmint;
	this->fmfreq = this->fm;
	this->am = this->amint;
	this->amfreq = this->am;

	this->sizeSS = (this->composition.size() * 2 * (22050.0f * (60.0f / this->tempo)));
	//cout << " sizeSS:" << this->sizeSS << " currentstep : " << this->step << " decay: " << this->decayf;
	//data=data;
	//this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
	for (this->i = (long)(this->step * (22050.0f * (float)(60.0f / this->tempo))); this->i < (long)(((this->step + ((1.0f+(this->decayf)))) * (22050.0f * (float)(60.0f / this->tempo)))) && this->i < this->sizeSS-1; this->i = this->i + 1) {
		if ((this->data.at(this->i) + (ALshort)(((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
			+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
			* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))))
			+
			((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
				+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am)))) * ((i - (this->step * 22050 * (60 / this->tempo))) / (22050 * (60 / this->tempo))) * (this->decayl)) < 32767)
			&&
			(this->data.at(this->i) + (ALshort)(((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
				+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))))
				+
				((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
					+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
					* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am)))) * ((i - (this->step * 22050 * (60 / this->tempo))) / (22050 * (60 / this->tempo))) * (this->decayl)) > -32768))
		{

			this->data.at(this->i) += (ALshort)(((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin( (this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
				+ ampadj*(sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				* (1.0+sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))))
				+ 
				((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
					+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
					* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))))*((i-(this->step*22050*(60/this->tempo)))/(22050 * (60 / this->tempo)))*(this->decayl));
			//cout << (ALshort)(ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i) * this->phase + ((this->freq * 2.0 * this->PI) / 22050 * i) * (this->fm * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				//+ (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) * (this->fm * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				//* (sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))));
		}

		
		else {
			if (((this->data.at(this->i))) + (ALshort)(((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
				+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))))
				+
				((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
					+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
					* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am)))) * ((i - (this->step * 22050 * (60 / this->tempo))) / (22050 * (60 / this->tempo))) * (this->decayl)) > 32767)
			{
				(this->data.at(this->i)) = 32767;
			}
			if (((this->data.at(this->i))) + (ALshort)(((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
				+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
				* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am))))
				+
				((ampadj * (((sin(((this->freq * 2.0 * this->PI) / 22050 * i + (this->phase * (22050.0 / this->freq))) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i)))))
					+ ampadj * (sin(((this->freq * 2.0 * this->PI) / 22050 * i) + ((this->freq * 2.0 * this->PI) / 22050 * i) + (this->fm * this->freq * sin((this->fmfreq * 2.0 * this->PI) / 22050 * i))))
					* (1.0 + sin((this->amfreq * 2.0 * this->PI) / 22050 * i) * this->am)))) * ((i - (this->step * 22050 * (60 / this->tempo))) / (22050 * (60 / this->tempo))) * (this->decayl)) < -32767)
			{
				(this->data.at(this->i)) = -32767;
			}
			if ((this->data.at(this->i)) == 0) {
				(this->data.at(this->i)) = 0;
			}
		}
		//}
		



	}
	//cout << "play note ";

}








void instrument::play() {
	this->dataAL = new ALshort[this->sizeSS];
	for (this->i = 0; this->i < this->sizeSS - 1; this->i++) {
		this->dataAL[i] =(ALshort) this->data[i];
	}
	alGenBuffers(1, &this->soundbuffer);
	alBufferData(this->soundbuffer, AL_FORMAT_MONO16, (this->dataAL), (ALsizei)(this->composition.size() * 2 * (22050 * (60 / (int)this->tempo))), (ALsizei)(22050));
	alGenSources(1, &(this->soundsource));
	alSourcei(this->soundsource, AL_BUFFER, (ALint)this->soundbuffer);
	alSourcePlay(this->soundsource);
	cout << "play";
	cout << "\nwrote composition\n";
	// Write the file headers
	this->it = 0, this->iu = 0, this->iy = 0, this->ii = 0, this->i = 0, this->ir = 0;
}






void instrument::initVals() {
	this->tempo = 160.0;

	this->PI = 3.141592653589f;

	this->srate = 22050;
	this->soundsource;
	this->data_size;
	this->soundbuffer;
	this->soundstream;
	//float soundstreamvec[44100*60*5];


	this->currentStep = 0;
	this->mainboard_title = ((char*)"WaveBricks Synth");



	this->heuristic_listbox = 1;


	this->voices_spinner = 128;


	this->pitchscale_spinner = 0.5;
	this->pitchcolor_spinner = 0.5;
	this->pitchrot_spinner = 0.5;
	this->ampscale_spinner = 0.5;
	this->ampcolor_spinner = 0.5;
	this->amprot_spinner = 0.5;
	this->phaserot_spinner = 0.5;
	this->phasecolor_spinner = 0.5;
	this->phasescale_spinner = 0.5;
	this->xpos_spinner = 0.0;
	this->ypos_spinner = 0.0;
	this->zpos_spinner = 0.0;
	this->scale_spinner = 1.0;
	/*lpfiltercolor_spinner=0.5;
	hpfiltercolor_spinner=0.0;
	lpfilterscale_spinner=0.5;
	hpfilterscale_spinner=0.0;*/
	this->r_spinner = 0.5;
	this->g_spinner = 0.5;
	this->b_spinner = 0.5;
	this->r_mod_spinner = 0.5;
	this->g_mod_spinner = 0.5;
	this->b_mod_spinner = 0.5;
	this->xmod_spinner = 1.0;
	this->ymod_spinner = 1.0;
	this->zmod_spinner = 1.0;
	this->fm = 0.0;
	this->fmint = 1.0;
	this->am = 0.0;
	this->amint = 1.5;



	/*SCRIPTING README
	*** REMEMBER: DELETE YOUR VOICES AUTOMATION SCRIPTS EVERY TIME YOU RESIZE THE INSTRUMENT VOICE COUNT.
	PUT FUNCTIONS LIKE ROOT, SIN, ETC in PARENTHESES, OR HAVE ANY AND ALL MULTIPLYING FACTORS BEFORE BUT NOT AFTER.
	REPRESENT ALL WHOLE NUMBERS AS FLOAT WITH .0.
	VOICES SPINNER MUST NEVER BE LESS THAN THE NUMBER OF VOICES LISTED IN SCRIPT. YOU MAY SET VOICES SPINNER TO THE 
	NUMBER OF WHICH THE SCRIPT CALLS FOR, IN ORDER TO TESSELLATE THE SHAPE MORE EFFECTIVELY.
	EVERY VOICES AND COMP SCRIPT MUST END WITH A STEP NUMBER THAT IS THE STEP +1 OR HIGHER, FOLLOWED BY A COMMA.
	SCRIPTING FOR COMPOSITION NOW RELIES ON SIX VARIABLES, THE STEP FOLLOWED BY AMP AND PITCH PLUS FM AND AM 
	INTENSITIES AND FREQUENCIES PER STEP IN THAT ORDER.
	
	BEGIN WITH NEW STEP FOR WHICH VOICES WILL TRANSISTION INTO ALONG WITH THE 3*12 INITIALIZERS, SEPARATED BY COMMAS. 
	CONTINUE.

	INTEGER STEPS, FLOAT EVERYTHING ELSE. GOOD PRACTICE TO REPRESENT EVERY WHOLE NUMBER WITH A .0.

	
	VOICES SCRIPTING:
	START WITH NO STEP NUMBER, COMMA SEPARATED AMP PITCH PHASE, REPEATED FOR EACH VOICE(12 DEFAULT). COLON SEPARATED,
	
	AMP,PITCH,PHASE (x Voices number) : (STEP), AMP,PITCH,PHASE (x Voices number):

	COMPOSITION SCRIPTING:

	STEP, AMP, PITCH,  FMINT, FMFREQ, AMINT, AMFREQ, DECAY TIME +/- STEP, DECAY INTENSITY +/- AMP: 
	STEP, AMP, PITCH, FMINT, FMFREQ, AMINT, AMFREQ, DECAY TIME +/- STEP, DECAY INTENSITY +/- AMP,       
	AMP, PITCH, FMINT, FMFREQ, AMINT, AMFREQ, DECAY TIME +/- STEP, DECAY INTENSITY +/- AMP : 

	//Multiple notes per step in second  scripted step.

	

	DECAY:

	DECAY, STEP : DECAY, STEP

	*IF IT DOESN'T COMPOSE, YOU *PROBABLY* made a comma  or colon error or enumeration error.

	*/







	this->voiceautomation_script = {
		".5,2,0,"
		"1,4,0,"
		"1.5,8,0,"
		"2,16,0:1,"

	};


	this->composition_script = {
		"0,2,16,0,0,0,0,1,2,"
		".5,24,0,0,0,0,2,2:"
		"1,1,52,1,1,0,0,1,2,"
		".5,48,0,0,1,1,2,2:"
		"2,1,52,0,0,1,1,1,2,"
		".5,64,1,1,0,0,2,2:"
		"3,2,86,0,0,0,0,1,2,"
		".5,24,0,0,0,0,2,2:"
		"4,2,48,1,.5,0,0,1,2,"
		".5,52,0,0,1,.5,2,2:"
		"5,2,128,0,0,0,0,1,2,"
		".5,56,1,1,0,0,2,2:"
		"6,2,86,1,1,0,0,1,2,"
		".5,24,0,0,0,0,2,2:"
		"7,2,48,1,.5,0,0,1,2,"
		".5,96,0,.5,1,1,1,2:8,"


	};
}
void instrument::init_al() {
	ALCdevice* dev = NULL;
	ALCcontext* ctx = NULL;

	const char* defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	std::cout << "Default device: " << defname << std::endl;

	dev = alcOpenDevice(defname);
	ctx = alcCreateContext(dev, NULL);
	alcMakeContextCurrent(ctx);
}

void instrument::exit_al() {
	ALCdevice* dev = NULL;
	ALCcontext* ctx = NULL;
	ctx = alcGetCurrentContext();
	dev = alcGetContextsDevice(ctx);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);
}