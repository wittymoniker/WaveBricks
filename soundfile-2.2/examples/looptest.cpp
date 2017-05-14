//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Feb  2 10:06:21 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Last Modified: Sun Aug 29 03:32:03 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/looptest.cpp
// Syntax:        C++ 
//
// Description:   Test looping a soundfile using SoundFileRead class.
//

#include "soundfile.h"
#include <stdlib.h>

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif


void printSample(SoundFileRead& soundfile);


int main(int argc, char** argv) {
   Options options;
   options.define("L|no-looping=b",  "turn off looping");
   options.define("r|reset=b",       "use reset to restart looping");
   options.process(argc, argv);
   if (options.getArgCount() == 0) {
      cout << "Usage: " << options.getCommand() 
           << " filename" 
           << endl;
      exit(1);
   }

   SoundFileRead soundfile(options.getArg(1));
   if (!options.getBoolean("no-looping") && !options.getBoolean("reset")) {
      soundfile.setLoopOn();                        // enable looping
   }
   int i;

   cout << "; Sample count = " << soundfile.getSamples() << "\n";
   cout << "; Channels     = " << soundfile.getChannels() << "\n";
   cout << "; samp\t16-bit\tdouble\n";

   cout << "; The first 10 samples:\n";
   for (i=0; i<10; i++) {
      printSample(soundfile);
      soundfile.incrementSample(); 
   }

   soundfile.gotoSample(soundfile.getSamples() - 10); 
   
   cout << "\n; The last 10 samples:\n";
   for (i=0; i<10; i++) {
      printSample(soundfile);
      soundfile.incrementSample(); 
   }
 
   if (options.getBoolean("reset")) {
      soundfile.reset();
   }
   
   cout << "\n; The first 10 samples again via looping:\n";
   for (i=0; i<10; i++) {
      printSample(soundfile);
      soundfile.incrementSample();
   }
 
   return 0;
}



//////////////////////////////
//
// printSample -- print the samples at the current point in the soundfile.
//

void printSample(SoundFileRead& soundfile) {
      cout << soundfile.getCurrentSampleIndex() << ":\t";
      int channel;
      for (channel=0; channel < soundfile.getChannels(); channel++) {
         cout << soundfile.getCurrentSample16Bit(channel);
         cout << "\t(";
         cout << soundfile.getCurrentSampleDouble(channel) << ")\t";
      }
      cout << "\n";
}

// md5sum: 95fb9c64f63f367084b461823dc64261 looptest.cpp [20050403]
