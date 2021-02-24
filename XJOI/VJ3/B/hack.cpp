#include <cstdio>
#include <algorithm>
using std :: sort;
namespace IO {
#define getcha() (SS == TT && (TT = (SS = BB) + fread(BB, 1, 1 << 23, stdin), SS == TT) ? EOF : *SS++)
char BB[1 << 23], *SS = BB, *TT = BB;
template <typename T>
inline void read(T &x) {
  x = 0; int fu = 1;
  char c = getcha();
  while(c > 57 || c < 48) {
    if(c == 45) fu = -1;
    c = getcha(); }
  while(c <= 57 && c >= 48) {
    x = x * 10 + c - 48;
    c = getcha(); }
  x *= fu; }
template <typename T, typename ...Args>
inline void read(T &x, Args &...args) {
  read(x); read(args...); }
char out[1 << 22], *Out = out;
#define flush() fwrite(out, 1, Out - out, stdout)
inline void putcha(char x) {
  *Out++ = x;
  if(Out - out >= (1 << 22)) flush(), Out = out; }
template <typename T>
inline void fprint(T x) {
  if(x < 0) putcha(45), x = -x;
  if(x > 9) fprint(x / 10);
  putcha(x % 10 + 48); }
template <typename T>
inline void print(T x) {
  fprint(x);
  putcha(10); }
inline void print(const char *ch) {
  while(*ch != '\0') putcha(*(ch ++)); }
inline void put(const char *ch) {
  while(*ch != '\0') putcha(*(ch ++));
  putcha(10); }
template <typename T, typename ...Args>
inline void print(T x, Args ...args) {
  fprint(x);
  putcha(32);
  print(args...); }
template <typename T>
inline void sprint(T x) {
  fprint(x);
  putcha(32); }
template <typename T, typename ...Args>
inline void sprint(T x, Args ...args) {
  fprint(x);
  putcha(32);
  sprint(args...); }
class AutoFlush {
public:
  ~AutoFlush() {
    flush(); } } __AutoFlush; } // namespace IO
using namespace IO;
#include <ctime>
namespace MyMinMax {
template <typename T>
inline T mn(T x, T y) {
  return x < y ? x : y; }
template <typename T>
inline T mx(T x, T y) {
  return x > y ? x : y; }
template <typename T>
inline void chmin(T &x, T y) {
  (x > y) && (x = y); }
template <typename T>
inline void chmax(T &x, T y) {
  (x < y) && (x = y); } }
using namespace MyMinMax;
#define MAXN 300005
typedef long long LL;
int n, m1, m2;
int cnt[1000005];
int a[MAXN], ret;
int tot, ans[MAXN], b[MAXN], c[MAXN];


inline int calc(int p, int t) {
  t -= c[p];
  if(t < 0) return -0x3f3f3f3f;
  int l = 0, r = m1, res = 0;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(b[mid] <= t) res = mid, l = mid + 1;
    else r = mid - 1; }
  return res + p - 1; }

int main() {
  read(n);
  for (int i = 1; i <= n;
    ++ i) read(a[i]), ret += !(cnt[a[i]] ++), chmax(tot, a[i]);
  sprint(ret);
  for (int i = 1; i <= tot; ++ i) {
    if(!cnt[i]) continue;
    bool ck = 0;
    for (int j = (i << 1); j <= tot; j += i) {
      if(cnt[j]) {
        ck = 1;
        break; } }
    if(ck) b[++ m1] = cnt[i];
    else c[++ m2] = cnt[i]; }
  sort(b + 1, b + m1 + 1);
  sort(c + 1, c + m2 + 1);
  for (int i = 1; i <= m1; ++ i) b[i] += b[i - 1];
  for (int i = 1; i <= m2; ++ i) c[i] += c[i - 1];
  c[1] = 0;
  int p = 1;
  for (int i = 1; i <= n; ++ i) {
    p = mx(p - 150, 1);
    while(p < m2 && calc(p + 1, i) >= calc(p, i)) ++ p;
    int TIM = m2;
    while(TIM) {
      int t = mx(1, p - TIM);
      if(calc(t, i) > calc(p, i)) p = t;
      t = mn(m2, p + TIM);
      if(calc(t, i) > calc(p, i)) p = t;
      TIM *= 3;
      TIM >>= 2;
    }
    sprint(ret - calc(p, i)); }
  putcha(10); }
