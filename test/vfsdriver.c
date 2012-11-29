/*
 * File: vfsdriver.c
 *
 * Description: This is a driver program for testing your VFS system using an interaction script as input
 * You need to make additional calls to your respective functions as noted in the comments below
 * Make sure the output you display is exactly as per the given specifications for you. Do NOT print
 * any extra output (like debug messages) in the final version of your driver program. You can use this driver program
 * in a in incremental manner as you keep implementing one operator after another. For operators not yet implemented,
 * you can leave the output as given ("TO_BE_DONE"). So you can use this program as your "main" program for testing purposes.
 *
 * DO NOT write the full code for operators in the driver program! You must only CALL your functions from here.
 *
 * Usage: vfsdriver <scriptfilename>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/FileOpns.h"
#include "../include/DirOpns.h"
#include "../include/Filesystem.h"
#include "../include/vfs_errorcodes.h"
#include "../include/Bst_test.h"

#define BUFSIZE 200
#define CMDSIZE 30
#define PARSIZE 100

void createvfs ( char *P1, int P2 );
void mountvfs ( char *P1 );
void unmountvfs ( char *P1 );
void makedir ( char *P1, char *P2 );
void deletedir ( char *P1 );
void movedir ( char *P1, char *P2 );
void listdir ( char *P1, int P2, char *P3 );
void addfile ( char *P1, char *P2, char *P3 );
void listfile ( char *P1, char *P2 );
void updatefile ( char *P1, char *P2 );
void removefile ( char *P1 );
void movefile ( char *P1, char *P2 );
void copyfile ( char *P1, char *P2 );
void exportfile ( char *P1, char *P2 );
void searchfile ( char *P1, char *P2 );
void printds();

void processcommand( char *command, char *P1, char *P2, char *P3 );

int main( int argc, char *argv[] )
{
    FILE *scriptfp;
    char linebuffer[BUFSIZE];
    char command[CMDSIZE], par1[PARSIZE], par2[PARSIZE], par3[PARSIZE];
    char *token;
    //HARDCODING
//    argc = 2;
//    argv[1] = "./test/vfstestdata2/group20_06.in";
    if( argc != 2 )
    {
        printf("%d",argc);
        fprintf(stderr,"Usage: vfsdriver <scriptfile>\n");
        return(1);
    }

    if( (scriptfp=fopen(argv[1],"r")) == NULL )
    {
        fprintf(stderr,"Unable to open script file: %s\n", argv[1]);
        return(2);
    }

    while( fgets(linebuffer, sizeof(linebuffer), scriptfp) != NULL )
    {
        //printf("\nProcessing: %s", linebuffer);
        /* This output is for debugging... do not uncomment in final version */
        /*
        		printf("==================================================\n");
        		printf("Processing: %s", linebuffer);
        		printf("==================================================\n");
        */
        /* Remove the extra newline character in the end of line */
        linebuffer[ strlen(linebuffer)-1 ] = '\0';

        /* Get the command and the parameters using tokenizer */
        strcpy( command, (token = strtok(linebuffer, " ")) == NULL ? "" : token );

        strcpy( par1, (token = strtok(NULL, " ")) == NULL ? "" : token );
        strcpy( par2, (token = strtok(NULL, " ")) == NULL ? "" : token );
        strcpy( par3, (token = strtok(NULL, " ")) == NULL ? "" : token );

//		printf("Command:%s:p1:%s:p2:%s:p3:%s\n",command, par1, par2, par3);

        processcommand( command, par1, par2, par3 );
    }
    return 0;
}

