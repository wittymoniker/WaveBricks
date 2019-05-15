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
        static float track,tempo;
        static float scale, seq, rate;
        float verts, yRes, xRes, zRes, sX,sY,sZ, rx,ry,rz, rox,roy,roz, r,g,b, fade;
        bool linear, dim2;
        static std::vector<float> song;
        //static ALuint soundstream;
        //static ALuint notestream;  stream in main
        static std::vector<float> note;
        static std::string name;
        static std::vector<vector <float> > waves;
        static std::vector<vector<float> >seqAmp;
        static std::vector<float>seqNotes;
        static std::vector<vector<vector<float> > >seqNoteParams;
        static std::vector<float>vPitches;
        static std::vector<float>vAmplitudes;
        static std::vector<float>vWaveform;
        void play(){

        }
        void stop(){

        }
        void pKeys(){

        }
        void getTrack(){

        }
        void defNote(){

        }
        void getObjFromNote(){

        }
        vector<float> getNote(){
            for(int o=0;o<=synthpanel::seqNotes.size();o++)
            for (int i=0; i<=(synthpanel::rate*(synthpanel::tempo/60));i++){

                synthpanel::song[o*(synthpanel::rate/(synthpanel::tempo/60))+i]=
                (float)synthpanel::note[(32768.0f)*(float)(synthpanel::seqNotes[o]) *(float)(i/(synthpanel::rate/(synthpanel::tempo/60)))];
            }
            return synthpanel::note;
        }
        void getNoteFromObj(){
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

};

#endif // SYNTHS_H_INCLUDED
