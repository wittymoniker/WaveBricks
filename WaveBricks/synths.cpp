#include<windows.h>
#include<stdlib.h>
#include<vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include "GLUI/glui.h"
#else
#include <GL/glut.h>
#include "GL/glui.h"
#endif
#include"synths.h"

void synthpanel::getNote(synthpanel synth){
    for(int o=0;o<=synth.seqNotes.size();o++)
    for (int i=0; i<=(synth.rate*(synth.tempo/60));i++){

        synth.song[o*(synth.rate/(synth.tempo/60))+i]=
        (float)synth.note[(32768.0f)*(float)(synth.seqNotes[o]) *(float)(i/(synth.rate/(synth.tempo/60)))];
    }
}
void synthpanel::getNoteFromObj(synthpanel synth){
    synth.rate=44100;
    for (int i = 0; i<= synth.waves.size();i++){
        for(int o=0; o<=32000; o++){
            synth.note[o]+=synth.waves[i][o];
        }
    }
}
void synthpanel::dispValues(synthpanel synth){

}
void synthpanel::getVisualArgs(synthpanel synth){

}

        //values to set: float verts, yRes, xRes, zRes, sX,sY,sZ, rx,ry,rz, rox,roy,roz, r,g,b, fade;



