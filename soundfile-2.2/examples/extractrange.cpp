//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Thu Aug 26 00:22:22 PDT 2004
// Last Modified: Thu Aug 26 00:22:25 PDT 2004
// Filename:      ...soundfile/examples/extractRange.cpp
// Syntax:        C++ 
//
// Description:   Extracts a range of samples from a soundfile
//

#include "soundfile.h"

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif

int main(int argc, char** argv) {
   Options options;
   options.define("b|begin=i:0", "beginning sample inclusive");
   options.define("B|Begin=i:0", "beginning sample exclusive");
   options.define("e|end=i:0",   "ending sample inclusive");
   options.define("E|End=i:0",   "ending sample exclusive");
   options.define("v|verbose=b", "verbose output");
   options.process(argc, argv);

   if (options.getArgCount() != 2) {
      cout << "Usage: " << options.getCommand() 
           << " -[b|B] begin_sample -[e|E] end_sample input.wav output.wav\n";
      cout << "\n-b = begin sample (offset from 0)\n";
      cout << "-B = begin sample excluding specified sample\n";
      cout << "-e = end sample including specified sample\n";
      cout << "-E = end sample excluding specified sample\n";
      cout << "-v = verbose: display calculated range\n";
      cout << endl;
      exit(1);
   }
   
   const char* inputname  = options.getArg(1);
   const char* outputname = options.getArg(2);

   SoundFileRead  insound(inputname);
   SoundHeader    header = insound;
   SoundFileWrite outsound(outputname, header);

   int startsample = 0;
   if (options.getBoolean("begin")) {
      startsample = options.getInteger("begin");
   } else if (options.getBoolean("Begin")) {
      startsample = options.getInteger("Begin") + 1;
   }

   int stopsample = 0;
   if (options.getBoolean("end")) {
      stopsample = options.getInteger("end");
   } else if (options.getBoolean("End")) {
      stopsample = options.getInteger("End") - 1;
   }

   if (options.getBoolean("verbose")) {
      cout << "Input: " << inputname << "\tOutput: " << outputname << endl;
      cout << "\tBegin_sample: " << startsample 
           << "\tEnd_sample: " << stopsample << endl;
      cout << "\tSample_count: " << stopsample - startsample + 1
           << "\tSeconds: " 
           << (stopsample - startsample + 1.0) / header.getSrate() << endl;
   }

   int samplecount = stopsample - startsample + 1;
   insound.gotoSample(startsample);   // offset by zero

   int i, j;
   for (i=0; i<samplecount; i++) {
      for (j=0; j<header.getChannels(); j++) {
         outsound.writeSampleDouble(insound.getCurrentSampleDouble(j));
      }
      insound.incrementSample();   
   }

   return 0;
}



// md5sum: 4e88b7f680c7e1c46dc2a076b0a8f9e3 extractrange.cpp [20050403]