void processcommand( char *command, char *P1, char *P2, char *P3 )
{
    if( strcmp(command, "createvfs") == 0 )
    {
        if(strcmp(P1,"")==0 || strcmp(P2 , "")==0)
        {
            printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_00);
        }
        else
        {
            int size = atoi(P2);
            createvfs (P1,size);
        }
    }
    else if( strcmp(command, "mountvfs") == 0 )
    {
        if(strcmp(P1,"")==0)
        {
            printf("\nmountvfs_FAILURE "ERR_VFS_MOUNT_00);
        }
        else
        {
            mountvfs (P1);
        }
    }
    else if( strcmp(command, "unmountvfs") == 0 )
    {
        if(strcmp(P1,"")==0)
        {
            printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_00);
        }
        else
        {
            unmountvfs (P1);
        }
    }
    else if( strcmp(command, "makedir") == 0 )
    {
        if(strcmp(P1,"")==0 || strcmp(P2 , "")==0)
        {
            printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_00);
        }
        else
        {
            makedir (P1,P2);
        }
    }

    else if( strcmp(command, "deletedir") == 0 )
    {
        if(strcmp(P1,"")==0)
        {
            printf("\ndeletedir_FAILURE "ERR_VFS_DELETEDIR_00);
        }
        else
        {
            deletedir (P1);
        }

    }
    else if( strcmp(command, "movedir") == 0 )
    {
        if(strcmp(P1,"")==0 || strcmp(P2 , "")==0)
        {
            printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_00);
        }
        else
        {
            movedir (P1,P2);
        }
    }
    else if( strcmp(command, "listdir") == 0 )
    {
        int flag = atoi(P2);
        if(strcmp(P1,"")==0 || strcmp(P3 , "")==0 || strcmp(P2,"")==0)
        {
            printf("\nlistdir_FAILURE "ERR_VFS_MOVEDIR_00);
        }
        else
        {
            listdir (P1,flag,P3);
        }
    }
    else if( strcmp(command, "addfile") == 0 )
    {
        if((strcmp(P1, "") == 0 )|| (strcmp(P2, "") == 0) || (strcmp(P3, "") == 0))
        {
            printf("\naddfile_FAILURE "ERR_VFS_ADDFILE_00);
        }
        else
        {
            addfile(P1,P2,P3);
        }
    }
    else if( strcmp(command, "listfile") == 0 )
    {
        if(strcmp(P1,"")==0 || strcmp(P2 , "")==0)
        {
            printf("\nlistfile_FAILURE "ERR_VFS_LISTFILE_00);
        }
        else
        {
            listfile (P1,P2);
        }
    }
    else if( strcmp(command, "updatefile") == 0 )
    {
        if((strcmp(P1, "") == 0 )|| (strcmp(P2, "") == 0))
        {
            printf("\nupdatefile_FAILURE "ERR_VFS_UPDATEFILE_00);
        }
        else
        {
            updatefile (P1,P2);
        }
    }
    else if( strcmp(command, "removefile") == 0 )
        if((strcmp(P1, "") == 0 )|| (strcmp(P2, "") != 0))
        {
            printf("\nremovefile_FAILURE "ERR_VFS_REMOVEFILE_00);
        }
        else
        {
            removefile (P1);
        }
    else if( strcmp(command, "movefile") == 0 )
    {
        if((strcmp(P1, "") == 0 )|| (strcmp(P2, "") == 0))
        {
            printf("\nmovefile_FAILURE "ERR_VFS_MOVEFILE_00);
        }
        else
        {
            movefile (P1,P2);
        }
    }
    else if( strcmp(command, "copyfile") == 0 )
        if((strcmp(P1, "") == 0 )|| (strcmp(P2, "") == 0))
        {
            printf("\ncopyfile_FAILURE "ERR_VFS_COPYFILE_00);
        }
        else
        {
            copyfile (P1,P2);
        }
    else if( strcmp(command, "exportfile") == 0 )
    {
        if(strcmp(P1, "")==0 || strcmp(P2, "")==0)
        {
            printf("\nexportfile_FAILURE "ERR_VFS_EXPORTFILE_00);
        }
        else
        {
            exportfile(P1,P2);
        }
    }
    else if( strcmp(command, "searchfile") == 0 )
    {
        if((strcmp(P1, "") == 0 )|| (strcmp(P2, "") == 0))
        {
            printf("\nsearchfile_FAILURE "ERR_VFS_SEARCHFILE_00);
        }
        else
        {
            searchfile (P1,P2);
        }

    }
    else if(strcmp(command, "testbst") == 0 )
    {
        bst_test_main();
    }
    else if(strcmp(command, "printds") == 0 )
    {
        printds();
    }
    else
        printf("Ignoring invalid command %s\n", command);
}

void createvfs ( char *P1, int P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if (create_vfs(P1, P2) == 0)
    {
        printf("\ncreatevfs_SUCCESS");
    }
}

void mountvfs ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
//	printf("mountvfs_TO_BE_DONE\n");
    if (mount_vfs(P1) == 0)
    {
        printf("\nmountvfs_SUCCESS");
    }

}

void unmountvfs ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
//	printf("unmountvfs_TO_BE_DONE\n");
    if (unmount_vfs(P1) == 0)
    {
        printf("\nunmountvfs_SUCCESS");
    }
}

void makedir ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("makedir_TO_BE_DONE\n");
    if (make_dir(P1, P2) == 0)
    {
        printf("\nmakedir_SUCCESS");
    }
}

void deletedir ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("deletedir_TO_BE_DONE\n");
    if (delete_dir(P1) == 0)
    {
        printf("\ndeletedir_SUCCESS");
    }
}

void movedir ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("movedir_TO_BE_DONE\n");
    if (move_dir(P1, P2) == 0)
    {
        printf("\nmovedir_SUCCESS");
    }
}

void listdir ( char *P1, int P2, char *P3 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("listdir_TO_BE_DONE\n");
    if (list_dir(P1, P2, P3) == 0)
    {
        printf("\nlistdir_SUCCESS");
    }
}

void addfile ( char *P1, char *P2, char *P3 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if (add_file(P1, P2, P3) == 0)
    {
        printf("\naddfile_SUCCESS");
    }
}

void listfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if (list_file(P1, P2) == 0)
    {
        printf("\nlistfile_SUCCESS");
    }
}

void updatefile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if (update_file(P1, P2) == 0)
    {
        printf("\nupdatefile_SUCCESS");
    }
}

void removefile ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("removefile_TO_BE_DONE\n");
    if (remove_file(P1) == 0)
    {
        printf("\nremovefile_SUCCESS");
    }
}

void movefile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //move_file(P1,P2);
    if (move_file(P1, P2) == 0)
    {
        printf("\nmovefile_SUCCESS");
    }
}

void copyfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
   if (copy_file(P1, P2) == 0)
    {
        printf("\ncopyfile_SUCCESS");
    }
}

void exportfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if (export_file(P1, P2) == 0)
    {
        printf("\nexportfile_SUCCESS");
    }
}

void searchfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if (search_file(P1, P2) == 0)
    {
        printf("\nsearchfile_SUCCESS");
    }
}

void printds()
{
    print_ds();
}



