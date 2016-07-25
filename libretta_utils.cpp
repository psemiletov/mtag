/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/


#include <iostream>
#include <locale> 
#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>  // for FILENAME_MAX

#include <dirent.h>


#ifdef WINDOWS
#include <direct.h>
#define get_cur_dir _getcwd
#else
#include <unistd.h>
#define get_cur_dir getcwd
#endif


using namespace std;


string get_2char_locale()
{
  locale l("");
  string nm = l.name();
  string nn;
  nn += nm[0];
  nn += nm[1];
  return nn;  
}


string get_home_dir()
{
  string homedir = getenv ("HOME");
  return homedir;  
}


string current_path()
{
  char path [FILENAME_MAX];
  string result;
 
  if (! get_cur_dir (path, sizeof (path)))
     return result;

  result = path;
  return result;
}


vector <string> files_get_list (const string &path, const string &ext) //ext with dot: ".txt"
{
  DIR *directory;
  struct dirent *dir_entry;

  vector <string> result;
  
  directory = opendir(path.c_str());
  if (! directory)
     {
      closedir (directory);
      return result;
     }

   while (dir_entry = readdir (directory)) 
         {
          // std::cout << dir_entry->d_name << std::endl;
          string t = dir_entry->d_name;
          if (t.rfind (ext) != string::npos)
            result.push_back (path + "/" + t);
         }

   closedir (directory);
   return result;
}
