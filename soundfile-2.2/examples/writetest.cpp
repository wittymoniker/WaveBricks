//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Jan 20 12:13:18 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Filename:      ...soundfile/examples/writetest.cpp
// Syntax:        C++ 
//
// Description:   Test writing a soundfile using SoundFileWrite class.
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
   options.define("n|samples=i:100", "number of samples to write");
   options.define("s|start=i:0",     "starting value to write");
   options.define("d|double=b",      "write samples also as doubles");
   options.process(argc, argv);
   if (options.getArgCount() == 0) {
      cout << "Usage: " << options.getCommand() 
           << " [-n count][-s start][-d] filename" 
           << endl;
      exit(1);
   }

   SoundHeader header;
   header.setHighMono();
   SoundFileWrite soundfile(options.getArg(1), header);
   int count = options.getInteger("samples");
   int start = options.getInteger("start");
   int i;

   for (i=0; i<count; i++) {
      soundfile.writeSample16Bit((short)(i+start));
   }

   // test writing doubles to the file (writing the same info as last loop)

   if (options.getBoolean("double")) {
      for (i=0; i<count; i++) {
         soundfile.writeSampleDouble(((double)(i+start))/0x8000);
      }
   }


   // file will be closed automatically, but can be done manually:
   soundfile.close();

   return 0;
}





// md5sum: 0786311b475438b96f55ce4c2fe3d9ce writetest.cpp [20050403]
