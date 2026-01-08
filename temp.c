// n_queens
int is_safe(int row,int col)
{
    for(int c = 0; c < col;c ++)
    {
        int r = board[col];
        if(r == row || abs(r - row) == abs(c - col)) return 0;
    }
    return 1;
}
void solve(int col)
{
    if(col == n) print();
    for(int row = 0;row < n;row ++)
    {
        if(is_safe(row,col))
        {
            board[col] = row;
            solve(col + 1);
        }
    }
}


// permutations'


void solve(char *str, int len, int *used, char *perm, int pos)
{
    if(pos == len) print()
    for(int i = 0;i < len ;i ++)
    {
        if(used[i]) continue;
        used[i] = 1;
        perm[pos] = str[i];
        solve(str,len,used,perm,pos + 1);
        used[i] = 0;
    }
}

// powerset

void solve(int idx, int sum, int subset_size)
{
    if(idx == n) print()
    solve(idx + 1, sum,subset_size); // don't pick up
    subset[subset_size] = set[idx];
    solve(idx + 1, sum + set[idx],subset_size + 1); // pick up at idx
}

// rip

void solve(char *str, int res, int l, int r, int pos)
{
    if(l + r == res && ok(str)) print()
    for(int i = pos; i < n;i ++)
    {
        char backup = str[i];
        str[i] = ' ';
        solve(str, res, l + (backup == '('),r + (backup == ')'),i + 1);
        str[i] = backup;
    }
}

//tsp

void solve(City cities, int *path, int n,int pos, float * res)
{
    if(pos == n) print();
    for(int i = pos; i < n; i ++)
    {
        swap(path[pos],path[i]);
        solve(cities,path,n,pos + 1,res);
        swap(path[pos],path[i]);
    }
}
