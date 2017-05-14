//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Tue Feb 12 10:07:44 PST 2002
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/sndscale.cpp
// Syntax:        C++ 
// For:           Aditya Mishra <adityamishraa@helloduniya.com>
//
// Description:   Scale the volume of a soundfile.
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
   options.define("a|amp=d:1.0", "volume scaling for soundfile");
   options.process(argc, argv);
   if (options.getArgCount() != 2) {
      cout << "Usage: " << argv[0] << " inputfile outputfile " << endl;
      exit(1);
   }
   const char* inputname  = options.getArg(1);
   const char* outputname = options.getArg(2);
   double amp = options.getDouble("amp");

   SoundFileRead  insound(inputname);
   SoundFileWrite outsound(outputname, insound);

   int i, chan;
   for (i=0; i<insound.getSamples(); i++) {
      for (chan=0; chan < insound.getChannels(); chan++) {
         outsound.writeSampleDouble(amp * insound.getCurrentSampleDouble(chan));
      }
      insound.incrementSample(); 
   }

   return 0;
}




// md5sum: 18dd2eb8bd5ac37e6d77d2e248fdc7d2 sndscale.cpp [20050403]
