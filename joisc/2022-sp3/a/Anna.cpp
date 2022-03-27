#include "Anna.h"
#include <utility>
#include <vector>

namespace {

const int N = 60;

}

int Declare() {
  return N * 3;
}

std::pair<std::vector<int>, std::vector<int> > Anna(long long A) {
  std::vector<int> x; for (int i = 0; i < N * 3; i++) x.push_back(i % 2);
  std::vector<int> y; for (int i = 0; i < N; i++) { int t = (A >> i) & 1; y.push_back(t); y.push_back(t); y.push_back(t); }
  return make_pair(x, y);
}
