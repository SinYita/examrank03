#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>



void filter(char *buffer, const char *t)
{
    int t_len = strlen(t);

    int i = 0;
    while(buffer[i])
    {
        int j = 0;
        while(buffer[i + j] == t[j]) j ++;
        if(j == t_len)
        {
            int k = 0;
            while(k < t_len)
            {
                printf("*");
                k ++;
            }
            i += t_len;
        }
        else 
        {
            printf("%c",buffer[i]);
            i ++;
        }
    }
}

int main(int argc, char **argv)
{
    if(argc !=2 || argv[1][0] == '\0')
        return 1;

    char read_temp[BUFFER_SIZE];
    char *temp;
    char *result = NULL;
    int total_read = 0;
    size_t bytes;

    while((bytes = read(0,read_temp,BUFFER_SIZE)))
    {
        temp = realloc(result,total_read + bytes + 1);
        if(!temp)
        {
            free(result);
            perror("realloc");
            return 1;
        }
        result = temp;
        memmove(result + total_read, read_temp,bytes);
        total_read += bytes;
        result[total_read] = '\0';
    }
    if(bytes < 0)
    {
        perror("read");
        free(result);
        return 1;
    }
    if(!result)
        return 0;
    filter(result,argv[1]);
    free(result);
    return 0;
}