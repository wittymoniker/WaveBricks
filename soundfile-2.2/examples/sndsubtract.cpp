//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Jan 23 21:58:50 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Filename:      ...soundfile/examples/sndsubtract.cpp
// Syntax:        C++ 
//
// Description:   subtract two sound files and store results in a third 
//                soundfile.  Input soundfiles are assumed to have the
//                same number of channels and ideally should have the
//                same length.
//

#include "soundfile.h"
#include <stdlib.h>

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif


int main(int argc, char** argv) {
   Options options;
   options.process(argc, argv);
   const char* inputname1 = options.getArg(1);
   const char* inputname2 = options.getArg(2);
   const char* outputname = options.getArg(3);

   SoundFileRead  insound1(inputname1);
   SoundFileRead  insound2(inputname2);
   SoundFileWrite outsound(outputname, insound1);

   int i, channel;
   double sample = 0.0;
   for (i=0; i<insound1.getSamples(); i++) {
      for (channel=0; channel < insound1.getChannels(); channel++) {
         sample = insound1.getCurrentSampleDouble(channel);
         sample = sample - insound2.getCurrentSampleDouble(channel);
         outsound.writeSampleDouble(sample);
      }
      insound1.incrementSample();
      insound2.incrementSample();
   }

   return 0;
}


// md5sum: 36d7d18ec50b35ea08b3fb95fb574405 sndsubtract.cpp [20050403]
