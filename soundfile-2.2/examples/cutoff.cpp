//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed May 14 16:12:29 PDT 2003
// Last Modified: Sun Aug 29 03:22:58 PDT 2004 (updates for GCC3 compiling)
// Filename:      ...soundfile/examples/cutoff.cpp
// Syntax:        C++ 
//
// Description:   Calculate the average signal power for given durations
//

#include "soundfile.h"
#include <stdlib.h>
#include <math.h>

#ifndef OLDCPP
   #include <iostream>
   #include <iomanip>
   using namespace std;
#else
   #include <iostream.h>
   #include <iomanip.h>
#endif

void generatePowerSummary(Array<double>& list, const char* filename,
      int chunk, int frames);
void printLongSummary(Array<double>& list, int chunk, int channels);
void generateOutputFile(const char* outfilename, const char* infilename, 
      Array<double>& powerlist, double cutoff, int direction, int chunk);

int main(int argc, char** argv) {
   Options options;
   options.define("a|average=i:10000", "Number of samples to average over");
   options.define("c|cutoff=d:0.1",    "Cut-off RMS amplitude");
   options.define("h|high=b",     "Remove stuff above the cutoff");
   options.define("l|low=b",      "Remove stuff below the cutoff");
   options.define("i|info=b",     "Print only power information");
   options.define("s|start=i:0",  "Starting sample");
   options.define("n|count=i:-1", "Number of analyses to make");
   options.define("all=b",        "Calculate the energy of the entire file");
   options.define("q|quiet=b",    "Suppress printing of header info");
   options.process(argc, argv);

   if (options.getArgCount() == 0) {
      cout << "Usage: " << options.getCommand() 
           << " filename" 
           << endl;
      exit(1);
   }

   int direction = 1;
   if (options.getBoolean("high")) {
      direction = 0;
   }
   double cutoff = options.getDouble("cutoff");

   SoundFileRead soundfile(options.getArg(1));
   int chunk = options.getInteger("average");
   int start = options.getInteger("start");
   int channels = soundfile.getChannels();
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

   Array<double> powerlist;
   generatePowerSummary(powerlist, options.getArg(1), chunk, totalframes);

   if (options.getBoolean("info")) {
      if (options.getBoolean("all")) {
         printLongSummary(powerlist, soundfile.getSamples(), channels); 
      } else {
         printLongSummary(powerlist, chunk, channels);
      }
   } else {
      generateOutputFile(options.getArg(2), options.getArg(1), powerlist, 
            cutoff, direction, chunk);
   }

   return 0;
}


//////////////////////////////
//
// generateOutputFile --
//

void generateOutputFile(const char* outfilename, const char* infilename, 
      Array<double>& powerlist, double cutoff, int direction, int chunk) {

   SoundFileRead infile(infilename);
   SoundFileWrite outfile(outfilename, infile);
   int samples  = infile.getSamples();
   int channels = infile.getChannels();

   int i, chan;
   int frame;

   Array<double> rms(powerlist.getSize());
   for (i=0; i<rms.getSize(); i++) {
      rms[i] = sqrt(powerlist[i]/chunk/channels);
   }

   for (i=0; i<samples; i++) {
      frame = i/chunk;
      for (chan=0; chan<channels; chan++) {
         if (rms[frame] < cutoff && direction == 1) {
            outfile.writeSampleDouble(0.0);
         } else if (rms[frame] > cutoff && direction == 0) {
            outfile.writeSampleDouble(0.0);
         } else {
            outfile.writeSampleDouble(infile.getCurrentSampleDouble(chan));
         }
      }
      infile.incrementSample(); 
   }
}



//////////////////////////////
//
// generatePowerSummary --
//

void generatePowerSummary(Array<double>& list, const char* filename,
      int chunk, int frames) {

   SoundFileRead soundfile(filename);
   list.setSize(frames+100);
   list.setGrowth(frames+100);
   list.setSize(0);

   double sum, value;
   int i, j, channel;
   for (i=0; i<frames; i++) {
      sum = 0.0;
      for (j=0; j<chunk; j++) {
         for (channel=0; channel < soundfile.getChannels(); channel++) {
            value = soundfile.getCurrentSampleDouble(channel);
            sum += value * value;
         }
         soundfile.incrementSample(); 
      }

      list.append(sum);
   }
}



//////////////////////////////
//
// printLongSummary --
//

void printLongSummary(Array<double>& list, int chunk, int channels) {
   double db, rms, peak;
   int i;
   for (i=0; i<list.getSize(); i++) {
      cout << i * chunk << ":\t";
      if (list[i] == 0.0) {
         db = -1000;
      } else {
         db = 10.0 * log10(list[i]/chunk/channels);
      }
      rms = sqrt(list[i]/chunk/channels);
      peak = sqrt(2.0) * rms;
      cout << db << '\t' << rms << '\t' << peak << "\n";
   }
}



// md5sum: df65bc0564edc975e12594ee774aed81 cutoff.cpp [20050403]
