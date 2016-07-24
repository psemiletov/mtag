#include <iostream>
#include <string>
#include <vector>

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

  string rules_file_data = string_file_load (rules_file);
 
  vector<string> vs = string_split (rules_file_data, "###");
  
 
  for (auto &element: vs) // access by reference to avoid copying
      {
       if (element.empty())
          continue;
       
      // cout << element <<  endl;  
       
       
  
       CPairFile pf (element, true);
       cout << pf.get_string ("@artist", "1") << endl;
       cout << pf.get_string ("@title", "1") << endl;
       
       //cout << pf.values.size() << endl;
       
      }
  
  
  return 0;
}
