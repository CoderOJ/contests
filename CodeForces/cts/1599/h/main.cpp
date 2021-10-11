#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

// constexpr int N = 10;
constexpr int N = 1'000'000'000;

int query(int x, int y)
{
  std::cout << "? " << x << " " << y << std::endl;
  int ans;
  std::cin >> ans;
  return ans;
}

int main()
{
  int lb = query(1, 1);
  int rb = query(N, 1);
  int rt = query(N, N);

  int l = 1, r = std::min(N, 1 + lb);
  while (l < r)
  {
    int mid = (l + r + 1) / 2;
    see(l, r, mid);
    if (query(mid, 1) + (mid - 1) == lb) l = mid;
    else r = mid - 1;
  }

  int ax = l;
  int ay = 1 + lb - (ax - 1);
  int bx = N - (rb - (ay - 1));
  int by = N - (rt - (N - bx));

  std::cout << "! " <<  ax << " " << ay << " " << bx << " " << by << std::endl;

  return 0;
}

