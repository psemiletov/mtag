/*
 MTAG (https://github.com/psemiletov/mtag)
 
 This code is Public Domain.
 
 Peter Semiletov <tea@list.ru>, http://semiletov.org
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "libretta_utils.h"
#include "libretta_string_utils.h"
#include "libretta_pairfile.h"


#include <fileref.h>
#include <tstring.h>


using namespace std;
using namespace TagLib;

int main (int argc, char *argv[])
{
  if (argc < 3) 
     {
      cout << "Usage: mtag RULESFILE files_extension. Read README for the details." << endl;
      return 0;
     }
 
  cout << "mtag START" << endl;
 
  string rules_file = argv[1];
  string ext = argv[2];
  ext = "." + ext;
  
  std::vector <string> files = files_get_list (current_path(), ext);
  std::sort (files.begin(), files.end());


  if (files.size() == 0)
    {
     cout << "No files to process! Please provide some files. Read README for the details." << endl;
     return 0;
    }
  
  string rules_file_data = string_file_load (rules_file);
 
  /*
   Nasty hack - the first line at the tags block, by the mystical reason, cannot be
   parsed properly, so we programmatically add the additional line: 
   */
  
  
 // rules_file_data = rules_file_data.insert (3, "@testkey=testvalue\n"); 
   
  
  vector<string> vs = string_split (rules_file_data, "###");
  
  //vs[0] = vs[0].insert (3, "@testkey=testvalue\n"); 
 // vs[0] = vs[0].insert (3, ";a=a\u000A"); 
 //  vs[0] = vs[0].insert (3, ";080808808909\u000A\n"); 
 
  
  
  for (size_t i = 0; i < vs.size(); i++)
     {
      string fname = files[i];
      
      cout << "process:" << fname << endl;
      
      TagLib::FileRef f (fname.c_str());
      
      CPairFile pf (vs[i], true);

  /*
   Nasty hack - the first tag at the first tags block, by the mystical reason, cannot be
   parsed properly.
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
               f.tag()->setYear (atoi(val.c_str()));
           else            
           if (key == "@track")
               f.tag()->setTrack (atoi(val.c_str()));
          }

         f.save();
   
         cout << "tag: saved" << endl;
        }
  
  
  return 0;
}
