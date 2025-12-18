/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 * 
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"
#include <fcntl.h>

char *ft_strchr(char *s, int c)
{
    if(!s)
        return NULL;
    int i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == (char) c)
        {
            return s + i;
        }
        i ++;
    }
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    while(i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i ++;
    }
    return (dest);
}

size_t ft_strlen(char *s)
{
  size_t res = 0;
  if(!s)
    return 0;
  while(s[res]) res ++;
  return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{

  size_t size1 = 0;
  if(*s1)
    size1 = ft_strlen(*s1);
  char *tmp;
  tmp  = malloc(size1 + size2 + 1);
  if (!tmp)
    return 0;
if(*s1)
    ft_memcpy(tmp, *s1, size1);
  ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
  *s1 = tmp;
  return 1; 
}

int str_append_str(char **s1, char *s2)
{
    size_t len2 = ft_strlen(s2);
  return str_append_mem(s1, s2, len2);
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    if(!src || !dest)
        return NULL;
    size_t i = 0;
  if (dest > src)
  {
    i = n;
     while (i > 0)
    {    i --;
        ((char *)dest)[i] = ((char *)src)[i];
    }
  }
  else
  {
    i = 0;
    while(i < n)
    {
         ((char *)dest)[i] = ((char *)src)[i];
         i ++;
    }
  }
   
  return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *line = NULL;
  char *tmp;
  int read_ret = 0;

  while(1)
  {
    tmp  = ft_strchr(b, '\n');
    if(tmp)
    {
         if(!str_append_mem(&line, b, tmp - b + 1))
         {
            free(line);
            return NULL;
         }
         ft_memmove(b,tmp + 1,ft_strlen(tmp + 1) + 1);
         return line;
    }
    if(!str_append_str(&line, b))
    {
        free(line);
        return NULL;
    }
    b[0] = '\0';
    read_ret = read(fd,b,BUFFER_SIZE);
    if(read_ret <=0)
    {
        b[0] = '\0';
        if(line && *line)
            return line;
       free(line);
            return NULL;
    }
     b[read_ret] = '\0';
   
  }
}

int main()
{
    int fd = open("1.txt",O_RDONLY);
    char *line;
    while((line = get_next_line(fd)) > 0)
    {
        printf("%s",line);
        free(line);

    }
    close(fd);
    return 0;
}
 