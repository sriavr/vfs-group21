#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Filesystem.h"

const char * generate_rand_string()
{
    int length = rand()%10 + 6;
    char * str = (char *) malloc(sizeof(char)*length);
    int i;
    for(i=0; i<length -1; i++)
    {
        str[i] = 'a' + rand()%26;
    }
    str[i] = '\0';
    return str;
}

char* join_name_path(char * name_with_path, char * path, char * name)
{
    if(name_with_path == NULL || path == NULL || name == NULL)
    {
        return NULL;
    }
    int path_length = strlen(path);
    int name_length = strlen(name);
    int length = 0;
    char * key = NULL;

    if(path[path_length - 1] == '/')
    {
        length = path_length + name_length;
        key = calloc((length+1),sizeof(char));
        strcpy(key, path);
        strcat(key, name);
    }
    else
    {
        length = path_length + name_length;
        key = calloc((length+2),sizeof(char));
        strcpy(key, path);
        strcat(key, "/");
        strcat(key, name);
    }
    strcpy (name_with_path, key);
    free(key);
    return name_with_path;
}

void split_name_path(char * name_with_path, char * path, char * name)
{
    if(name_with_path == NULL || path == NULL || name == NULL)
    {
        return;
    }

    if(strlen(name_with_path) == 1)
    {
        strcpy(name, "");
        strcpy(path, name_with_path);
        return;
    }

    char * pch, * last_token, *temp;
    int len = strlen(name_with_path);
    if((len > 1) && (name_with_path[len - 1] == '/'))
    {
        name_with_path[len - 1] = '\0';
    }
    len = strlen(name_with_path);
    //printf("modified strin: %s ", name_with_path );
    temp = malloc(sizeof(char) * (len + 1));
    strcpy(temp, name_with_path);

    pch = strtok (temp, "/");

    while (pch != NULL)
    {
        last_token = pch;
        //printf ("%s\n",pch);
        pch = strtok (NULL, "/");
    }
    int temp_len = strlen(name_with_path) - strlen(last_token);
    strncpy(path ,name_with_path, temp_len);
    path[temp_len] = '\0';
    strcpy(name, last_token);

    free(temp);
}

void correct_dir_path(char dir_path[FULLPATH_MAX_SIZE])
{
    if(dir_path == NULL || (strcmp(dir_path, "/") == 0))
        return;

    char temp_path[FULLPATH_MAX_SIZE];
    if(dir_path[0] != '/')
    {
        strcpy(temp_path, "/");
        strcat(temp_path, dir_path);
    }
    else
    {
        strcpy(temp_path, dir_path);
    }

    int length = strlen(temp_path);
    if(temp_path[length - 1] != '/')
    {
        strcat(temp_path, "/");
    }

    strcpy(dir_path, temp_path);
}

void correct_file_path(char file_path[FULLPATH_MAX_SIZE])
{
    if(file_path == NULL || (strcmp(file_path, "/") == 0))
        return;

    char temp_path[FULLPATH_MAX_SIZE];
    if(file_path[0] != '/')
    {
        strcpy(temp_path, "/");
        strcat(temp_path, file_path);
    }
    else
    {
        strcpy(temp_path, file_path);
    }

    strcpy(file_path, temp_path);
}

//int main()
//{
//    char name[128], path[256], name_with_path[256];
//    strcpy(name, "harsha.txt");
//    strcpy(path, "/etc/lib/vikas/");
//    join_name_path(name_with_path, path, name);
//    printf ("name_with_path: %s\n", name_with_path);
//    printf ("name: %s\n", name);
//    printf ("path: %s\n\n", path);
//
//    strcpy(name, "file1.txt");
//    strcpy(path, "/etc/abc");
//    join_name_path(name_with_path, path, name);
//    printf ("name_with_path: %s\n", name_with_path);
//    printf ("name: %s\n", name);
//    printf ("path: %s\n\n", path);
//
//    strcpy(name, "song.mp3");
//    strcpy(path, "/");
//    join_name_path(name_with_path, path, name);
//    printf ("name_with_path: %s\n", name_with_path);
//    printf ("name: %s\n", name);
//    printf ("path: %s\n\n", path);
//
//    strcpy(name, "file4.txt");
//    strcpy(path, "/etc/abc/rocking/hyderabad");
//    join_name_path(name_with_path, path, name);
//    split_name_path(name_with_path, path, name);
//    printf ("name_with_path: %s\n", name_with_path);
//    printf ("name: %s\n", name);
//    printf ("path: %s\n\n", path);
//
//    strcpy(name, "");
//    strcpy(path, "/");
//    join_name_path(name_with_path, path, name);
//    split_name_path(name_with_path, path, name);
//    printf ("name_with_path: %s\n", name_with_path);
//    printf ("name: %s\n", name);
//    printf ("path: %s\n\n", path);
//
//    strcpy(name, "");
//    strcpy(path, "");
//    strcpy(name_with_path, "/home/sridhar/");
//    split_name_path(name_with_path, path, name);
//    printf ("name_with_path: %s\n", name_with_path);
//    printf ("name: %s\n", name);
//    printf ("path: %s\n\n", path);
//
//}
