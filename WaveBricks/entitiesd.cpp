#pragma once
#include "entities.cpp"


void instrument::assembleVoices() {
	instrument::breakpoints = {};
	int last = 0;
	for (int i = 1; i < instrument::stepvoices.size(); i++) {
		if (!instrument::stepvoices[i].empty()) {
			if (!instrument::stepvoices.at(i).at(2).empty()) {
				instrument::breakpoints.resize(instrument::breakpoints.size() + 1);
				instrument::breakpoints[instrument::breakpoints.size() - 1].resize(i + 1);
				instrument::breakpoints[instrument::breakpoints.size() - 1][i].resize(3);
				instrument::breakpoints[instrument::breakpoints.size() - 1][i][0].resize(instrument::voices_spinner);
				instrument::breakpoints[instrument::breakpoints.size() - 1][i][1].resize(instrument::voices_spinner);
				instrument::breakpoints[instrument::breakpoints.size() - 1][i][2].resize(instrument::voices_spinner);
				instrument::breakpoints.at(instrument::breakpoints.size() - 1).at(i) = (instrument::stepvoices.at(i));
			}
		}
	}
	for (int ir = 1; ir < instrument::breakpoints.size(); ir++) {
		int lastBreak = 0;
		for (int iu = instrument::breakpoints[lastBreak].size(); iu < instrument::breakpoints[ir].size(); iu++) {
			instrument::stepvoices[iu].resize(3);
			instrument::stepvoices[iu][0].resize(voices_spinner);
			instrument::stepvoices[iu][1].resize(voices_spinner);
			instrument::stepvoices[iu][2].resize(voices_spinner);
			for (int iy = 0; iy < instrument::breakpoints[ir][iu].size() && iy < instrument::stepvoices[iu][2].size(); iy++) {
				for (int i = 0; i < instrument::voices_spinner; i++) {
					instrument::stepvoices.at(iu).at(iy).at(i) = (((instrument::breakpoints[ir][instrument::breakpoints[ir].size() - 1][iy][i] / (instrument::breakpoints[ir][instrument::breakpoints[ir].size() - 1][iy][i]
						- instrument::breakpoints[lastBreak][instrument::breakpoints[lastBreak].size() - 1][iy][i])))
						* instrument::stepvoices.at(lastBreak).at(iy).at(i))
						+ (((((instrument::breakpoints[ir][instrument::breakpoints[ir].size() - 1][iy][i]) / instrument::breakpoints[ir][instrument::breakpoints[ir].size() - 1][iy][i])
							/ instrument::breakpoints[ir][instrument::breakpoints[ir].size() - 1][iy][i])) * (instrument::stepvoices.at(iu).at(iy).at(i)));
				}
			}

		}
		if (ir > 0) {
			lastBreak = ir - 1;
		}
	}
	if (instrument::breakpoints.size() == 0) {
		instrument::stepvoices.resize(instrument::composition.size());
		for (int i = 0; i < instrument::stepvoices.size(); i++) {
			instrument::stepvoices[i] = instrument::stepvoices[0];
		}
	}

	last = 1;
	if (instrument::decaystep.size() < instrument::composition.size()) {
		instrument::decaystep.resize(instrument::composition.size());
	}
	for (int i = 0; i < instrument::decaystep.size(); i++) {

		if (!instrument::decaystep.at(i)) {
			instrument::decaystep.at(i) = last;
		}
		else {
			int last = instrument::decaystep.at(i);
		}
	}
	if (instrument::stepvoices.at(instrument::currentStep).size() >= 3) {
		instrument::voicesamp.resize(instrument::stepvoices.at(instrument::currentStep).at(0).size() + 1);
		instrument::voicespitch.resize(instrument::stepvoices.at(instrument::currentStep).at(1).size() + 1);
		instrument::voicesphase.resize(instrument::stepvoices.at(instrument::currentStep).at(2).size() + 1);
		instrument::voicesamp = instrument::stepvoices.at(instrument::currentStep).at(0);
		instrument::voicespitch = instrument::stepvoices.at(instrument::currentStep).at(1);
		instrument::voicesphase = instrument::stepvoices.at(instrument::currentStep).at(2);
	}

}

