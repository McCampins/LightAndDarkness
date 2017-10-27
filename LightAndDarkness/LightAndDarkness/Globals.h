#ifndef __Globals__
#define __Globals__

#define NDEBUG //Invalidate asserts

#include <string>
#include <vector>

bool Same(const std::string& a, const std::string& b);
bool Same(const char* a, const char* b);
bool Same(const std::string& a, const char* b);
bool Same(const char* a, const std::string& b);
void Tokenize(const std::string& line, std::vector<std::string>& args);

#endif
