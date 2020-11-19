## DP

`dp[i][j]` -> minimal `low` of a prefix that with `i` in original sequence
and `j` in external sequence(all 1s)


switch `fr[i][j]`:

+ 0: from `fr[i-1][j]`

+ 1: from `fr[i][j-1]`
