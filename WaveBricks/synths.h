#ifndef SYNTHS_H_INCLUDED
#define SYNTHS_H_INCLUDED
#include<windows.h>
#include <stdlib.h>
#include<vector>
#include<GL/glui.h>
#include<GL/glut.h>

#ifdef LIBAUDIO
#include <audio/wave.h>
#define BACKEND	"libaudio"
#else
#endif
//#include "main.cpp"
using namespace std;
template< class T >
class reference_wrapper;
class synthpanel{
    public:
        float vol, fLow, fHigh, res, stereo;
        float track,tempo;
        float scale, seq, rate;
        float verts, yRes, xRes, zRes, sX,sY,sZ, rx,ry,rz, rox,roy,roz, r,g,b, fade;
        bool linear, dim2;
        std::vector<float> song;
        //static ALuint soundstream;
        //static ALuint notestream;  stream in main
        std::vector<float> note;
        std::vector<vector <float> > waves;
        std::vector<vector<float> >seqAmp;
        std::vector<float>seqNotes;
        std::vector<vector<vector<float> > >seqNoteParams;
        std::vector<float>vPitches;
        std::vector<float>vAmplitudes;
        std::vector<float>vWaveform;

        void play(synthpanel synth);
        void stop(synthpanel synth);
        void pKeys(synthpanel synth);
        void getTrack(synthpanel synth);
        void defNote(synthpanel synth);
        void getObjFromNote(synthpanel synth);
        void getNote(synthpanel synth);
        void getNoteFromObj(synthpanel synth);
        void dispValues(synthpanel synth);
        void getVisualArgs(synthpanel synth);


};

#endif // SYNTHS_H_INCLUDED
