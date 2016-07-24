/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#ifndef LIBRETTA_PAIRFILE_H
#define LIBRETTA_PAIRFILE_H

#include <string>
#include <map>

using namespace std;

typedef std::map <string, string> TSPair;

class CPairFile
{
public:
  
  string file_name;
  
  TSPair values;
  
  int get_int (const string &key, int def_value = 0);
  float get_float (const string &key, float def_value = 0.0f);
  string get_string (const string &key, const string &def_value = "");
  
  void set_string (const string &key, const string &value);
  void set_int (const string &key, int value);
  void set_float (const string &key, float value);
  
  void save();
  
  CPairFile (const string &fname, bool from_data = false);
};

#endif
