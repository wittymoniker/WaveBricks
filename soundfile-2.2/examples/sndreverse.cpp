//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Feb  3 12:55:04 PST 2002
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/sndreverse.cpp
// Syntax:        C++ 
//
// Description:   Demonstration of the SoundFileRead::gotoSample().
//                Reverses all of the samples from input soundfile.
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
   if (options.getArgCount() != 2) {
      cout << "Usage: " << options.getCommand() << " insound outsound" << endl;
      exit(1);
   }

   SoundFileRead insound(options.getArg(1));
   SoundFileWrite outsound(options.getArg(2), insound);
   int channels     = insound.getChannels();
   int totalsamples = insound.getSamples();
   int i, j;

   for (i=totalsamples - 1; i >= 0; i--) {
      insound.gotoSample(i);
      for (j=0; j<channels; j++) {
         outsound.writeSampleDouble(insound.getCurrentSampleDouble(j));
      }
   }

   return 0;
}


// md5sum: 4c34aecc7438a9317eaf85a75f24a2e7 sndreverse.cpp [20050403]