void instrument::assemble() {
	//cout  << "assemble instrument" ;
	initVals();
	glutInitWindowSize(700, 800);
	
	instrument::wavebricks_synth = glutCreateWindow("Wavebricks Synth");
	//glutDisplayFunc(display);



	instrument::synth_panel = GLUI_Master.create_glui_subwindow(wavebricks_synth);
	instrument::syn_panel = synth_panel->add_panel("Synth Panel");
	//GLuint synth_window= glutCreateWindow ("WaveBricks Instrument");
	//synth_panel->add_listbox_to_panel(syn_panel, "Construction Heuristic", heuristic_listbox );
	instrument::heuristic_listbox_panel = synth_panel->add_listbox_to_panel(instrument::syn_panel, "Construction Heuristic", &(instrument::heuristic_listbox), HEURISTIC_LISTBOX, instrument::glui_callback);
	instrument::heuristic_listbox_panel->add_item(1, "Vertice Voice 2d");//phase manipulation is rotation around shape, frequency is distance, amplitude contributes to distance between sister vertices
	instrument::heuristic_listbox_panel->add_item(2, "Vertice Voice 3d");//phase manipulation is rotation around an axis, frequency is one other axis, and amplitude another axis. octave or order or cycle per distance around shape
	instrument::heuristic_listbox_panel->add_item(3, "AFP XYZ 2d");//wave interfered across shape as oscilloscope, clipped at boundaries, FM by changing scanning location, 2d.
	instrument::heuristic_listbox_panel->add_item(4, "AFP XYZ  3d");//wave interfered across shape as oscilloscope, clipped at boundaries, FM by changing scanning location, 3d.


	instrument::panning_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Audio Panning(L/R)", GLUI_SPINNER_FLOAT, &(instrument::panning_spinner), PANNING_SPINNER, instrument::glui_callback);

	 instrument::xpos_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Shape Position X", GLUI_SPINNER_FLOAT, &(instrument::xpos_spinner), XPOS_SPINNER, instrument::glui_callback);
	instrument::ypos_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Shape Position Y", GLUI_SPINNER_FLOAT, &(instrument::ypos_spinner), YPOS_SPINNER, instrument::glui_callback);
	instrument::zpos_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Shape Position Z", GLUI_SPINNER_FLOAT, &(instrument::zpos_spinner), ZPOS_SPINNER, instrument::glui_callback);

	instrument::xmod_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "X Mod", GLUI_SPINNER_FLOAT, &(instrument::xmod_spinner), XMOD_SPINNER, instrument::glui_callback);
	instrument::ymod_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Y Mod", GLUI_SPINNER_FLOAT, &(instrument::ymod_spinner), YMOD_SPINNER, instrument::glui_callback);
	instrument::zmod_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Z Mod", GLUI_SPINNER_FLOAT, &(instrument::zmod_spinner), ZMOD_SPINNER, instrument::glui_callback);


	instrument::voices_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Voices Number", GLUI_SPINNER_INT, &(instrument::voices_spinner), VOICES_SPINNER, instrument::glui_callback);

	instrument::scale_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Scale", GLUI_SPINNER_FLOAT, &(instrument::scale_spinner), SCALE_SPINNER, instrument::glui_callback);

	instrument::r_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Red", GLUI_SPINNER_FLOAT, &(instrument::r_spinner), R_SPINNER, instrument::glui_callback);
	instrument::g_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Green", GLUI_SPINNER_FLOAT, &(instrument::g_spinner), G_SPINNER, instrument::glui_callback);
	instrument::b_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Blue", GLUI_SPINNER_FLOAT, &(instrument::b_spinner), B_SPINNER, instrument::glui_callback);

	instrument::r_mod_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Red Mod", GLUI_SPINNER_FLOAT, &(instrument::r_spinner), R_SPINNER, instrument::glui_callback);
	instrument::g_mod_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Green Mod", GLUI_SPINNER_FLOAT, &(instrument::g_spinner), G_SPINNER, instrument::glui_callback);
	instrument::b_mod_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Blue Mod", GLUI_SPINNER_FLOAT, &(instrument::b_spinner), B_SPINNER, instrument::glui_callback);


	instrument::phaserot_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Phase Vertice Rotation Influence", GLUI_SPINNER_FLOAT, &(instrument::phaserot_spinner), PHASEROT_SPINNER, instrument::glui_callback);
	instrument::phasecolor_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Phase Color Influence", GLUI_SPINNER_FLOAT, &(instrument::phasecolor_spinner), PHASECOLOR_SPINNER, instrument::glui_callback);
	instrument::phasescale_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Phase Scale Influence", GLUI_SPINNER_FLOAT, &(instrument::phasescale_spinner), PHASESCALE_SPINNER, instrument::glui_callback);
	instrument::ampcolor_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Amplitude Color Influence", GLUI_SPINNER_FLOAT, &(instrument::ampcolor_spinner), AMPCOLOR_SPINNER, instrument::glui_callback);
	instrument::pitchcolor_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Pitch Color Influence", GLUI_SPINNER_FLOAT, &(instrument::pitchcolor_spinner), PITCHCOLOR_SPINNER, instrument::glui_callback);
	instrument::ampscale_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Amplitude Scale Influence", GLUI_SPINNER_FLOAT, &(instrument::ampscale_spinner), AMPSCALE_SPINNER, instrument::glui_callback);
	instrument::pitchscale_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Pitch Scale Influence", GLUI_SPINNER_FLOAT, &(instrument::pitchscale_spinner), PITCHSCALE_SPINNER, instrument::glui_callback);
	instrument::pitchrot_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Pitch Rotation Influence", GLUI_SPINNER_FLOAT, &(instrument::pitchrot_spinner), PITCHROT_SPINNER, instrument::glui_callback);
	instrument::amprot_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Amplitude Rotation Influence", GLUI_SPINNER_FLOAT, &(instrument::amprot_spinner), AMPROT_SPINNER, instrument::glui_callback);
	instrument::fm_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Frequency Modulation Frequency", GLUI_SPINNER_FLOAT, &(instrument::fm_spinner), FM_SPINNER, instrument::glui_callback);
	instrument::fmint_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Frequency Modulation Intensity", GLUI_SPINNER_FLOAT, &(instrument::fmint_spinner), FMINT_SPINNER, instrument::glui_callback);
	instrument::am_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Amplitude Modulation Frequency", GLUI_SPINNER_FLOAT, &(instrument::am_spinner), AM_SPINNER, instrument::glui_callback);
	instrument::amint_spinner_panel = synth_panel->add_spinner_to_panel(instrument::syn_panel, "Amplitude Modulation Intensity", GLUI_SPINNER_FLOAT, &(instrument::amint_spinner), AMINT_SPINNER, instrument::glui_callback);

	/*
	 GLUI_Spinner *hpfilterscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "HP Filter Scale Influence", GLUI_SPINNER_FLOAT, &hpfilterscale_spinner, HPFILTERSCALE_SPINNER, glui_callback);
	 GLUI_Spinner *lpfilterscale_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "LP Filter Scale Influence", GLUI_SPINNER_FLOAT, &lpfilterscale_spinner, LPFILTERSCALE_SPINNER, glui_callback);
	 GLUI_Spinner *hpfiltercolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "HP Filter Color Influence", GLUI_SPINNER_FLOAT, &hpfiltercolor_spinner, HPFILTERCOLOR_SPINNER, glui_callback);
	 GLUI_Spinner *lpfiltercolor_spinner_panel = synth_panel->add_spinner_to_panel(syn_panel, "LP Filter Color Influence", GLUI_SPINNER_FLOAT, &lpfiltercolor_spinner, LPFILTERCOLOR_SPINNER, glui_callback);
 */
 //script so users can define the sine voices differences across a song, or set them steady(see spinners)
	instrument::voicesscript_panel = synth_panel->add_edittext_to_panel(instrument::syn_panel, "Voices and Voice Automation Script:"
		, instrument::voiceautomation_script, VOICEAUTOMATION_SCRIPT, instrument::glui_callback);
	//script so users can define composition for song along tracking by BPM
	instrument::compositionscript_panel = synth_panel->add_edittext_to_panel(instrument::syn_panel, "Composition script:"
		, instrument::composition_script, COMPOSITION_SCRIPT, instrument::glui_callback);


	instrument::decayscript_panel = synth_panel->add_edittext_to_panel(instrument::syn_panel, "Decay script:"
		, instrument::decay_script, DECAY_SCRIPT, instrument::glui_callback);

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

	instrument::voicesscript_panel->set_h(20);
	instrument::voicesscript_panel->set_w(650);

	instrument::compositionscript_panel->set_h(20);
	instrument::compositionscript_panel->set_w(650);

	instrument::decayscript_panel->set_h(20);
	instrument::decayscript_panel->set_w(650);

	/*    envelopescript_panel->set_h(15);
		envelopescript_panel->set_w(200);

		filterscript_panel->set_h(15);
		filterscript_panel->set_w(200);

		colorscript_panel->set_h(15);
		colorscript_panel->set_w(200);*/

		//apmscript_panel->set_h(20);
		//apmscript_panel->set_w(200);


	instrument::synth_panel->set_main_gfx_window(wavebricks_synth);

	GLUI_Button* exitinst_button = synth_panel->add_button_to_panel(syn_panel, "Delete Instrument", DESTROY_BUTTON, glui_callback);


	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
}
void instrument::updateVoices() {
	instrument::decaystep = {};
	instrument::voicesamp = {};
	instrument::voicesphase = {};
	instrument::voicespitch = {};
	instrument::stepvoices = {};
	instrument::compamp = {};
	instrument::comppitch = {};
	instrument::composition = {};
	std::string tempNumber;//
	instrument::stepvoices.resize(1);
	instrument::composition.resize(1);
	char comma = ',';
	char colon = ':';
	std::string placement = "amp";
	float step = 0;
	for (unsigned i = 0; i < instrument::voiceautomation_script.length(); i++) {//voices script interpreter

		if (instrument::voiceautomation_script[i] != colon && instrument::voiceautomation_script[i] != comma) {
			tempNumber = tempNumber + (instrument::voiceautomation_script[i]);
			//cout<<voiceautomation_script.at(i);
			//cout<<"appended tempNumber" +tempNumber;
			//cout<<atof(tempNumber);
		}
		else {
			//cout <<"else";
			if (instrument::voiceautomation_script[i] == colon) {
				//cout<<colon;
				if (placement == "amp" && tempNumber.length() > 0) {
					instrument::voicesamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";

				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					instrument::voicespitch.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "phase";
				}
				if (placement == "phase" && tempNumber.length() > 0) {
					instrument::voicesphase.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "getNewStep";

				}

			}
			if (instrument::voiceautomation_script.at(i) == comma) {
				if (placement == "phase" && tempNumber.length() > 0) {
					instrument::voicesphase.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "amp";
				}
				if (placement == "amp" && tempNumber.length() > 0) {
					instrument::voicesamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";
				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					instrument::voicespitch.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "phase";
				}
				if (placement == "getNewStep" && tempNumber.length() > 0) {
					instrument::stepvoices[step].push_back(instrument::voicesamp);
					instrument::stepvoices[step].push_back(instrument::voicespitch);
					instrument::stepvoices[step].push_back(instrument::voicesphase);
					//cout<<(atof(tempNumber.c_str()));
					step = (atof(tempNumber.c_str()));
					instrument::stepvoices.resize(step + 1);

					instrument::voicesamp = {};
					instrument::voicespitch = {};
					instrument::voicesphase = {};
					tempNumber = "";
					placement = "amp";

				}
			}
		}

	}
	if (placement == "phase" && tempNumber.length() > 0) {
		instrument::voicesphase.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "amp";
	}
	if (placement == "amp" && tempNumber.length() > 0) {
		instrument::voicesamp.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "pitch";
	}
	if (placement == "pitch" && tempNumber.length() > 0) {
		instrument::voicespitch.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "phase";
	}
	if (placement == "getNewStep" && tempNumber.length() > 0) {
		instrument::stepvoices[step].push_back(instrument::voicesamp);
		instrument::stepvoices[step].push_back(instrument::voicespitch);
		instrument::stepvoices[step].push_back(instrument::voicesphase);
		//cout<<(atof(tempNumber.c_str()));
		step = (atof(tempNumber.c_str()));
		instrument::stepvoices.resize(step + 1);

		instrument::voicesamp = {};
		instrument::voicespitch = {};
		instrument::voicesphase = {};
		tempNumber = "";
		placement = "amp";

	}

	placement = "amp";
	step = 0;
	for (unsigned i = 0; i < instrument::composition_script.length(); i++) {//composition script interpreter
		if (instrument::composition_script.at(i) != colon && instrument::composition_script[i] != comma) {
			tempNumber = tempNumber + (instrument::composition_script[i]);
			//cout<<"appended tempNumber" +tempNumber;
		}
		else {
			//cout<<"else";
			if (instrument::composition_script.at(i) == colon) {
				//cout<<colon;
				if (placement == "amp" && tempNumber.length() > 0) {
					instrument::compamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";
				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					instrument::comppitch.push_back(atof(tempNumber.c_str()));
					//cout<<comppitch.at(0);
					tempNumber = "";
					placement = "getNewStep";
				}


			}
			if (composition_script.at(i) == comma) {
				//cout<<comma;
				if (placement == "getNewStep" && tempNumber.length() > 0) {
					instrument::composition[step].push_back(instrument::compamp);
					instrument::composition[step].push_back(instrument::comppitch);
					step = (atof(tempNumber.c_str()));
					instrument::composition.resize(step + 1);


					instrument::compamp = {};
					instrument::comppitch = {};
					tempNumber = "";
					placement = "amp";

				}
				if (placement == "amp" && tempNumber.length() > 0) {
					instrument::compamp.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "pitch";
				}
				if (placement == "pitch" && tempNumber.length() > 0) {
					instrument::comppitch.push_back(atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "amp";
				}

			}
		}
	}
	if (placement == "getNewStep" && tempNumber.length() > 0) {
		instrument::composition[step].push_back(compamp);
		instrument::composition[step].push_back(comppitch);
		step = (atof(tempNumber.c_str()));
		instrument::composition.resize(step + 1);


		instrument::compamp = {};
		instrument::comppitch = {};
		tempNumber = "";
		placement = "amp";

	}
	if (placement == "amp" && tempNumber.length() > 0) {
		instrument::compamp.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "pitch";
	}
	if (placement == "pitch" && tempNumber.length() > 0) {
		instrument::comppitch.push_back(atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "amp";
	}


	instrument::decaystep.resize(1);
	placement = "decay";
	step = 0;
	for (unsigned i = 0; i < instrument::decay_script.length(); i++) {//decay script interpreter
		if (instrument::decay_script.at(i) != colon && instrument::decay_script[i] != comma) {
			tempNumber = tempNumber + (instrument::decay_script[i]);
			//cout<<"appended tempNumber" +tempNumber;
		}
		else {
			if (instrument::decay_script.at(i) == colon) {
				//cout<<colon;
				if (placement == "decay" && tempNumber.length() > 0) {
					instrument::decaystep[step] = (atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "step";
				}
				if (placement == "step" && tempNumber.length() > 0) {
					step = (atof(tempNumber.c_str()));
					instrument::decaystep.resize(step + 1);
					tempNumber = "";
					placement = "decay";
				}

			}
			if (instrument::decay_script.at(i) == comma) {
				//cout<<comma;
				if (placement == "decay" && tempNumber.length() > 0) {
					instrument::decaystep[step] = (atof(tempNumber.c_str()));
					tempNumber = "";
					placement = "step";
				}
				if (placement == "step" && tempNumber.length() > 0) {
					step = (atof(tempNumber.c_str()));
					instrument::decaystep.resize(step + 1);
					tempNumber = "";
					placement = "decay";
				}
			}
		}
	}
	if (placement == "decay" && tempNumber.length() > 0) {
		instrument::decaystep[step] = (atof(tempNumber.c_str()));
		tempNumber = "";
		placement = "step";
	}
	if (placement == "step" && tempNumber.length() > 0) {
		step = (atof(tempNumber.c_str()));
		instrument::decaystep.resize(step + 1);
		tempNumber = "";
		placement = "decay";
	}



}



void instrument::render() {
	glPatchParameteri(GL_PATCH_VERTICES, instrument::voices_spinner);
	glPushMatrix();
	//glPatchParameteri(GL_PATCH_VERTICES,voices_spinner);
	//glTranslatef(0.0f, 0.0f, -7.0f);
	glBegin(GL_TRIANGLES);
	instrument::instrumentPoly.resize(instrument::voices_spinner);
	for (int i = 0; i < instrument::voices_spinner; i++) {
		instrument::instrumentPoly[i].resize(6);
	}
	instrument::updateVoices();
	instrument::assembleVoices();
	// //glLoadIdentity();

	for (int i = 0; i < instrument::voices_spinner; i++) {
		instrument::voicesamp[i] = instrument::stepvoices[instrument::currentStep][0][i];
		instrument::voicespitch[i] = instrument::stepvoices[instrument::currentStep][1][i];
		instrument::voicesphase[i] = instrument::stepvoices[instrument::currentStep][2][i];
		//cout<<"\nvoicespitch phase amp "<<" " <<voicesamp[i]<< " "<<voicespitch[i]<<" "<<voicesphase[i]<<" "<<heuristic_listbox<<"\n";
	}
	if (instrument::heuristic_listbox = 1 && instrument::voicesphase.size() >= instrument::voices_spinner && instrument::voicesamp.size() >= instrument::voices_spinner && instrument::composition[instrument::currentStep].size() >= 2 && instrument::voicespitch.size() >= instrument::voices_spinner) {//2d shape
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][0].size(); iy++) {
				instrument::voicesamp[i] += instrument::composition[instrument::currentStep][0][iy];
				instrument::voicesamp[i] += instrument::voicesamp[i] * sin(instrument::currentStep * 2.0 * instrument::PI * instrument::am_spinner) * instrument::amint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][1].size(); iy++) {
				instrument::voicespitch[i] += instrument::voicespitch[i] * sqrt(instrument::composition[instrument::currentStep][1][iy]) / 1024;
				instrument::voicespitch[i] += instrument::voicespitch[i] * sin(instrument::currentStep * 2.0 * PI * instrument::fm_spinner) * instrument::fmint_spinner;
				//cout<<"\nvoicespitch phase amp "<<" " <<voicesamp[i]<< " "<<voicespitch[i]<<" "<<voicesphase[i]<<"\n";
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			//TODO: set voice values all to 1 unless being played, wherat custom values proclaimed
			instrument::instrumentPoly[i][0] = (GLfloat)((instrument::xpos_spinner + (instrument::xmod_spinner * instrument::pitchscale_spinner * instrument::ampscale_spinner * instrument::phasescale_spinner))) * instrument::voicesamp[i] * instrument::voicespitch[i] * instrument::voicesphase[i] + instrument::voicesamp[i] + instrument::voicespitch[i] + instrument::voicesphase[i];
			instrument::instrumentPoly[i][1] = (GLfloat)((instrument::ypos_spinner + (instrument::ymod_spinner * instrument::pitchscale_spinner))) * instrument::voicespitch[i] + instrument::voicespitch[i];

			instrument::instrumentPoly[i][2] = (GLfloat)((instrument::zpos_spinner)) + instrument::voicesamp[i];

			instrument::instrumentPoly[i][3] = (GLfloat)(1.0 / (instrument::r_spinner / (instrument::r_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][4] = (GLfloat)(1.0 / (instrument::g_spinner / (instrument::g_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][5] = (GLfloat)(1.0 / (instrument::b_spinner / (instrument::b_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			if (instrument::instrumentPoly[i][3] < 0) {
				instrument::instrumentPoly[i][3] = (GLfloat)0 - instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][3] > 1) {
				instrument::instrumentPoly[i][3] = (GLfloat)1 / instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][4] < 0) {
				instrument::instrumentPoly[i][4] = (GLfloat)0 - instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][4] > 1) {
				instrument::instrumentPoly[i][4] = (GLfloat)1 / instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][5] < 0) {
				instrument::instrumentPoly[i][5] = (GLfloat)0 - instrument::instrumentPoly[i][5];
			}
			if (instrument::instrumentPoly[i][5] > 1) {
				instrument::instrumentPoly[i][5] = (GLfloat)1 / instrument::instrumentPoly[i][5];
			}
			glColor3f((GLfloat)instrument::instrumentPoly[i][3], (GLfloat)instrument::instrumentPoly[i][4], (GLfloat)instrument::instrumentPoly[i][5]);
			//cout << (GLfloat)instrument::instrumentPoly[i][3] << " " << (GLfloat)instrument::instrumentPoly[i][4] << " " << (GLfloat)instrument::instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)instrument::instrumentPoly[i][0], (GLfloat)instrument::instrumentPoly[i][1], (GLfloat)instrument::instrumentPoly[i][2]);
			//cout << (GLfloat)instrument::instrumentPoly[i][0] << " " << (GLfloat)instrument::instrumentPoly[i][1] << " " << (GLfloat)instrument::instrumentPoly[i][2] << " VERTS\n";

		}

	}
	if (instrument::heuristic_listbox = 2 && instrument::voicesphase.size() >= instrument::voices_spinner && instrument::voicesamp.size() >= instrument::voices_spinner && instrument::composition[instrument::currentStep].size() >= 2 && instrument::voicespitch.size() >= instrument::voices_spinner) {//3d shape
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][0].size(); iy++) {
				instrument::voicesamp[i] += instrument::composition[currentStep][0][iy];
				instrument::voicesamp[i] += instrument::voicesamp[i] * sin(instrument::currentStep * 2.0 * instrument::PI * instrument::am_spinner) * instrument::amint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][1].size(); iy++) {
				instrument::voicespitch[i] += voicespitch[i] * sqrt(composition[currentStep][1][iy]) / 1024;
				voicespitch[i] += voicespitch[i] * sin(currentStep * 2.0 * PI * fm_spinner) * fmint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			instrument::instrumentPoly[i][0] = (GLfloat)((instrument::xpos_spinner + (instrument::xmod_spinner * instrument::pitchscale_spinner * instrument::ampscale_spinner * instrument::phasescale_spinner))) * instrument::voicesamp[i] * instrument::voicespitch[i] * instrument::voicesphase[i] + instrument::voicesamp[i] + instrument::voicespitch[i] + instrument::voicesphase[i];
			instrument::instrumentPoly[i][1] = (GLfloat)((instrument::ypos_spinner + (instrument::ymod_spinner * instrument::pitchscale_spinner))) * instrument::voicespitch[i] + instrument::voicespitch[i];
			instrument::instrumentPoly[i][2] = (GLfloat)((instrument::zpos_spinner + (instrument::zmod_spinner * instrument::pitchscale_spinner * instrument::ampscale_spinner))) * instrument::voicesamp[i] * instrument::voicespitch[i] + instrument::voicesamp[i] + instrument::voicespitch[i];

			instrument::instrumentPoly[i][3] = (GLfloat)(1.0 / (instrument::r_spinner / (instrument::r_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][4] = (GLfloat)(1.0 / (instrument::g_spinner / (instrument::g_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][5] = (GLfloat)(1.0 / (instrument::b_spinner / (instrument::b_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			if (instrument::instrumentPoly[i][3] < 0) {
				instrument::instrumentPoly[i][3] = (GLfloat)0 - instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][3] > 1) {
				instrument::instrumentPoly[i][3] = (GLfloat)1 / instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][4] < 0) {
				instrument::instrumentPoly[i][4] = (GLfloat)0 - instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][4] > 1) {
				instrument::instrumentPoly[i][4] = (GLfloat)1 / instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][5] < 0) {
				instrument::instrumentPoly[i][5] = (GLfloat)0 - instrument::instrumentPoly[i][5];
			}
			if (instrument::instrumentPoly[i][5] > 1) {
				instrument::instrumentPoly[i][5] = (GLfloat)1 / instrument::instrumentPoly[i][5];
			}
			glColor3f((GLfloat)instrument::instrumentPoly[i][3], (GLfloat)instrument::instrumentPoly[i][4], (GLfloat)instrument::instrumentPoly[i][5]);
			//cout << (GLfloat)instrument::instrumentPoly[i][3] << " " << (GLfloat)instrument::instrumentPoly[i][4] << " " << (GLfloat)instrument::instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)instrument::instrumentPoly[i][0], (GLfloat)instrument::instrumentPoly[i][1], (GLfloat)instrument::instrumentPoly[i][2]);
			//cout << (GLfloat)instrument::instrumentPoly[i][0] << " " << (GLfloat)instrument::instrumentPoly[i][1] << " " << (GLfloat)instrument::instrumentPoly[i][2] << " VERTS\n";
		}
	}
	if (instrument::heuristic_listbox = 3 && instrument::voicesphase.size() >= instrument::voices_spinner && instrument::voicesamp.size() >= instrument::voices_spinner && instrument::composition[instrument::currentStep].size() >= 2 && instrument::voicespitch.size() >= instrument::voices_spinner) {//2d interfere
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][0].size(); iy++) {
				instrument::voicesamp[i] += instrument::composition[instrument::currentStep][0][iy];
				instrument::voicesamp[i] += instrument::voicesamp[i] * sin(instrument::currentStep * 2.0 * instrument::PI * instrument::am_spinner) * instrument::amint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][1].size(); iy++) {
				instrument::voicespitch[i] += instrument::voicespitch[i] * sqrt(instrument::composition[instrument::currentStep][1][iy]) / 1024;
				instrument::voicespitch[i] += instrument::voicespitch[i] * sin(instrument::currentStep * 2.0 * instrument::PI * instrument::fm_spinner) * instrument::fmint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			//TODO: set voice values all to 1 unless being played, wherat custom values proclaimed
			instrument::instrumentPoly[i][0] = (GLfloat)((instrument::xpos_spinner + (instrument::xmod_spinner * instrument::pitchscale_spinner) +
				instrument::xpos_spinner + (instrument::xmod_spinner * instrument::pitchscale_spinner) *
				instrument::scale_spinner * instrument::xmod_spinner * sin((i / instrument::voices_spinner) * instrument::xmod_spinner * (instrument::voicespitch.at(i) * instrument::pitchrot_spinner))));
			instrument::instrumentPoly[i][1] = (GLfloat)((instrument::ypos_spinner + (instrument::ymod_spinner * instrument::ampscale_spinner) +
				instrument::ypos_spinner + (instrument::ymod_spinner * instrument::ampscale_spinner) *
				instrument::scale_spinner * instrument::ymod_spinner * cos((i / instrument::voices_spinner) * instrument::ymod_spinner * (instrument::voicesamp.at(i) * instrument::amprot_spinner)) *
				(instrument::ampscale_spinner * instrument::voicesamp[i])));
			instrument::instrumentPoly[i][2] = (GLfloat)((instrument::zpos_spinner));

			instrument::instrumentPoly[i][3] = (GLfloat)(1.0 / (instrument::r_spinner / (instrument::r_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					voicesphase.at(i)))));
			instrument::instrumentPoly[i][4] = (GLfloat)(1.0 / (instrument::g_spinner / (instrument::g_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][5] = (GLfloat)(1.0 / (instrument::b_spinner / (instrument::b_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			if (instrument::instrumentPoly[i][3] < 0) {
				instrument::instrumentPoly[i][3] = (GLfloat)0 - instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][3] > 1) {
				instrument::instrumentPoly[i][3] = (GLfloat)1 / instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][4] < 0) {
				instrument::instrumentPoly[i][4] = (GLfloat)0 - instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][4] > 1) {
				instrument::instrumentPoly[i][4] = (GLfloat)1 / instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][5] < 0) {
				instrument::instrumentPoly[i][5] = (GLfloat)0 - instrument::instrumentPoly[i][5];
			}
			if (instrument::instrumentPoly[i][5] > 1) {
				instrument::instrumentPoly[i][5] = (GLfloat)1 / instrument::instrumentPoly[i][5];
			}
			glColor3f((GLfloat)instrument::instrumentPoly[i][3], (GLfloat)instrument::instrumentPoly[i][4], (GLfloat)instrument::instrumentPoly[i][5]);
			//cout << (GLfloat)instrument::instrumentPoly[i][3] << " " << (GLfloat)instrument::instrumentPoly[i][4] << " " << (GLfloat)instrument::instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)instrument::instrumentPoly[i][0], (GLfloat)instrument::instrumentPoly[i][1], (GLfloat)instrument::instrumentPoly[i][2]);
			//cout << (GLfloat)instrument::instrumentPoly[i][0] << " " << (GLfloat)instrument::instrumentPoly[i][1] << " " << (GLfloat)instrument::instrumentPoly[i][2] << " VERTS\n";
		}
	}
	if (instrument::heuristic_listbox = 4 && instrument::voicesphase.size() >= instrument::voices_spinner && instrument::voicesamp.size() >= instrument::voices_spinner && instrument::composition[instrument::currentStep].size() >= 2 && instrument::voicespitch.size() >= instrument::voices_spinner) {//3d interfere
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][0].size(); iy++) {
				instrument::voicesamp[i] += instrument::composition[instrument::currentStep][0][iy];
				instrument::voicesamp[i] += instrument::voicesamp[i] * sin(instrument::currentStep * 2.0 * instrument::PI * instrument::am_spinner) * instrument::amint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			for (int iy = 0; iy < instrument::composition[instrument::currentStep][1].size(); iy++) {
				instrument::voicespitch[i] += instrument::voicespitch[i] * sqrt(instrument::composition[currentStep][1][iy]) / 1024;
				instrument::voicespitch[i] += instrument::voicespitch[i] * sin(instrument::currentStep * 2.0 * instrument::PI * instrument::fm_spinner) * instrument::fmint_spinner;
			}
		}
		for (int i = 0; i < instrument::voices_spinner; i++) {
			instrument::instrumentPoly[i][0] = (GLfloat)((instrument::xpos_spinner + (instrument::xmod_spinner * instrument::pitchscale_spinner) +
				instrument::xpos_spinner + (instrument::xmod_spinner * instrument::pitchscale_spinner) *
				instrument::scale_spinner * instrument::xmod_spinner * sin((i / instrument::voices_spinner) * instrument::xmod_spinner * (instrument::voicespitch.at(i) * instrument::pitchrot_spinner))));
			instrument::instrumentPoly[i][1] = (GLfloat)((instrument::ypos_spinner + (instrument::ymod_spinner * instrument::ampscale_spinner) +
				instrument::ypos_spinner + (instrument::ymod_spinner * instrument::ampscale_spinner) *
				instrument::scale_spinner * instrument::ymod_spinner * cos((i / instrument::voices_spinner) * instrument::ymod_spinner * (instrument::voicesamp.at(i) * instrument::amprot_spinner)) *
				(instrument::ampscale_spinner * instrument::voicesamp[i])));
			instrument::instrumentPoly[i][2] = (GLfloat)((instrument::zpos_spinner + (instrument::zmod_spinner * instrument::phasescale_spinner) +
				instrument::zpos_spinner + (instrument::zmod_spinner * instrument::phasescale_spinner) *
				instrument::scale_spinner * instrument::zmod_spinner * tan((i / instrument::voices_spinner) * instrument::zmod_spinner * (instrument::voicesphase.at(i) * instrument::phaserot_spinner))));

			instrument::instrumentPoly[i][3] = (GLfloat)(1.0 / (instrument::r_spinner / (instrument::r_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][4] = (GLfloat)(1.0 / (instrument::g_spinner / (instrument::g_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			instrument::instrumentPoly[i][5] = (GLfloat)(1.0 / (instrument::b_spinner / (instrument::b_mod_spinner * (instrument::pitchcolor_spinner * instrument::voicespitch.at(i)) *
				(instrument::ampcolor_spinner * instrument::voicesamp.at(i)) * (instrument::phasecolor_spinner *
					instrument::voicesphase.at(i)))));
			if (instrument::instrumentPoly[i][3] < 0) {
				instrument::instrumentPoly[i][3] = (GLfloat)0 - instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][3] > 1) {
				instrument::instrumentPoly[i][3] = (GLfloat)1 / instrument::instrumentPoly[i][3];
			}
			if (instrument::instrumentPoly[i][4] < 0) {
				instrument::instrumentPoly[i][4] = (GLfloat)0 - instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][4] > 1) {
				instrument::instrumentPoly[i][4] = (GLfloat)1 / instrument::instrumentPoly[i][4];
			}
			if (instrument::instrumentPoly[i][5] < 0) {
				instrument::instrumentPoly[i][5] = (GLfloat)0 - instrument::instrumentPoly[i][5];
			}
			if (instrument::instrumentPoly[i][5] > 1) {
				instrument::instrumentPoly[i][5] = (GLfloat)1 / instrument::instrumentPoly[i][5];
			}
			glColor3f((GLfloat)instrument::instrumentPoly[i][3], (GLfloat)instrument::instrumentPoly[i][4], (GLfloat)instrument::instrumentPoly[i][5]);
			//cout << (GLfloat)instrument::instrumentPoly[i][3] << " " << (GLfloat)instrument::instrumentPoly[i][4] << " " << (GLfloat)instrument::instrumentPoly[i][5] << " COLORS\n";
			glVertex3f((GLfloat)instrument::instrumentPoly[i][0], (GLfloat)instrument::instrumentPoly[i][1], (GLfloat)instrument::instrumentPoly[i][2]);
			//cout << (GLfloat)instrument::instrumentPoly[i][0] << " " << (GLfloat)instrument::instrumentPoly[i][1] << " " << (GLfloat)instrument::instrumentPoly[i][2] << " VERTS\n";
		}
	}
	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}







void instrument::assembleSongData() {
	instrument::samples = new ALshort[instrument::composition.size() * 2 * (22050 * (60 / (int)tempo))];
	instrument::init_al();
	instrument::updateVoices();
	instrument::assembleVoices();
	float bpm = instrument::tempo;
	//ALfloat *soundstream;
	ALuint srate = 22050;

	alGenBuffers(1, &(instrument::soundbuffer));

	//cout<<composition.size();
	instrument::audioout.open("audio.wav");
	cout << instrument::composition.size();
	for (int it = 0; it<instrument::composition.size() && it<instrument::stepvoices.size(); it++) {
		for (int iu = 0; iu < instrument::composition[it].size() && iu < instrument::stepvoices[it].size(); iu++) {
			for (int ii = 0; ii < instrument::stepvoices[it][iu].size() && it < instrument::composition[it][iu].size(); ii++) {
				for (int iy = 0; iy < instrument::composition[it][iu].size(); iy++) {
					for (int i = 0; i < instrument::voices_spinner; i++) {
						//cout<<it<<"\n";
						float amp = instrument::composition.at(it).at(iu).at(iy) * instrument::stepvoices[it][iu][i];
						float pitch = instrument::composition.at(it).at(iu).at(iy) * instrument::stepvoices[it][iu][i];
						float phase = instrument::stepvoices[it][iu][i];
						float decayf = instrument::decaystep.at(it);
						instrument::playVertice(instrument::samples, instrument::srate, instrument::pitch, instrument::amp, instrument::phase,
							instrument::decayf, instrument::tempo, instrument::amint_spinner, instrument::am_spinner, instrument::fmint_spinner, instrument::fm_spinner, it);
					}
				}
			}
		}
	}
	for (int i = 0; i < instrument::composition.size() * 2 * (22050 * (60 / (int)tempo)); i++) {
		instrument::audioout << instrument::samples[i];
	}
	instrument::audioout.close();


}
void instrument::playVertice(ALshort data[], float srate, float freq, float amp, float phase,
	float decayf, float bpm, float am, float amfreq, float fm, float fmfreq, float step) {
	float ampmult = 32.0f;
	float cycle = 2.0f;
	float minute = 60.0f;
	float i = 0.0f;
	float ampadj = ampmult * amp;
	float M_PI = instrument::PI;

	instrument::sizeSS = instrument::composition.size() * 2 * (22050 * (60 / (int)instrument::tempo));
	//data=data;
	for (int i = step * (22050 * (60 / instrument::tempo)); i < (step + (1.0 * decayf)) * (22050 * (60 / instrument::tempo)) && i < instrument::sizeSS; (i)++) {
		//cout<<"\nattempting transfer at "<<i;

		(instrument::samples[i]) += (short)(ampadj * (((sin(((freq * 2.0 * M_PI) / 22050 * i) * phase + ((freq * 2.0 * M_PI) / 22050 * i) * (fm * sin((fmfreq * 2.0 * M_PI) / 22050 * i))))
					+ (sin(((freq * 2.0 * M_PI) / 22050 * i) + ((freq * 2.0 * M_PI) / 22050 * i) * (fm * sin((fmfreq * 2.0 * M_PI) / 22050 * i))))
					* (sin((amfreq * 2.0 * M_PI) / 22050 * i) * am))));
		
		cout << samples[i];
	}

}
void instrument::play() {
	
	alBufferData(instrument::soundbuffer, AL_FORMAT_MONO16, &(instrument::samples), instrument::composition.size() * 2 * (22050 * (60 / (int)instrument::tempo)), (22050));
	alGenSources(1, &(instrument::soundsource));
	alSourcei(instrument::soundsource, AL_BUFFER, instrument::soundbuffer);
	alSourcePlay(instrument::soundsource);
	cout << "play";
	cout << "\nwrote composition\n";
	
	
}






void instrument::initVals() {
	instrument::tempo = 160.0;

	instrument::PI = 3.141592653589f;

	instrument::srate = 22050;
	instrument::soundsource;
	instrument::data_size;
	instrument::soundbuffer;
	instrument::soundstream;
	//float soundstreamvec[44100*60*5];


	instrument::currentStep = 0;
	instrument::mainboard_title = ((char*)"WaveBricks Synth");



	instrument::heuristic_listbox = 2;
	instrument::voices_spinner = 6;
	instrument::pitchscale_spinner = 0.5;
	instrument::pitchcolor_spinner = 0.5;
	instrument::pitchrot_spinner = 0.5;
	instrument::ampscale_spinner = 0.5;
	instrument::ampcolor_spinner = 0.5;
	instrument::amprot_spinner = 0.5;
	instrument::phaserot_spinner = 0.5;
	instrument::phasecolor_spinner = 0.5;
	instrument::phasescale_spinner = 0.5;
	instrument::xpos_spinner = 0.0;
	instrument::ypos_spinner = 0.0;
	instrument::zpos_spinner = 0.0;
	instrument::scale_spinner = 1.0;
	/*lpfiltercolor_spinner=0.5;
	hpfiltercolor_spinner=0.0;
	lpfilterscale_spinner=0.5;
	hpfilterscale_spinner=0.0;*/
	instrument::r_spinner = 0.5;
	instrument::g_spinner = 0.5;
	instrument::b_spinner = 0.5;
	instrument::r_mod_spinner = 0.5;
	instrument::g_mod_spinner = 0.5;
	instrument::b_mod_spinner = 0.5;
	instrument::xmod_spinner = 1.0;
	instrument::ymod_spinner = 1.0;
	instrument::zmod_spinner = 1.0;
	instrument::fm_spinner = 0.0;
	instrument::fmint_spinner = 1.0;
	instrument::am_spinner = 0.0;
	instrument::amint_spinner = 1.5;



	/*SCRIPTING
	*** REMEMBER: DELETE YOUR VOICES AUTOMATION SCRIPTS EVERY TIME YOU RESIZE THE INSTRUMENT VOICE COUNT.
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
	instrument::voiceautomation_script = { "1.0,1.5,0.5,"
							"1.3,1.3,0.2,"
							"1.2,0.8,.3,"
							"1.1,0.4,0.2,"
							"4.2,.02,0.7,"
							"3.0,1.25,0.4"
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
							"3,0.0274,0.4:129," };
	instrument::composition_script = { "2.0,3.0:"
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
						"129,3.0,5096:" };
	instrument::decay_script = { "1.3,0:"
				 "1.3,15:"
				 "1.3,23:"
				 "1.3,31:"
				 "1.3,47:"
				 "1.3,63:"
				 "1.3,85:"
				 "1.3,129:" };
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

void exit_al() {
	ALCdevice* dev = NULL;
	ALCcontext* ctx = NULL;
	ctx = alcGetCurrentContext();
	dev = alcGetContextsDevice(ctx);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);
}