#include <string>
#include <math.h>       


#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
    
  long remaining = seconds;
  long hours = floor(remaining/(60*60));
  remaining -= hours*60*60;
  long minutes = floor(remaining/(60));
  remaining -= minutes*60;

  std::string mins = std::to_string(minutes);
  if(mins.length() == 1){
    mins.insert(0, 1, '0');
  }

  std::string secs = std::to_string(remaining);
  if(secs.length() == 1){
    secs.insert(0, 1, '0');
  }
  
  std::string hms = std::to_string(hours) + ":" + mins  + ":" + secs;

  return hms;

}