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
   #include <fstream>
   using namespace std;
#else
   #include <iostream.h>
   #include <fstream.h>
#endif

void getClickTimes(Array<long>& clicktimes, const char* filename);


//////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
   Options options;
   options.define("a|amp=d:1.0",       "amplitude scaling factor");
   options.define("c|click-amp=d:0.15","click track amplitude scaling factor");
   options.process(argc, argv);
   
   double amp      = options.getDouble("amp");
   double clickamp = options.getDouble("click-amp");
   const char* inputname  = options.getArg(1);
   const char* clicktrack = options.getArg(2);
   const char* outputname = options.getArg(3);

   Array<long> clicktimes;
   getClickTimes(clicktimes, clicktrack);

   SoundFileRead  insound(inputname);
   SoundHeader    header = insound;
   header.setChannels(2);
   SoundFileWrite outsound(outputname, header);

   int i, channel;
   double newsample;
   double clicksample;

   for (i=0; i<clicktimes.getSize(); i++) {
      clicktimes[i] = (long)(clicktimes[i] / 1000.0 * insound.getSrate() + 0.5);
      cout << clicktimes[i] << endl;
   }

   int clicki = 0;
   int clickstatus = 0;
   int clickcount = clicktimes.getSize();

   for (i=0; i<insound.getSamples(); i++) {
      newsample = 0.0;
      for (channel = 0; channel < insound.getChannels(); channel++) {
         newsample += insound.getCurrentSampleDouble(channel);
      }
      if ((clicki < clickcount) && (clicktimes[clicki] == i)) {
         clickstatus = 1;
         clicki++;
      }
      if (clickstatus) {
         clicksample = ((rand() * 2.0)/INT_MAX - 1.0) * clickamp;
         clickstatus++;
         if (clickstatus > 44) {
            clickstatus = 0;
         }
      } else {
         clicksample = 0.0;
      }
      outsound.writeSampleDouble(clicksample);
      outsound.writeSampleDouble(amp * newsample/insound.getChannels());
      insound.incrementSample();
   }

   return 0;
}



//////////////////////////////
//
// getClickTimes --
//

void getClickTimes(Array<long>& clicktimes, const char* filename) {

   ifstream clickfile(filename);
   if (!clickfile.is_open()) {
      cerr << "Error: cannot open file " << filename << endl;
   }

   long input;
   clicktimes.setSize(100000);
   clicktimes.setGrowth(100000);
   clicktimes.setSize(0);

   clickfile >> input;
   while (!clickfile.eof()) {
      clicktimes.append(input);
      clickfile >> input;
   }
}


// md5sum: 5090326fba542fed193ee26abbe6281a clicktrack.cpp [20051017]
