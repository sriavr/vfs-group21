//void fsystem_ui()
//{
//    char full_path_file_name[150];
//    int file_length,ret=0;
//
//    printf("\nEnter the file name with full path: ");
//    scanf("%s",full_path_file_name);
//
//    printf("\nEnter size of file in Bytes: ");
//    scanf("%d",&file_length);
//
//    //create a virtual file system
//    ret=create_vfs(full_path_file_name,file_length);
//
//    if(ret==0)
//    {
//        printf("\nSuccessfully created the file system\n");
//    }
//    else
//    {
//        printf("\nError while creating the file system\n");
//    }
//
//    //test the newly created file system
//    test_vfs(full_path_file_name);
//
//    //test case for read_meta_header() function
//    test_read_meta_header(full_path_file_name);
//
//    //test case for read_header() function
//    test_read_header(full_path_file_name);
//
//    //test case for read_block_array
//    //test_read_block_array(full_path_file_name);
//
//    //check if mount is working
//    mount_vfs(full_path_file_name);
//
//    unmount_vfs(full_path_file_name);
//}

//void test_vfs(char fullpath[150])
//{
//    /*  FILE *fp;
//      meta_header *mh;
//      header *hdr;*/
//    FILE *fp;
//    //allocate memory for meta header
//    mh=(meta_header*) malloc(sizeof(meta_header));
//
//    fp = fopen(fullpath,"r+b");
//    //read and copy the meta header to mh
//    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
//    {
//        printf("Failed to read meta header");
//        fclose(fp);
//        return;
//    }
//
//    print_meta_header_info(mh);
//
//    //allocate memory for header
//    hdr=(header*) malloc(sizeof(header));
//    //read and copy the header to hdr
//    if(fread(hdr, sizeof(header), 1, fp) != 1)
//    {
//        printf("\nFailed to read header");
//        fclose(fp);
//        return;
//    }
//}



//void test_read_meta_header(char fullpath[150])
//{
//    mh =  read_meta_header(fullpath);
//    if(mh!=NULL)
//    {
//        print_meta_header_info(mh);
//    }
//    else
//    {
//        printf("\n read_meta_header() function failed");
//    }
//}
//
//void test_read_header(char fullpath[150])
//{
//    hdr = read_header(fullpath);
//    if(hdr!=NULL)
//    {
//        print_header_info(hdr);
//    }
//    else
//    {
//        printf("\n read_header() function failed");
//    }
//}
//
//void test_read_block_array(char fullpath[150])
//{
//    block *block_array;
//    block_array = read_block_array(fullpath);
//    int i;
//    if(block_array !=NULL)
//    {
//        for(i=0; i< MAX_NUM_OF_BLOCKS; i++)
//        {
//            print_block(block_array[i]);
//        }
//        printf("\n number of blocks printed: %d", MAX_NUM_OF_BLOCKS);
//    }
//    else
//    {
//        printf("\n read_block_array() function failed");
//    }
//
//}
//
//void print_block(block blk)
//{
//    int i;
//    printf("\nStart of block\n");
//    for(i=0; i< BLOCK_SIZE; i++)
//    {
//        printf("%d",blk.data[i]);
//    }
//    printf("\nEnd of block\n");
//}
//
//
//void print_meta_header_info(meta_header * mh)
//{
//    printf("\ninformation in meta header:");
//    printf("\nfile_system_label: %s", mh -> file_system_label);
//    //printf("\nmax_num_file_descriptors: %ld", mh -> max_num_file_descriptors);
//    printf("\nfile_descriptors_used: %ld", mh -> file_descriptors_used);
//}
//
//void print_header_info(header * hdr)
//{
//    printf("\ninformation in header:");
//    //printf("\nHEADER_TEST_FIELD: %s", hdr -> HEADER_TEST_FIELD);
//}
//
//file_descriptor * create_test_fd_data(file_descriptor * fd_array, long int size)
//{
//    if(fd_array == NULL)
//    {
//        fd_array = calloc(size, sizeof(file_descriptor));
//    }
//    char *temp_file_path;
//    temp_file_path = calloc(150, sizeof(char));
//
//    char * file_type[2] = {"file","dir"};
//    long int i;
//    for(i =0; i < size; i++)
//    {
//        temp_file_path = calloc(150, sizeof(char));
//
//        strcpy(fd_array[i].file_name, generate_rand_string());
//
//        strcat(temp_file_path, "/");
//        strcat(temp_file_path, generate_rand_string());
//        strcat(temp_file_path, "/");
//        strcat(temp_file_path, generate_rand_string());
//        strcat(temp_file_path, "/");
//        strcat(temp_file_path, generate_rand_string());
//        strcpy(fd_array[i].location_full_path, temp_file_path);
//
//        strcpy(fd_array[i].file_type, file_type[rand()%2]);
//        fd_array[i].file_size = rand();
//        fd_array[i].location_block_num = rand();
//    }
//
//    return fd_array;
//}
//
//
//void display_file_descriptor(file_descriptor output)
//{
//
//    printf("Filename: %s\n" , output.file_name);
//    printf("Location: %s\n" , output.location_full_path);
//    printf("Filetype: %s\n" , output.file_type);
//    printf("Block Num: %d\n" , output.location_block_num);
//    printf("Size: %ld\n" , output.file_size);
//
//}
