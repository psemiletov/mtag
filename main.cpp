#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "libretta_utils.h"
#include "libretta_string_utils.h"
#include "libretta_pairfile.h"



using namespace std;

int main (int argc, char *argv[])
{
  if (argc < 3) 
  {
   cout << "mtag RULESFILE filemask" <<  endl;
   return 0;
  }
 
 
 
  string rules_file = argv[1];
  string mask = argv[2];

  
  std::vector <string> files = files_get_list (current_path(), mask);

  //std::vector< std::string>::sort(files.begin(), files.end());
  
  std::sort(files.begin(), files.end());
  
  /*
  for (const auto &t: files)
      {  
       cout << t << endl;
     
      }
  */
  string rules_file_data = string_file_load (rules_file);
 
  
   
  vector<string> vs = string_split (rules_file_data, "###");
   
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

  for (size_t i = 0; i < vs.size(); i++)
     {
      string fname = files[i];
      
     
      CPairFile pf (vs[i], true);
      
       cout << pf.get_string ("@artist", "1") << endl;
       cout << pf.get_string ("@title", "1") << endl;
      
       
   
     }
  
  
  return 0;
}
