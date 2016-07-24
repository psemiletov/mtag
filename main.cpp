#include <iostream>
#include <string>

#include "libretta_string_utils.h"


using namespace std;

int main (int argc, char *argv[])
{

  string s = string_file_load (argv[1]);
  cout << s << endl; 
 
  return 0;
}
