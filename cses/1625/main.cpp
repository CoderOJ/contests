#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int ans = 0;
int mp[9][9];
char pat[49];
void init()
{
    scanf("%s", pat);
    for (int i = 0; i <= 8; ++i) for (int j = 0; j <= 8; ++j) mp[i][j] = i == 0 || i == 8 || j == 0 || j == 8;
}

bool one_dir(int x, int y)
{
    if (x == 7 && y == 1) return 0;
    int num = 0;
    if (!mp[x - 1][y]) ++num;
    if (!mp[x + 1][y]) ++num;
    if (!mp[x][y - 1]) ++num;
    if (!mp[x][y + 1]) ++num;
    return num == 1;
}

void dfs(int x, int y, int dep)
{
    if (dep == 48 || (x == 7 && y == 1))
    {
        if (dep == 48) ++ans;
        return;
    }
    int u = mp[x - 1][y] == 0;
    int d = mp[x + 1][y] == 0;
    int l = mp[x][y - 1] == 0;
    int r = mp[x][y + 1] == 0;
    char c = pat[dep++];
    mp[x][y] = 1;
    if (u && one_dir(x - 1, y))
    {
        if (c == '?' || c == 'U') dfs(x - 1, y, dep);
        mp[x][y] = 0;
        return;
    }
    if (d && one_dir(x + 1, y))
    {
        if (c == '?' || c == 'D') dfs(x + 1, y, dep);
        mp[x][y] = 0;
        return;
    }
    if (l && one_dir(x, y - 1))
    {
        if (c == '?' || c == 'L') dfs(x, y - 1, dep);
        mp[x][y] = 0;
        return;
    }
    if (r && one_dir(x, y + 1))
    {
        if (c == '?' || c == 'R') dfs(x, y + 1, dep);
        mp[x][y] = 0;
        return;
    }
    if (u && (c == '?' || c == 'U')) dfs(x - 1, y, dep);
    if (d && (c == '?' || c == 'D')) dfs(x + 1, y, dep);
    if (l && (c == '?' || c == 'L')) dfs(x, y - 1, dep);
    if (r && (c == '?' || c == 'R')) dfs(x, y + 1, dep);
    mp[x][y] = 0;
}

void solve()
{
    dfs(1, 1, 0);
    printf("%d\n", ans);
}

int main()
{
    init();
    solve();
    return 0;
}
