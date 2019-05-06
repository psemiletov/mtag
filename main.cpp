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
#include <cstdio>

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
  
 // result = string_replace_all (result, str_counter, std::to_string (index));
 
  result = string_replace_all (result, str_counter, bstr);
 
  return result;
}


void files_list_tags (const string &ext, const string &templte)
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
      
       size_t sep = fname.rfind ("/");
       if (sep == 0)
          continue;
      
       string dir = fname.substr (0, sep + 1);
       string name = fname.substr (sep + 1);
       string sout = templte; 
       sout = string_replace_all (sout, "@fname", name);
          
       TagLib::FileRef f (fname.c_str());
      
       if (f.tag()->properties().size() == 0)
           continue;
      
       TagLib::String ts;
      
       ts = f.tag()->artist();
       if (! ts.isEmpty())
          sout = string_replace_all (sout, "@artist", ts.toCString(true));
      
       ts = f.tag()->title();
       if (! ts.isEmpty())
          sout = string_replace_all (sout, "@title", ts.toCString(true));

       ts = f.tag()->album();
       if (! ts.isEmpty())
          sout = string_replace_all (sout, "@album", ts.toCString(true));
      
       ts = f.tag()->comment();
       if (! ts.isEmpty())
          sout = string_replace_all (sout, "@comment", ts.toCString(true));
      
       ts = f.tag()->genre();
       if (! ts.isEmpty())
          sout = string_replace_all (sout, "@genre", ts.toCString(true));
       
       unsigned int x = 0;
   
       x = f.tag()->year();
       if (x != 0)
          sout = string_replace_all (sout, "@year", std::to_string (x));
   
       x = f.tag()->track();
       if (x != 0)
          sout = string_replace_all (sout, "@track", std::to_string (x));
      
       sout = process_counter (sout, '#', i + 1);
      
       cout << sout << endl;
     }
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
      
       nameout = process_counter (nameout, '#', i + 1);
       nameout = dir + nameout;
      
//      cout << nameout << endl;
      
       int r = rename (fname.data(), nameout.data());
       if (! r)
          cout << "cannot rename " << fname << " > " << nameout << endl;
       else
           cout << fname << " > " << nameout << endl;
     }
     
  cout << "files: renamed" << endl;
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

  if (vs.size() != files.size())
     {
      cout << "Warning! Files count is not equal to songs count at the rules file." << endl;
      return;
     }

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

      //TODO: check CPairFile::CPairFile for the bug described obove

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


void extract_tags (const string &rules_file, const string &ext, const string &required_tag_set)
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

       string filename_comment = "#filename: " + fname;
       vs.push_back(filename_comment);
          
       cout << "process:" << fname << endl;
      
       TagLib::FileRef f (fname.c_str());
      
       if (f.tag()->properties().size() == 0)
          continue;
      
       TagLib::String ts;
      
       ts = f.tag()->artist();
       if (! ts.isEmpty() || std::string::npos != required_tag_set.find("@artist"))
          {           
           string pair = "@artist";
           pair += "=";
           pair += ts.toCString(true);
           vs.push_back (pair);
          } 
   
        ts = f.tag()->title();
        if (! ts.isEmpty() || std::string::npos != required_tag_set.find("@title"))
           {
            string pair = "@title";
            pair += "=";
            pair += ts.toCString(true);
            vs.push_back (pair);
           } 
   
        ts = f.tag()->album();
        if (! ts.isEmpty() || std::string::npos != required_tag_set.find("@album"))
           {
            string pair = "@album";
            pair += "=";
            pair += ts.toCString(true);
            vs.push_back (pair);
           } 
   
        ts = f.tag()->comment();
        if (! ts.isEmpty() || std::string::npos != required_tag_set.find("@comment"))
           {
            string pair = "@comment";
            pair += "=";
            pair += ts.toCString(true);
            vs.push_back (pair);
           } 
   
        ts = f.tag()->genre();
        if (! ts.isEmpty() || std::string::npos != required_tag_set.find("@genre"))
           {
            string pair = "@genre";
            pair += "=";
            pair += ts.toCString(true);
            vs.push_back (pair);
           } 
   
        unsigned int x = 0;
   
        x = f.tag()->year();

        if (x != 0 || std::string::npos != required_tag_set.find("@year"))
           {
            string pair = "@year";
            pair += "=";
            pair += std::to_string (x);
            vs.push_back (pair);
           } 
   
        x = f.tag()->track();

        if (x != 0 || std::string::npos != required_tag_set.find("@track"))
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
  if (argc < 2) 
     {
      cout << "mtag 2.2.4" << endl;
      cout << "mtag: the command line tool for media files tagging" << endl;
      cout << "by Petr Semiletov" << endl;
      cout << "https://github.com/psemiletov/mtag" << endl;
      cout << endl;
      
      cout << "Too few arguments. Look at README for the details." << endl;
      return 0;
     }

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
     string required_tag_set = "";

     if (argv[4])
         required_tag_set = argv[4];

     extract_tags (rules_file, ext, required_tag_set);
    }
  else
  if (command == "rename")
     {
      cout << "rename" << endl;
      string templte = argv[2];
      string ext = argv[3];
      files_rename_by_tags (ext, templte);
     }
  else
  if (command == "list")
     {
      string templte = argv[2];
      string ext = argv[3];
      files_list_tags (ext, templte);
     }

  return 0;
}
