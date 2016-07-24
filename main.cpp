#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "libretta_utils.h"
#include "libretta_string_utils.h"
#include "libretta_pairfile.h"


#include <fileref.h>
#include <tstring.h>

/*
#include <mpegfile.h>



#include <id3v2tag.h>
#include <id3v2frame.h>
#include <id3v2header.h>

#include <id3v1tag.h>
*/

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
  
  /*
  for (const auto &t: files)
      {  
       cout << t << endl;
     
      }
  */
  
  string rules_file_data = string_file_load (rules_file);
 
 // rules_file_data = rules_file_data.insert (0, ";\n");
   
  //cout << rules_file_data << endl;
  
  vector<string> vs = string_split (rules_file_data, "###");
   
  cout << "vs.size: " << vs.size() << endl;
  
  
 /* 
  for (auto &element: vs)
      {
      // if (element.empty())
        //  continue;
       
       
       CPairFile pf (element, true);
       cout << pf.get_string ("@artist", "1") << endl;
       cout << pf.get_string ("@title", "1") << endl;
       
       //cout << pf.values.size() << endl;
       
      }
 */
 
   
 //cout << vs[0] << endl;
 
/* 
   CPairFile pft (vs[0], true);
   
   cout << "pft.values.size is " << pft.values.size() << endl;
   
  std::vector<string> itemKeys;
for (auto & kvp : pft.values)
{
    itemKeys.emplace_back(kvp.first);
    //std::cout << kvp.first << std::endl;

   cout << "!!!!!! " << pft.values[kvp.first] << endl;
    
    
}
  */ 
   
 //  cout << "!!!!!! " << pft.values["@artist"] << endl;
//   cout << "!!!!!! " << pft.values["@title"] << endl;
   //cout << "!!!!!! " << pft.values["@album"] << endl;
         
 

  for (size_t i = 0; i < vs.size(); i++)
     {
      string fname = files[i];
      
      cout << "process:" << fname << endl;
      
      TagLib::FileRef f (fname.c_str());
      
      CPairFile pf (vs[i], true);
  
      for (auto & kvp : pf.values)
          {
           //itemKeys.emplace_back(kvp.first);
           //std::cout << kvp.first << std::endl;

           cout << kvp.first << " is " << pf.values[kvp.first] << endl;
     
           if (kvp.first == "@artist")
              {
               TagLib::String ts (pf.values[kvp.first], TagLib::String::Type::UTF8);
               f.tag()->setArtist (ts);
              }  
           
           if (kvp.first == "@title")
              {
               TagLib::String ts (pf.values[kvp.first], TagLib::String::Type::UTF8);
               f.tag()->setTitle (ts);
              }  
   
           if (kvp.first == "@album")
              {
               TagLib::String ts (pf.values[kvp.first], TagLib::String::Type::UTF8);
               f.tag()->setAlbum (ts);
              }  
           
          }

         f.save();
   
         cout << "tag saved" << endl;
   
      
      
   //   cout << "pf.values.size: "  << pf.values.size() << endl;
      
     /*for (size_t j = 0; j < pf.values.size(); j++)
        {
         qDebug() << pf.values[j] << endl;   
      
        }
*/
      
  //     cout << "!!!!!! " << pf.values["@artist"] << endl;
       
       
    //   cout << pf.get_string ("@artist", "1") << endl;
  //     cout << pf.get_string ("@title", "1") << endl;
      
//      for (size_t j = 0; j < pf.values.size(); j++)

      /*
        
       TagLib::FileRef f (fname.c_str());
     
       TagLib::String ts (pf.get_string ("@artist", "1"), TagLib::String::Type::UTF8);
       f.tag()->setArtist (ts);
       f.tag()->setTitle (pf.get_string ("@title", "1"));

       f.save();
   
       cout << "tag saved" << endl;
      */
     }
  
  
  return 0;
}
