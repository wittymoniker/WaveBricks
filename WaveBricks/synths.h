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
        static float rate;
        void play();
        void stop();
        void pKeys();
        void getWaves();
        void getNote();
        void dispValues();
        void getVisualArgs();
        float vol, fLow, fHigh, res;
        static float track,tempo;
        int scale, seq;
        float verts, yRes, xRes, zRes, sX,sY,sZ, rx,ry,rz, rox,roy,roz, r,g,b, fade;
        bool linear, dim2;
        static ALuint soundstream;
        static ALuint note[32000];
        static std::string name;
        static std::vector<vector <float> > waves;
        static std::vector<vector<float> >seqNotes;
        static std::vector<vector<vector<float> > >seqNoteParams;
        static std::vector<float>audioData;
};

#endif // SYNTHS_H_INCLUDED
