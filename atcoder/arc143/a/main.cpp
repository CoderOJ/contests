#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  std::vector<int64_t> a(3);
  std::cin >> a[0] >> a[1] >> a[2];
  std::sort(a.begin(), a.end());

  if (a[2] > a[0] + a[1])
    puts("-1");
  else {
    int64_t c = a[0] + a[1] - a[2];
    std::cout << c + (a[0] - c + a[1] - c) << std::endl;
  }

  return 0;
}
