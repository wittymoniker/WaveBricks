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


