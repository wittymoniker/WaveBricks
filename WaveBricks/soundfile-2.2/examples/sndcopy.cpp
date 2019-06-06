//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Jan 23 20:03:00 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Filename:      ...soundfile/examples/sndcopy.cpp
// Syntax:        C++ 
//
// Description:   Test reading a soundfile using SoundFileRead and
//                SoundFileWrite class.  The output of this program 
//                should be identical to the input; otherwise, there
//                may be bugs in the sound i/o classes.
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
   SoundFileWrite outsound(outputname, insound);

   int i, channel;
   for (i=0; i<insound.getSamples(); i++) {
      for (channel=0; channel < insound.getChannels(); channel++) {
         outsound.writeSampleDouble(insound.getCurrentSampleDouble(channel));
      }
      insound.incrementSample(); 
   }

   return 0;
}





// md5sum: dbfb02fafa2044fe1555a58bf86a626c sndcopy.cpp [20050403]
