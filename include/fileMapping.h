#pragma once
#include <extfat.h>
char *map_entire_file(fileInfo *disk);
/*
this reads the contents of a file into a char * (entire file is in a huge block of memory)
input_file is a filename


*/

void copy_file(fileInfo *disk, fileInfo *disk_copy);
/*
this copies file 1 into file 2
the char stars are the names of the files

*/
