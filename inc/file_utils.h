#ifndef __FILE_UTILS__
#define __FILE_UTILS__

#include <stdio.h>

//Returns entire file into allocated buffer. Must free buffer after use
const char* read_entire_file(const char* file_path);

#endif
