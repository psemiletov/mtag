/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <streambuf>

#include "libretta_string_utils.h"


vector<string> &split (const string &s, char delim)
{
  vector<string> result;
  stringstream stream (s);
  string line;
  
  while (getline (stream, line, delim)) 
       {
        result.push_back (line);
       }
  
  return result;
}


string string_file_load (const string &fname)
{
 std::ifstream t (fname.c_str());
 std::string s ((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

 return s;
}