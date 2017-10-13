#ifndef __Globals__
#define __Globals__

#define BACKSPACE '\b'
#define RETURN '\r'
#define BLANK ' ';

#include <string>
#include <vector>

using namespace std;

bool Same(const string& a, const string& b);
bool Same(const char* a, const char* b);
bool Same(const string& a, const char* b);
bool Same(const char* a, const string& b);
void Tokenize(const string& line, vector<string>& args);

#endif
