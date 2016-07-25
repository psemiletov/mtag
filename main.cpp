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
      cout << "mtag RULESFILE filemask" <<  endl;
      return 0;
     }
 
  cout << "START" <<  endl;
 
 
  string rules_file = argv[1];
  string mask = argv[2];

  
  std::vector <string> files = files_get_list (current_path(), mask);
  
  std::sort (files.begin(), files.end());
  
  
  string rules_file_data = string_file_load (rules_file);
 
  /*
   Nasty hack - the first line at the tags block, by the mystical reason, cannot be
   parsed properly, so we programmatically add the additional line: 
   */
  
  rules_file_data = rules_file_data.insert (3, "@test=test\n"); 
   
  
  vector<string> vs = string_split (rules_file_data, "###");
   
//  cout << "vs.size: " << vs.size() << endl;
  
 

  for (size_t i = 0; i < vs.size(); i++)
     {
      string fname = files[i];
      
      cout << "process:" << fname << endl;
      
      TagLib::FileRef f (fname.c_str());
      
      CPairFile pf (vs[i], true);
  
      for (auto & kvp : pf.values)
          {

  //         cout << kvp.first << " is " << pf.values[kvp.first] << endl;
           
           string key = kvp.first;
           string val = pf.values[kvp.first];
           
           cout << key << " --------------------- " << val << endl;
     
           if (key == "@artist")
              {
               TagLib::String ts (val, TagLib::String::Type::UTF8);
               f.tag()->setArtist (ts);
              }  
           else            
           if (key == "@title")
              {
               TagLib::String ts (val, TagLib::String::Type::UTF8);
               f.tag()->setTitle (ts);
              }  
           else            
           if (key == "@album")
              {
               TagLib::String ts (val, TagLib::String::Type::UTF8);
               f.tag()->setAlbum (ts);
              }  
           else            
           if (key == "@genre")
              {
               TagLib::String ts (val, TagLib::String::Type::UTF8);
               f.tag()->setGenre (ts);
              }  
           else            
           if (key == "@comment")
              {
               TagLib::String ts (val, TagLib::String::Type::UTF8);
               f.tag()->setComment (ts);
              }  
           else            
           if (key == "@year")
               f.tag()->setYear (atoi(val.c_str()));
           else            
           if (key == "@track")
               f.tag()->setTrack (atoi(val.c_str()));
   
          }

         f.save();
   
         cout << "tag saved" << endl;
      
     }
  
  
  return 0;
}
