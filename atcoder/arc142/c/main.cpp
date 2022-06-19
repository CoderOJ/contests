#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  auto query = [](int u, int v) {
    cout << "? " << u << " " << v << endl;
    int d;
    cin >> d;
    return d;
  };

  vector<pair<int, int>> mins{{n + 1, 0}};
  for (int i = 3; i <= n; i++) {
    int d = query(1, i) + query(2, i);
    if (d < mins.front().first)
      mins = {{d, i}};
    else if (d == mins.front().first)
      mins.emplace_back(d, i);
  }

  if (mins.front().first == 2)
    cout << "! 2" << endl;
  else if (mins.front().first == 3) {
    if ((int)(mins.size()) == 2 && query(mins[0].second, mins[1].second) == 1)
      cout << "! 3" << endl;
    else
      cout << "! 1" << endl;
  } else {
    cout << "! " << mins.front().first << endl;
  }

  return 0;
}
