/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#ifndef LIBRETTA_STRING_UTILS_H
#define LIBRETTA__STRING_UTILS_H


#include <iostream>
#include <locale> 

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>


using namespace std;

vector<string> &split (const string &s, char delim);

string string_file_load (const string &fname);


#endif