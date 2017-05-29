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
#include <al.h>
#include <alc.h>
#include <alut.h>

/*
        float vol, fLow, fHigh, res;
        float track,tempo;
        int scale, seq;
        float verts, yRes, xRes, sX,sY, rx,ry,rz, r,g,b, fade;
        bool linear, dim2;
        std::string name;
        std::vector<vector<float> > waves;
        std::vector<vector<float> >seqNotes;
        std::vector<vector<vector<float> > >seqNoteParams;
        std::vector<float>audioData;

        values to set: float verts, yRes, xRes, zRes, sX,sY,sZ, rx,ry,rz, rox,roy,roz, r,g,b, fade;
        bool linear, dim2;
*/
void play(bool button, int startSeq){
    if (button){
        alSourcePlay(synthpanel::soundstream);
    }
}
void stop(bool button){
    if(button){
        alSourceStop(synthpanel::soundstream);
    }
}
void pKeys(int key){

    alSourcei(*synthpanel::note, AL_LOOPING, 0);
    while(key!=0){
        alSourcei(*synthpanel::note, AL_LOOPING, 1);
    }
    alSourcePlay(*synthpanel::note);
}
void getWaves(){
    for(int o=0;o<=synthpanel::seqNotes.size();o++)
    for (int i=0; i<=synthpanel::rate/(synthpanel::tempo/60);i++){
        synthpanel::soundstream[o*(synthpanel::rate/(synthpanel::tempo/60))+i]=
        (float)(synthpanel::note[(32000)*(synthpanel::note)(i/(synthpanel::rate/(synthpanel::tempo/60)))])
    }
    return soundstream;
}
void getNote(){
    synthpanel::rate=44100;
    for (int i = 0; i<= synthpanel::waves.size();i++){
        for(int o=0; o<=32000; o++){
            synthpanel::note[o]+=synthpanel::waves[i][o];
        }
    }
}
void dispValues(){

}
void getVisualArgs(){

}
