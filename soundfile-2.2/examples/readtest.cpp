//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Jan 20 12:59:32 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Filename:      ...soundfile/examples/readtest.cpp
// Syntax:        C++ 
//
// Description:   Test reading a soundfile using SoundFileRead class.
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
   if (options.getArgCount() == 0) {
      cout << "Usage: " << options.getCommand() 
           << " filename" 
           << endl;
      exit(1);
   }

   SoundFileRead soundfile(options.getArg(1));
   int i, channel;

   cout << "; Sample count = " << soundfile.getSamples() << "\n";
   cout << "; Channels     = " << soundfile.getChannels() << "\n";
   cout << "; samp\t16-bit\tdouble\n";
   
   if (soundfile.getBitsPerSample() == 24) {
      for (i=0; i<soundfile.getSamples(); i++) {
         cout << i << ":\t";
         for (channel=0; channel < soundfile.getChannels(); channel++) {
            cout << soundfile.getCurrentSample24Bit(channel);
            cout << "\t(";
            cout << soundfile.getCurrentSampleDouble(channel) << ")\t";
         }
         cout << "\n";
         soundfile.incrementSample(); 
      }
   } else {
      for (i=0; i<soundfile.getSamples(); i++) {
         cout << i << ":\t";
         for (channel=0; channel < soundfile.getChannels(); channel++) {
            cout << soundfile.getCurrentSample16Bit(channel);
            cout << "\t(";
            cout << soundfile.getCurrentSampleDouble(channel) << ")\t";
         }
         cout << "\n";
         soundfile.incrementSample(); 
      }
   }
   
   return 0;
}





// md5sum: 2191b0d5d7026d99816c4cf22f191e95 readtest.cpp [20050403]
