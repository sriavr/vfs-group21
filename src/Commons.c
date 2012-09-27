#include <stdlib.h>
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
