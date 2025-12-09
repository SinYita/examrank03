/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 * 
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
//   int i = 0;
//   while(s[i] != c)
//     i++;
//   if (s[i] == c)
//     return s + i;
//   else
//     return NULL;
    int i = 0;
    if(!s) return NULL;
    while(s[i] != '\0')
    {
        if(s[i] == char (c))
            return (s + i);
        i ++;
    }
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
//   while(--n > 0)
//     ((char *)dest)[n - 1] = ((char *)src)[n - 1];
//   return dest;
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
//   size_t res = 0;
//   while (*s)
//   {
//     s++;
//     res++;
//   }
//   return res;
    size_t res = 0;
    if(!s) return res;
    while(s[res ++]!='\0')
    return res;
}
// 0 for failure and 1 for success
int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1= 0;
    if(!*s1) size1 = 0;
    else size1 = ft_strlen(*s1);
    char *temp = malloc(size1 + size2 + 1);
    if(!temp)
        return 0;
    if(*s1)
        ft_memcpy(temp,*s1, size1);
    ft_memcpy(temp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 1; 
}

int str_append_str(char **s1, char *s2)
{
    size_t len2 = ft_srlen(s2);
  return str_append_mem(s1, s2, len2);
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if(!dest || !src)
        return NULL;
    if(dest > src)
    {
        i = n;
        while(i > 0)
        {
            i --;
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
    else
    {
        while(i < n)
        {
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *line = NULL;
  char *temp;

  while(1)
  {
    temp = ft_strchr(b,'\n');
    if(temp)
    {
        if(!str_append_mem(line,temp,temp - b + 1)) // if failed
            return (free(line),NULL);
        ft_memove(b,temp + 1, ft_strlen(temp + 1) + 1);

    }
    if(!str_append_str(&line,b))
        return NULL;
    int read_ret = read(fd,b,BUFFER_SIZE);
    if(read_ret <= 0)
    {
        b[0] = '\0';
        if(line && *line)
            return line;
        free(line)
    }
  }
  while(!tmp)
  {
    if (!str_append_str(&ret, b))
      return (NULL);
    int read_ret = read(fd, b, BUFFER_SIZE);
    if (read_ret == -1)
      return (NULL);
    b[read_ret] = 0;
  }
  if (!str_append_mem(&ret, b, tmp - b + 1))
  {
    free(ret);
    return NULL;
  }
  return ret;
}