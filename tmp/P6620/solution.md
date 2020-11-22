---
title: 2020联考A卷T2
date: 2020-11-22 18:15:24
mathjax: true
tags:
  - Math
---

# [[省选联考 2020 A 卷] 组合数问题](https://www.luogu.com.cn/problem/P6620)

## Description

给定 $n,x,p$ 和一个 $m$ 度多项式，求：

$$
\sum_{k=0}^{n} ​f(k) x^k \binom{n}{k}
$$

在模 $p$ 意义下的值。

## Tutorial

把 $f$ 展开：

$$
f(k) = \sum_{0 \leq i \leq m} a_i k^i \\
\begin{aligned}
\sum_{k=0}^{n} ​f(k)  x^k  \binom{n}{k}
&= \sum_{k=0}^{n}\sum_{i=0}^ma_i k^i  x^k  \binom{n}{k} \\
&= \sum_{i=0}^{m}a_i \sum_{k=0}^{n}k^i  x^k  \binom{n}{k}
\end{aligned}
$$

接下来考虑如何处理右半边的这个和式：

发现其中有 $x^k \times \binom{n}{k}$，尝试牛顿二项式定理：

$$
(1+x)^n = \sum_{k=0}^{n}\binom{n}{k} x^k
$$

要凑出 $k^i$，首先将 $k^i$ 转成下降幂：

$$
k^i = \sum_{j=0}^{j\leq i} \begin{Bmatrix} {i\\j} \end{Bmatrix}
 k^\underline{j}
$$

然后要在牛顿二项式定理的右边产生一个 $j$ 次下降幂，可以对 $x$ 求 $k$ 次导然后再乘 $x^j$：

$$
\begin{aligned}

\frac{\mathrm{d}^j}{\mathrm{d}x} (1+x)^n &=
\sum_{k=0}^{n} \frac{\mathrm{d}^j}{\mathrm{d}x} \binom{n}{k} x^k
\\
n^\underline{j} (1+x)^{n-j} &=
\sum_{k=0}^n k^\underline{j} \binom{n}{k} x^{k-j}
\\
n^\underline{j} x^j (1+x)^{n-j} &=
\sum_{k=0}^n k^\underline{j} \binom{n}{k} x^{k}

\end{aligned}
$$

所以我们就有：

$$
\begin{aligned}
\sum_{k=0}^{n} k^i x^k \binom{n}{k} &=
\sum_{k=0}^{n}\sum_{j=0}^{i} \begin{Bmatrix} i\\j \end{Bmatrix} k^\underline{j}
  \binom{n}{k} x ^k \\
&= \sum_{j=0}^{i} \begin{Bmatrix} i\\j \end{Bmatrix}
  \sum_{k=0}^{n}k^{\underline{j}} \binom{n}{k} x^k \\
&= \sum_{j=0}^i \begin{Bmatrix} i\\j \end{Bmatrix}
  n^\underline{j} x^j (1+x)^{n-j}
\end{aligned}
$$


带回原式，答案即为：

$$
\sum_{i=0}^{m}a_i     
  \sum_{j=0}^i \begin{Bmatrix} i\\j \end{Bmatrix}
  n^\underline{j} x^j (1+x)^{n-j}
$$

$O(n^2)$ 预处理第二类斯特林数，$O(n)$ 预处理 $n^\underline{j},x^j,(1+x)^{n-j}$，
可以 $O(n^2)$ 完成计算。

## Code

```cpp
#include <bits/stdc++.h>

// 见 https://gitee.com/coderoj/code/blob/master/creats/Intm.h
#include "/home/jack/code/creats/Intm.h"

const int N = 1005;
typedef Intm::Intm Int;
int n, p, m;
Int a[N], x;

// 预处理第二类斯特林数
Int s[N][N];
void
initSt()
{
  s[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    s[i][0] = 0;
    for (int j = 1; j <= i; ++j) {
      s[i][j] = s[i - 1][j - 1] + Int(j) * s[i - 1][j];
    }
  }
}
 
// 预处理幂次
Int pow_x[N], pow_xp[N];
void
initPow()
{
  pow_x[0] = 1;
  pow_xp[0] = (x+Int(1)).pow(n-m);
  for (int i = 1; i <= m; ++i) {
    pow_x[i] = pow_x[i - 1] * x;
    pow_xp[i] = pow_xp[i - 1] * (x + Int(1));
  }
}

// 预处理n的下降幂
Int n_ds[N];
void
initNDs()
{
  n_ds[0] = 1;
  for (int i = 1; i <= m; ++i) {
    n_ds[i] = n_ds[i - 1] * Int(n - i + 1);
  }
}

Int
getCoe(int i)
{
  Int res = 0;
  for (int j = 0; j <= i; ++j) {
    res += s[i][j] * n_ds[j] * pow_x[j] * pow_xp[m - j];
  }
  return res;
}

void
solve()
{
  n = read();
  x = read();
  p = read();
  m = read();
  for (int i = 0; i <= m; ++i)
    a[i] = read();
  Int::setMod(p);
  initSt();
  initPow();
  initNDs();
  Int ans = 0;
  for (int i = 0; i <= m; ++i) {
    ans += a[i] * getCoe(i);
  }
  printf("%d\n", static_cast<int>(ans));
}
```
