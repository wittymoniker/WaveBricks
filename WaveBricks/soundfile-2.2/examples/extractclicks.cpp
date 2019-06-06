//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Thu Oct 13 01:31:38 PDT 2005
// Last Modified: Thu Oct 13 01:31:44 PDT 2005
// Filename:      ...soundfile/examples/extractclick.cpp
// Syntax:        C++ 
//
// Description:   Creates a list of times in milliseconds at which
//                times the program finds a click in a click track channel.
//                The click-track channel has digital silence between
//                the clicks, and the click time is aligned to the
//                nearest millisecond of the start of the click.
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
   options.define("c|channel=i:0","the click track channel");
   options.define("r|refraction-time=d:10.0","minimum time btwn clicks in ms");
   options.process(argc, argv);

   int channel    = options.getInteger("channel");
   const char* inputname  = options.getArg(1);
   SoundFileRead  insound(inputname);
   SoundHeader    header = insound;
   int refraction = (int)(header.getSrate() *
         options.getDouble("refraction-time") / 1000.0 + 0.5);

   int i;
   int rstatus = 0;

   for (i=0; i<insound.getSamples(); i++) {
      if (rstatus >= refraction) {
         rstatus = 0;
      }
      if (rstatus) {
         rstatus++;
      } else {
         if (insound.getCurrentSampleDouble(channel) != 0.0) {
            rstatus = 1;
            cout << (int)(1000.0 * i / header.getSrate() + 0.5) << "\n";
         }
      }
      insound.incrementSample();
   }

   return 0;
}


