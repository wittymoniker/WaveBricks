//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Jan 23 21:49:46 PST 2002
// Last Modified: Sun Feb  3 11:08:04 PST 2002 (updated for soundfile 2.0)
// Last Modified: Sun Aug 29 03:33:21 PDT 2004 (updated for compiling in GCC3)
// Filename:      ...soundfile/examples/sndinfo.cpp
// Syntax:        C++ 
//
// Description:   Print out header information from input soundfile(s).
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
   SoundFileRead  insound;

   int i;
   for (i=1; i<=options.getArgCount(); i++) {
      insound.setFile(options.getArg(i));
      cout << "Filename:        " << insound.getFilename() << "\n";
      cout << insound << endl;

   }

   return 0;
}





// md5sum: 79a9a1abade8301b268bda2fe6874cc8 sndinfo.cpp [20050403]
