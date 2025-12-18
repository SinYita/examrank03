#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 写一个替换t字符串的双指针。
void ft_filter(char *buffer, const char *target)
{
    int i = 0;
    int t_len = strlen(target);
    int j,k;
    while(buffer[i])
    {
        j = 0;
        while(buffer[i + j] == target[j]) j++;
        if(j == t_len)
        {
            k = 0;
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
    // 如果参数不是2或者参数为空，那么就返回1.
    if(argc != 2 || argv[1][0] == '\0')
        return 1;
    char temp[BUFFER_SIZE];
    char *buffer;
    char *result = NULL;
    int total_read = 0;
    ssize_t bytes;
    while((bytes = read(0,temp,BUFFER_SIZE) )> 0)
    {
        buffer = realloc(result,total_read + bytes + 1);
        // 重新分配total + read_size + 1的大小
        if(!buffer) // 如果分配失败
        {
            free(result);
            perror("realloc");
            return 1;
        }
        result = buffer;//将result指向新分配的空间。
        memmove(result + total_read,temp,bytes);//从result[total] 开始，将temp中的bytes放进result。
        total_read += bytes;//更新total
        result[total_read] = '\0';
    }
    if(bytes < 0) // 如果读失败
    {
        perror("read");
        free(result);
        return 1;
    }
    if(!result ) // 如果为空的话返回0
        return 0;
    ft_filter(result,argv[1]);
    free(result); // 记得释放内存
    return 0;
}
