#ifndef DIROPNS_H_INCLUDED
#define DIROPNS_H_INCLUDED

int make_dir(char *parent_path, char *dir_name);

int delete_dir(char *dir_path);

int move_dir(char * src_path, char * dest_path);

int list_dir(char *dir_path, int flag, char * txt_file_path);

void correct_path(char path[]);

int displaynary();
#endif
