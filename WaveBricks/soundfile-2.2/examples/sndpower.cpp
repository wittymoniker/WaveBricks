//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Thu Feb 14 07:20:44 PST 2002
// Last Modified: Sun Jan 19 09:23:59 EST 2003 (added peak amplitude)
// Last Modified: Fri Jan 24 00:09:30 PST 2003 (added formating options)
// Last Modified: Thu Aug 26 17:41:01 PDT 2004 (changed sqrt(2) to sqrt(2.0))
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/sndpower.cpp
// Syntax:        C++ 
//
// Description:   Calculate the average signal power for given durations
//

#include "soundfile.h"
#include <stdlib.h>
#include <math.h>

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif


#ifndef OLDCPP
   #include <iostream>
   #include <iomanip>
   using namespace std;
#else
   #include <iostream.h>
   #include <iomanip.h>
#endif

void printLongSummary   (SoundFileRead& soundfile, int totalframes, 
                         int start, int chunk);

int main(int argc, char** argv) {
   Options options;
   options.define("a|average=i:10000", "Number of samples to average over");
   options.define("s|start=i:0",       "Starting sample");
   options.define("n|count=i:-1",      "Number of analyses to make");
   options.define("all=b",       "calculate the energy of the entire file");
   options.define("q|quiet=b",   "suppress printing of header info");

   options.process(argc, argv);
   if (options.getArgCount() == 0) {
      cout << "Usage: " << options.getCommand() 
           << " filename" 
           << endl;
      exit(1);
   }

   SoundFileRead soundfile(options.getArg(1));

   int chunk = options.getInteger("average");
   int start = options.getInteger("start");
   int totalframes = options.getInteger("count");
   if (totalframes <= 0) {
      totalframes = (soundfile.getSamples() - start)/chunk + 1;
   } 

   // print header information
   if (!options.getBoolean("quiet")) {
      cout << "; Filename        = " << options.getArg(1) << "\n";
      cout << "; Samples         = " << soundfile.getSamples() << "\n";
      if (start != 0) {
         cout << "; Starting sample = " << start << "\n";
      }
      cout << "; Averaging size  = " << chunk << " samples" << "\n";
      cout << "; Total frames    = " << totalframes << "\n";
      cout << "; start-sample	dB	RMS		peak\n";
   }

   if (options.getBoolean("all")) {
      printLongSummary(soundfile, 1, 0, soundfile.getSamples()); 
   } else {
      printLongSummary(soundfile, totalframes, start, chunk);
   }

   return 0;
}



//////////////////////////////
//
// printLongSummary --
//

void printLongSummary(SoundFileRead& soundfile, int totalframes, int start, int chunk) {
   double sum, value, db, rms, peak;
   int i, j, channel;
   for (i=0; i<totalframes; i++) {
      sum = 0.0;
      cout << i * chunk << ":\t";
      for (j=0; j<chunk; j++) {
         for (channel=0; channel < soundfile.getChannels(); channel++) {
            value = soundfile.getCurrentSampleDouble(channel);
            sum += value * value;
         }
         soundfile.incrementSample(); 
      }
      if (sum == 0.0) {
         db = -1000;
      } else {
         db = 10.0 * log10(sum/chunk/soundfile.getChannels());
      }
      rms = sqrt(sum/chunk/soundfile.getChannels());
      peak = sqrt(2.0) * rms;
      cout << db << '\t' << rms << '\t' << peak << "\n";
   }
}



// md5sum: 5a53e4c5bd02e63d794c066cf9642a72 sndpower.cpp [20050403]
