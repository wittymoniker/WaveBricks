//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Feb 13 13:55:33 PST 2002
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/printbits.cpp
// Syntax:        C++ 
// For:           Sachiko Deguchi <deguchi@ccrma.stanford.edu>
//
// Description:   Display sound amplitude samples in binary form.
//

#include "soundfile.h"
#include <stdlib.h>

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif


// function declarations:
void printBinary(int sample, int digits);

// interface variables:
int spaceQ = 1;     // for use with the -S option

///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
   Options options;
   options.define("b|bits=i:0", "number of bits to display for each sample");
   options.define("n|samples=i:-1", "number of samples to display");
   options.define("s|start=i:0",    "starting samples to display");
   options.define("S|no-space=b",   "don't put spaces into data");
   options.process(argc, argv);
   if (options.getArgCount() == 0) {
      cout << "Usage: " << options.getCommand() 
           << " filename" 
           << endl;
      exit(1);
   }
   spaceQ = !options.getBoolean("no-space");
   int bitdisplay = options.getInteger("bits");
   int start = options.getInteger("start");
   int sampledisplay = options.getInteger("samples");
   SoundFileRead soundfile(options.getArg(1));
   if (bitdisplay <= 0) {
      bitdisplay = soundfile.getBitsPerSample();
   }
   if (bitdisplay > 24) {
      cout << "Error: cannot handle bit sizes greater than 24 bits." << endl;
      exit(1);
   }
   int i, channel;

   cout << "; Sample count = " << soundfile.getSamples() << "\n";
   cout << "; Channels     = " << soundfile.getChannels() << "\n";
   cout << "; Native Bits  = " << soundfile.getBitsPerSample() << "\n";
   if (start < 0) {
      start = 0;
   } else if (start >= soundfile.getSamples()) {
      start = 0;
   }
   soundfile.gotoSample(start);
   if (sampledisplay <= 0) {
      sampledisplay = soundfile.getSamples();
   }
   sampledisplay = sampledisplay - start;

   for (i=start; i<start+sampledisplay; i++) {
      cout << i << ":\t";
      for (channel=0; channel < soundfile.getChannels(); channel++) {
         printBinary(soundfile.getCurrentSample24Bit(channel), bitdisplay);
         cout << "\t";
      }
      cout << "\n";
      soundfile.incrementSample(); 
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////

//////////////////////////////
//
// printBinary -- print sound sample in binary form.
//

void printBinary(int sample, int digits) {
   int i;
   int value;
   for (i=0; i<digits; i++) {
      value = sample >> (24 - 1 - i);
      value = value & 0x01;
      if (value) {
         cout << '1';
      } else {
         cout << '0';
      }
      if (spaceQ) {
         if (((digits - 1) - i) % 4 == 0) {
            cout << ' ';
         }
      }
   }
}



// md5sum: f89d04d5146cc848bd7bd99a82c478ae printbits.cpp [20050403]
