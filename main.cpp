/*
 MTAG (https://github.com/psemiletov/mtag)
 
 This code is Public Domain.
 
 Peter Semiletov <tea@list.ru>, http://semiletov.org
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#include "libretta_utils.h"
#include "libretta_string_utils.h"
#include "libretta_pairfile.h"


#include <fileref.h>
#include <tstring.h>
#include <tpropertymap.h>

using namespace std;
using namespace TagLib;




string process_counter (const string &val, const char &counter_char, size_t index)
{
  string result = val;
  
  size_t i = val.find (counter_char); 
  
  if (i == string::npos)
       return result;
  
  size_t len = val.length();
   
  for (size_t j = i; j < len; j++)
      {
       if (val[j] != counter_char)
         {
          len = j - i;
          break; //how many digits in the counter
         } 
       else //to properly parse the counter at the end of the string
           if ((j + 1) == len)
             {
              len = j - i + 1;
              break; 
           }
      } 
  
   
  string str_counter (len, counter_char);
  
  string outfmt = "%0";
  outfmt += std::to_string (len);
  outfmt += "d";
  
  char buff [256];
  snprintf (buff, sizeof (buff), outfmt.data(), index);
  string bstr = buff;
  
  result = string_replace_all (result, str_counter, std::to_string (index));
  
  return result;
}


void files_rename_by_tags (const string &ext, const string &templte)
{
 
  std::vector <string> files = files_get_list (current_path(), ext);
  std::sort (files.begin(), files.end());

  if (files.size() == 0)
    {
     cout << "No files to process! Please provide some files. Read README for the details." << endl;
     return;
    }
  
  for (size_t i = 0; i < files.size(); i++)
     {
      string fname = files[i];
          
      cout << "rename:" << fname << endl;
      
      size_t sep = fname.rfind ("/");
      if (sep == 0)
          continue;
      
      string dir = fname.substr (0, sep + 1);
      string name = fname.substr (sep + 1);
      
     
      string nameout = templte; 
      
      nameout = string_replace_all (nameout, "@fname", name);
      
      
      TagLib::FileRef f (fname.c_str());
      
      if (f.tag()->properties().size() == 0)
          continue;
      
      TagLib::String ts;

      
      ts = f.tag()->artist();
      if (! ts.isEmpty())
         nameout = string_replace_all (nameout, "@artist", ts.toCString(true));
      
      ts = f.tag()->title();
      if (! ts.isEmpty())
         nameout = string_replace_all (nameout, "@title", ts.toCString(true));

      ts = f.tag()->album();
      if (! ts.isEmpty())
         nameout = string_replace_all (nameout, "@album", ts.toCString(true));
      
      ts = f.tag()->comment();
      if (! ts.isEmpty())
         nameout = string_replace_all (nameout, "@comment", ts.toCString(true));
      
      ts = f.tag()->genre();
      if (! ts.isEmpty())
         nameout = string_replace_all (nameout, "@genre", ts.toCString(true));
      
      unsigned int x = 0;
   
      x = f.tag()->year();
      if (x != 0)
         nameout = string_replace_all (nameout, "@year", std::to_string (x));
   
      x = f.tag()->track();
      if (x != 0)
         nameout = string_replace_all (nameout, "@track", std::to_string (x));
     
      
      nameout = process_counter (nameout, '#', i);
      
      nameout = dir + nameout;
      
      cout << "nameout: " << nameout << endl;
       
      cout << "files: renamed" << endl;
     }
  
  }

 
 


void write_tags (const string &rules_file, const string &ext)
{
  std::vector <string> files = files_get_list (current_path(), ext);
  std::sort (files.begin(), files.end());
  if (files.size() == 0)
    {
     cout << "No files to process! Please provide some files. Read README for the details." << endl;
     return;
    }

  string rules_file_data = string_file_load (rules_file);
  
  vector<string> vs = string_split (rules_file_data, "###");

  for (size_t i = 0; i < vs.size(); i++)
     {
      string fname = files[i];
      cout << "process:" << fname << endl;
      TagLib::FileRef f (fname.c_str());
      CPairFile pf (vs[i], true);

      /*
       Nasty hack - the first tag at the first tags block,
       by the mystical reason, cannot be parsed properly.
      There are two medicines from this STRANGE behaviour.
      1. Manually (but not programmatically from mtag)
      add the obsolete first line to the RULES file.
      2. Add the obsolete key-val to the tags structure.
      */

     pf.values["@testkey"] = "testvalue";
     for (auto & kvp : pf.values)
        {
         string key = kvp.first;
         string val = pf.values[kvp.first];
         
         cout << key << " --------------------- " << val << endl;
         
         TagLib::String ts (val, TagLib::String::Type::UTF8);
         
         if (key == "@artist")
            f.tag()->setArtist (ts);
         else
         if (key == "@title")
            f.tag()->setTitle (ts);
         else
         if (key == "@album")
            f.tag()->setAlbum (ts);
         else
         if (key == "@genre")
            f.tag()->setGenre (ts);
         else
             if (key == "@comment")
         f.tag()->setComment (ts);
         else
         if (key == "@year")
            f.tag()->setYear (stoi (val));
         else
         if (key == "@track")
            f.tag()->setTrack (stoi (val));
        }

     f.save();
     cout << "tag: saved" << endl;
    }
}


