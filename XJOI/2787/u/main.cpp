#include "./grader.cpp"

#undef fr
#undef fd
#undef i64

constexpr int L = 100000000;
std::mt19937 rd(20050610);
std::uniform_int_distribution<> rd_range(-L,L);

int free_x;

std::vector<int> ans_x, ans_y;
void dac(int l, int r) {
  if (l > r) { return; }

  int mid = l + (r - l) / 2;
  int dis = query(mid, mid);

  if (dis == 0) {
    if (query(mid, free_x) == 0) ans_y.push_back(mid);
    if (query(free_x, mid) == 0) ans_x.push_back(mid);
    dac(l, mid-1); dac(mid+1, r); return; }

  int find_l = mid-1;
  while (find_l >= -L) {
    int dis = query(find_l, find_l);
    if (dis == 0) break;
    find_l -= dis; }
  int find_r = mid+1;
  while (find_r <= L) {
    int dis = query(find_r, find_r);
    if (dis == 0) break;
    find_r += dis; }

  dac(l, find_l);
  dac(find_r, r);
}

std::pair<std::vector<int>,std::vector<int>>
solve() {
  while (true) {
    free_x = rd_range(rd);
    if (query(free_x, free_x) != 0) break; }
  dac(-L, L);
  return std::make_pair(std::move(ans_y), std::move(ans_x));
}
