#ifndef SYNTHS_H_INCLUDED
#define SYNTHS_H_INCLUDED
#include<windows.h>
#include <stdlib.h>
#include<vector>
#include<GL/glui.h>
#include<GL/glut.h>
#include <al.h>
#include <alc.h>
#include <alut.h>
using namespace std;
template< class T >
class reference_wrapper;
class synthpanel{
    public:
        void play();
        void stop();
        void pKeys();
        void getWaves();
        void dispValues();
        void getVisualArgs();
        float vol, fLow, fHigh, res;
        float track,tempo;
        int scale, seq;
        float verts, yRes, xRes, sX,sY, rx,ry,rz, r,g,b, fade;
        bool linear, dim2;
        ALuint soundstream;
        std::string name;
        std::vector<vector<float> > waves;
        std::vector<vector<float> >seqNotes;
        std::vector<vector<vector<float> > >seqNoteParams;
        std::vector<float>audioData;
};

#endif // SYNTHS_H_INCLUDED
