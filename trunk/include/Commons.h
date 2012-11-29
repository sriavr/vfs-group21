#ifndef COMMONS_H_INCLUDED
#define COMMONS_H_INCLUDED

//generates a random string of random length 6 to 15
const char * generate_rand_string();

void split_name_path(char * name_with_path, char * path, char * name);

char* join_name_path(char * name_with_path, char * path, char * name);

void correct_dir_path(char path[]);

void correct_file_path(char path[]);

#endif
