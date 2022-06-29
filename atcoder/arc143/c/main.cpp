#include <iostream>
#include <vector>

int main() {
  int n, x, y;
  std::cin >> n >> x >> y;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  auto can_win = [&](int v) { return v % (x + y) < y; };

  bool ans = [&] {
    bool operated = false;
    for (int i = 0; i < n; i++) {
      bool wa = can_win(a[i]);
      bool wb = a[i] >= x && can_win(a[i] - x);
      if (!wa && !wb)
        return false;
      if (wb)
        operated = true;
    }
    return operated;
  }();

  puts(ans ? "First" : "Second");
}
