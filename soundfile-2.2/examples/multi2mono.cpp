//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Jan 23 21:10:32 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Filename:      ...soundfile/examples/multi2mono.cpp
// Syntax:        C++ 
//
// Description:   Adds all channels in the input sound file and writes
//                a sound file with the summation of all channels.
//                Amplitude scaling factor can be given to prevent
//                clipping if necessary.
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
   options.define("a|amp=d:1.0",     "amplitude scaling factor");
   options.process(argc, argv);
   
   double amp = options.getDouble("amp");
   const char* inputname  = options.getArg(1);
   const char* outputname = options.getArg(2);

   SoundFileRead  insound(inputname);
   SoundHeader    header = insound;
   header.setChannels(1);
   SoundFileWrite outsound(outputname, header);

   int i, channel;
   double newsample;
   for (i=0; i<insound.getSamples(); i++) {
      newsample = 0.0;
      for (channel = 0; channel < insound.getChannels(); channel++) {
         newsample += insound.getCurrentSampleDouble(channel);
      }
      outsound.writeSampleDouble(amp * newsample/insound.getChannels());
      insound.incrementSample();
   }

   return 0;
}




// md5sum: f71df8766a321be0c049c80d6b8a8e39 multi2mono.cpp [20050403]
