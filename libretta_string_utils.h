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

vector<string> string_split (const string &s, char delim);
vector<string> string_split (string s, const string &delim);


string string_file_load (const string &fname);

string string_replace_all (const string &s, const string &from, const string &to);


#endif