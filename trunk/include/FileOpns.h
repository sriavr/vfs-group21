#ifndef FILEOPNS_H_INCLUDED
#define FILEOPNS_H_INCLUDED

int add_file(char *dest_dir_path , char* file_name , char* data_file_path);
void export_file(char *source_file_path, char *destination_file_path);
int search_file(char *filename, char *outputfile);
int list_file(char * file_path , char* output_file);
void copy_file(char *source_file_with_path , char *destination_file_path);
void move_file(char *source_file_with_path , char *destination_with_path);
void update_file( char *souce_file_with_path, char *data_file);

#endif