void extract_tags (const string &rules_file, const string &ext)
{
  std::vector <string> files = files_get_list (current_path(), ext);
  std::sort (files.begin(), files.end());


  if (files.size() == 0)
    {
     cout << "No files to process! Please provide some files. Read README for the details." << endl;
     return;
    }
     
  
  vector<string> vs;
  
  for (size_t i = 0; i < files.size(); i++)
     {
      string fname = files[i];
          
      cout << "process:" << fname << endl;
      
      TagLib::FileRef f (fname.c_str());
      
      if (f.tag()->properties().size() == 0)
          continue;
      
      TagLib::String ts;
      
      ts = f.tag()->artist();
      if (! ts.isEmpty())
        {
         string pair = "@artist";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      ts = f.tag()->title();
      if (! ts.isEmpty())
        {
         string pair = "@title";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      ts = f.tag()->album();
      if (! ts.isEmpty())
        {
         string pair = "@album";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      ts = f.tag()->comment();
      if (! ts.isEmpty())
        {
         string pair = "@comment";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
   
      ts = f.tag()->genre();
      if (! ts.isEmpty())
        {
         string pair = "@genre";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      unsigned int x = 0;
   
      x = f.tag()->year();
      if (x != 0)
        {
         string pair = "@year";
         pair += "=";
         pair += std::to_string (x);
         vs.push_back (pair);
        } 
   
      x = f.tag()->track();
      if (x != 0)
        {
         string pair = "@track";
         pair += "=";
         pair += std::to_string (x);
         vs.push_back (pair);
        } 
   
   
      vs.push_back ("###");
      
      cout << "tags: extracted" << endl;
     }
     
  //vs.pop_back();   
     
  ofstream outputFile (rules_file);

  if (outputFile.is_open())
    {
     for (string s: vs) 
        { 
         outputFile << s << endl; 
        }
    }   
  else 
      cout << "Unable to write output file" << endl;
}


int main (int argc, char *argv[])
{
  if (argc < 3) 
     {
      cout << "Too few arguments. Read README for the details." << endl;
      return 0;
     }

  cout << "mtag 2.1" << endl;
  cout << "mtag: the command line tool for media files tagging" << endl;
  cout << "by Petr Semiletov" << endl;
  cout << "https://github.com/psemiletov/mtag" << endl;
          
  cout << "mtag START" << endl;
 
  string command = argv[1];
  
  if (command == "apply")
     {
      string rules_file = argv[2];
      string ext = argv[3];
      ext = "." + ext;
      write_tags (rules_file, ext);
     }
  else
  if (command == "extract")
    {
     cout << "extract" << endl;
     string rules_file = argv[2];
     string ext = argv[3];
     extract_tags (rules_file, ext);
    }
  else
  if (command == "rename")
    {
     cout << "rename" << endl;
     string templte = argv[2];
     string ext = argv[3];
     files_rename_by_tags (ext, templte);
  }

  return 0;
}
