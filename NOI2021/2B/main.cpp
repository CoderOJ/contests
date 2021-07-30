#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#define SCANNER_H_CUSTOM
#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
std::mt19937 rd(20050610);

struct Matrix {
	int a[2][2];
	Matrix() =default;
	Matrix(int a00, int a01, int a10, int a11) : a{{a00,a01},{a10,a11}} {}
	int* operator[] (int id) { return a[id]; }
	const int* operator[] (int id) const { return a[id]; }
	void log() { printf("{%d, %d, %d, %d}\n", a[0][0], a[0][1], a[1][0], a[1][1]); }
	Matrix operator* (const Matrix &b) const {
		return Matrix {
			(int)((1ll * a[0][0] * b[0][0] + 1ll * a[0][1] * b[1][0]) % MOD),
			(int)((1ll * a[0][0] * b[0][1] + 1ll * a[0][1] * b[1][1]) % MOD),
			(int)((1ll * a[1][0] * b[0][0] + 1ll * a[1][1] * b[1][0]) % MOD),
			(int)((1ll * a[1][0] * b[0][1] + 1ll * a[1][1] * b[1][1]) % MOD) }; } };

Matrix trans[2] = { {1,0,1,1}, {2,1,998244352,0} };

struct Node {
  Matrix sum[4];
  Node *l=nullptr, *r=nullptr;
  size_t weigh = rd(), size = 1;
  bool mflip=0, tflip=0, trev=0;
  Node(bool t) : sum{trans[t], trans[t^1], trans[t], trans[t^1]}, mflip(t) {}

  void push_up() {
    size = 1; sum[0] = sum[2] = trans[mflip]; sum[1] = sum[3] = trans[mflip ^ 1];
    if (l != nullptr) { size += l->size;
      sum[0] = l->sum[0] * sum[0]; sum[1] = l->sum[1] * sum[1];
      sum[2] = sum[2] * l->sum[2]; sum[3] = sum[3] * l->sum[3]; }
    if (r != nullptr) { size += r->size;
      sum[0] = sum[0] * r->sum[0]; sum[1] = sum[1] * r->sum[1];
      sum[2] = r->sum[2] * sum[2]; sum[3] = r->sum[3] * sum[3]; } }
  void push_flip() { tflip ^= 1; mflip ^= 1;
    std::swap(sum[0], sum[1]); std::swap(sum[2], sum[3]); }
  void push_rev() { trev ^= 1;
    std::swap(sum[0], sum[2]); std::swap(sum[1], sum[3]); 
    std::swap(l, r); }
  void push_down() {
    if (tflip) { tflip = 0;
      if (l) l->push_flip(); 
      if (r) r->push_flip(); }
    if (trev) { trev = 0;
      if (l) l->push_rev(); 
      if (r) r->push_rev(); } }

  ~Node() { delete l; delete r; }
} __attribute__ ((aligned(16)));

void split(Node *&a, Node *&b, Node *u, size_t thr) {
  if (u == nullptr) { a=nullptr; b=nullptr; return; } 
  u->push_down();
  size_t lsize = (u->l ? u->l->size : 0) + 1;
  if (lsize <= thr) split((a = u)->r, b, u->r, thr - lsize);
  else split(a, (b = u)->l, u->l, thr);
  u->push_up(); }

void join(Node *&u, Node *a, Node *b) {
  if (a == nullptr) { u = b; return; } 
  if (b == nullptr) { u = a; return; } 
  a->push_down(); b->push_down();
  if (a->weigh > b->weigh) join((u = a)->r,  a->r, b);
  else join((u = b)->l, a, b->l);
  u->push_up(); }

Node *root = nullptr;
void insert(bool type) {
  join(root, root, new Node(type)); }

int n, m;
char str[10];

Scanner sc(fopen("code.in", "r"));
void preInit() { freopen("code.out", "w", stdout); }
void init() 
{
  root = new Node(0);
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; i++) insert(sc.nextChar() == 'E');
} 

void solve() 
{
  auto output = []{ printf("%d %d\n", root->sum[0][0][0], root->sum[0][1][0]); };
  output();
  for (int i=0; i<m; i++) {
    sc.next(str);
    if (str[0] == 'A') {
      insert(sc.nextChar() == 'E'); }
    else {
      int l = sc.n(), r = sc.n() + 1;
      Node *a, *b, *c;
      split(a, b, root, (size_t)l);
      split(b, c, b, (size_t)(r - l));
      if (str[0] == 'R') b->push_rev();
      else b->push_flip();
      join(root, a, b);
      join(root, root, c); 
    }
    output(); }
  delete root;
}
