//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Feb  3 12:03:18 PST 2002
// Last Modified: Sun Aug 29 03:29:24 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/badsplice.cpp
// Syntax:        C++ 
//
// Description:   Demonstration of the SoundFileRead::gotoSample().
//                Chops up an input soundfile into little pieces and 
//                splices them together in a random sequence in the
//                output file.
//

#include "soundfile.h"
#include <stdlib.h>


#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif

#ifndef VISUAL
   #include <time.h>
#endif


int getRandomInt(int minvalue, int maxvalue);

//////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
   Options options;
   options.define("n|min=d:0.1 sec",      "minimum duration of a splice");
   options.define("x|max=d:1.0 sec",      "maximum duration of a splice");
   options.define("d|duration=d:5.0 sec", "duration of output file");
   options.define("q|quiet=b",            "supress printed information");
   options.process(argc, argv);
   if (options.getArgCount() != 2) {
      cout << "Usage: " << options.getCommand() 
           << " [-n min-splice][-x max-splice][-d duration] insound outsound" 
           << endl;
      exit(1);
   }

   SoundFileRead insound(options.getArg(1));
   insound.setLoopOn();
   SoundFileWrite outsound(options.getArg(2), insound);
   int channels = insound.getChannels();

   int minsamples = (int)(options.getDouble("min") * insound.getSrate() + 0.5);
   if (minsamples < 1) minsamples = 1;
   int maxsamples = (int)(options.getDouble("max") * insound.getSrate() + 0.5);
   if (maxsamples < 1) maxsamples = 1;
   if (minsamples > maxsamples) {
      int tempnum = minsamples;
      minsamples = maxsamples;
      maxsamples = tempnum;
   }
   int totalsamples = (int)(options.getDouble("duration") * 
         insound.getSrate() + 0.5);
   int quiet = options.getBoolean("quiet");
   int i, j;
   int samplecount = 0;
   int startsample = 0;
   int duration = 0;
   int splice = 0;


   while (samplecount < totalsamples) {
      startsample = getRandomInt(0, insound.getSamples());
      insound.gotoSample(startsample);
      duration = getRandomInt(minsamples, maxsamples);
      if (samplecount + duration > totalsamples) {
         duration = totalsamples - samplecount;
      }
      if (!quiet) {
         cout << splice++ << '\t' << startsample << '\t' << duration << '\n';
      }

      for (i=0; i<duration; i++) {
         for (j=0; j<channels; j++) {
            outsound.writeSampleDouble(insound.getCurrentSampleDouble(j));
         }
         insound.incrementSample(); 
      }
      samplecount += duration;
   }


   return 0;
}


//////////////////////////////////////////////////////////////////////////

//////////////////////////////
//
// getRandomInt -- return an random integer in the specified range
//

int getRandomInt(int minvalue, int maxvalue) {
   #ifdef VISUAL
      return rand() % (maxvalue + 1 - minvalue) + minvalue;
   #else
      static int init = 0;
      if (!init) {
         srand48(time(NULL));
         init = 1;
      }
      return (int)(drand48() * (maxvalue - minvalue) + minvalue + 0.5);
   #endif
}







// md5sum: 33e3183aee379ea9512683605a34d931 badsplice.cpp [20050403]
