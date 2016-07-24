/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <streambuf>

#include "libretta_string_utils.h"


vector<string> string_split (const string &s, char delim)
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


vector<string> string_split (string s, const string &delim)
{
  vector<string> result;
  
  size_t delen = delim.length();
  size_t start = 0;
  size_t end = s.find (delim);
  
  while (end != std::string::npos)
       {
        result.push_back (s.substr (start, end - start));
        start = end + delen;
        end = s.find (delim, start);
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