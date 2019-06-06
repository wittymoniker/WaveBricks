//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Jan 23 21:26:08 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/makemulti.cpp
// Syntax:        C++ 
//
// Description:   Takes several mono input files and writes them
//                all to a single multi-channel soundfile.
//                The last filename is assumed to be the name of the
//                file to be written.  If the input files are not all
//                the same length, then zeros will be appended to the
//                channels of the shorter channels as needed.
//                If you have different sampling rates in each
//                input file, then the output sampling rate will 
//                be that of the first input file -- the sampling
//                rates *will not* be converted by this program.
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
   
   int insize = options.getArgCount() - 1;
   SoundFileRead *inputs = new SoundFileRead[insize];
   int i;
   int maxsample = 0;
   for (i=0; i<insize; i++) {
      inputs[i].setFile(options.getArg(i+1));
      if (inputs[i].getSamples() > maxsample) {
         maxsample = inputs[i].getSamples();
      }
   }

   const char* outputname = options.getArg(insize + 1);
   SoundHeader header = inputs[0];
   header.setChannels(insize);
   SoundFileWrite outsound(outputname, header);

   int channel;
   for (i=0; i<maxsample; i++) {
      for (channel = 0; channel < insize; channel++) {
         outsound.writeSampleDouble(inputs[channel].getCurrentSampleDouble());
         inputs[channel].incrementSample();
      }
   }

   delete [] inputs;
   return 0;
}




// md5sum: caf7a82e5f9354c03fcd3cca4dd3fcd5 makemulti.cpp [20050403]
