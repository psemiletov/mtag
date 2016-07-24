/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/


#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include "libretta_pairfile.h"

using namespace std;


typedef std::map <string, string> TSPair;


void CPairFile::save()
{
  ofstream myfile (file_name.c_str());
  if (! myfile.is_open())
      return; 
 
  TSPair::const_iterator end = values.end(); 

  for (TSPair::const_iterator it = values.begin(); it != end; ++it)
     {
      myfile << it->first << "=" << it->second << '\n';
     }
  
  myfile.close();
}


void CPairFile::set_string (const string &key, const string &value)
{
  values[key] = value; 
}


void CPairFile::set_float (const string &key, float value)
{
  char buffer [33];
  sprintf (buffer, "%f", value);
  string n (buffer);
  values[key] = n; 
}


float CPairFile::get_float (const string &key, float def_value)
{
  float result = def_value; 

  if (values[key].size() == 0)
     return result; 
  
  const char *s = values[key].c_str();
  if (s)
     result = atof (s);
   
  return result;
}


void CPairFile::set_int (const string &key, int value)
{
  char buffer [33];
  sprintf (buffer, "%d", value);
  string n (buffer);
  values[key] = n; 
}


int CPairFile::get_int (const string &key, int def_value)
{
  int result = def_value; 
  
  if (values[key].size() == 0)
     return result; 
  
  const char *s = values[key].c_str();
  if (s)
     result = atoi (s);
   
  return result;
}


string CPairFile::get_string (const string &key, 
                              const string &def_value)
{
  string result = def_value; 

  if (values[key].size() == 0)
     return result; 
 
  string s = values[key];
  if (! s.empty())
     result = s;
   
  return result;
}


CPairFile::CPairFile (const string &fname, bool from_data)
{
  if (from_data)
    {
     stringstream st (fname);
     string line;
     
     while (getline (st, line)) 
           {
            if (line.empty())
               continue;
            
           // cout << "line: " << line << endl;
           
            size_t pos = line.find ("=");
      
            //cout << "pos: " << pos << endl;
                 
            if (pos == string::npos)
                continue;
        
            if (pos > line.size())
                continue;
                    
            string a = line.substr (0, pos);
            string b = line.substr (pos + 1, line.size() - pos);

            //cout << a << ":" << b << endl;
            
            values[a] = b;
           }
     
     return; 
    }
 
 
  file_name = fname;
  
  ifstream infile (file_name.c_str());

  if (infile.fail())
     {
      cout << "CPairFile::CPairFile - Could not open file: " << fname << endl;
      return;
     }

  string line;

  while (getline (infile, line))
        {
         size_t pos = line.find ("=");
         
         if (pos == string::npos)
            continue;
        
         string a = line.substr (0, pos);
         string b = line.substr (pos + 1, line.size() - pos);

         values[a] = b;
        }

  infile.close();
};
