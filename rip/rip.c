#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// char table[100][15];
// int idx = 0;

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i]) i ++;
    return i;
}
// int diff(char *str, char *src)
// {
//     for(int i = 0;i < ft_strlen(str);i ++)
//     {
//         if(str[i] != src[i])
//             return 1;
//     }
//     return 0;
// }
// int in_table(char *str)
// {
//     for(int i = 0; i < idx;i ++)
//     {
//         if(diff(str, table[i]) == 0)
//             return 1;
//     }
//     return 0;
// }
// void join_table(char *str)
// {
//     for(int i = 0;i < ft_strlen(str);i ++)
//     {
//         table[idx][i] = str[i];
//     }
//     table[idx][ft_strlen(str)] = '\0';
//     idx ++;
// }

int min_remove(char *str)
{
    int balance = 0;
    int unbalance = 0;
    for(int i = 0;str[i];i ++)
    {
        if(str[i] == '(')
            balance ++;
        else if(str[i] == ')')
        {
            if(balance > 0)
                balance --;
            else
                unbalance ++;
        }
    }
    return balance + unbalance;
}
int ok(char *str)
{
    if(min_remove(str) == 0)
        return 1;
    return 0;   
}
// void print_result(char *str)
// {
//     for(int i = 0;str[i]; i ++)
//     {
//         write(1, &str[i], 1);
//     }
// }
int cnt = 0;
void dfs(char *str,int res,int l, int r,int depth)
{
    if(l + r == res && ok(str))
    {
        puts(str);
        //join_table(str);
        return;
    }
    for(int i = depth;i < ft_strlen(str); i++)
    {
        char backup = str[i];
        str[i] = ' ';
        dfs(str,res,l + (backup == '('),r + (backup == ')'),i + 1);
        // if(str[i] == '(')
        // {
        //     str[i] = ' ';
        //     dfs(str,res,l + 1,r,i + 1);
        //     str[i] = '(';
        // }
        // else if(str[i] == ')')
        // {
        //     str[i] = ' ';
        //     dfs(str,res,l,r + 1,i + 1);
        //     str[i] = ')';
        // }
        str[i] = backup;
    }
}
int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;
    char *str = argv[1];
    int rem = min_remove(str);
    dfs(str,rem,0,0,0);
    return 0;
}