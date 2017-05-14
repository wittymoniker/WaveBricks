//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Jan 23 21:02:04 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Last Modified: Sun Aug 29 03:30:07 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/extractChannel.cpp
// Syntax:        C++ 
//
// Description:   Extracts a single channel from a multi-channel soundfile and
//                stores the results in a mono soundfile.  Useful for extracting
//                the left or right channel in a stereo file and storing it
//                into a separate soundfile.
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
   options.define("c|channel=i:0",   "channel to extract (offset from zero)");
   options.process(argc, argv);
   
   int channel = options.getInteger("channel");
   const char* inputname  = options.getArg(1);
   const char* outputname = options.getArg(2);

   SoundFileRead  insound(inputname);
   SoundHeader    header = insound;
   header.setChannels(1);
   SoundFileWrite outsound(outputname, header);

   int i;
   for (i=0; i<insound.getSamples(); i++) {
      outsound.writeSampleDouble(insound.getCurrentSampleDouble(channel));
      insound.incrementSample();   
   }

   return 0;
}





// md5sum: b2a2d7ff65c0023142c6fd36e230f430 extractChannel.cpp [20050403]
