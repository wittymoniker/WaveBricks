//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Feb 13 15:31:09 PST 2002
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/snd16.cpp
// Syntax:        C++ 
// For:           Sachiko Deguchi <deguchi@ccrma.stanford.edu>
//
// Description:   Convert arbirary bits samples to 16 bit samples.
//                For example 24 bits sample to 16, but also
//                8-bit to 16-bit samples as well.
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
   const char* inputname  = options.getArg(1);
   const char* outputname = options.getArg(2);

   SoundFileRead  insound(inputname);
   SoundHeader    header;
   header.setHighMono();
   header.setChannels(insound.getChannels());
   header.setSrate(insound.getSrate());
   SoundFileWrite outsound(outputname, header);

   int i, channel;
   for (i=0; i<insound.getSamples(); i++) {
      for (channel=0; channel < insound.getChannels(); channel++) {
         outsound.writeSampleDouble(insound.getCurrentSampleDouble(channel));
      }
      insound.incrementSample(); 
   }

   return 0;
}


// md5sum: dae204523676ba8b41508f8e10bf8648 snd16.cpp [20050403]
