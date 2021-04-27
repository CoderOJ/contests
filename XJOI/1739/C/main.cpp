#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/tmp/Intm/Intm.hpp"
#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"
constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
constexpr Int tab[] = { 0,
#include "tab/tab.hpp"
0};
constexpr int BLOCK =
#include "tab/block.hpp"
; int n, p, c; Int calc (Int x, int c) { if (x == 0) { return 0; } return ((1 - x.pow(c)) / (1 - x) - c * x.pow(c)) / (1 - x); } Int getH (int n) { Int res = tab[n / BLOCK]; for (int i = n / BLOCK * BLOCK + 1; i <= n; ++i) { res += Int (i).inv(); } return res; } void preInit() { } void init() { } void solve() { n = sc.n(), p = sc.n(), c = sc.n(); std::cout << n * getH (n) * (p * calc(1 - Int(p), c-1) + c * (1 - Int(p)).pow (c - 1) ) << std::endl; }
