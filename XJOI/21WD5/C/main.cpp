#include <vector>
#include <algorithm>
#include <set>
#include <functional>

class ModuloCounters {
private:

public:
  long long minFoxes(long long M, std::vector<long long> a) {
    int n = a.size();
    if (n == 1) { return a[0]; }

    std::vector<int> id(n); 
    for (int i=0;i<n;++i) id[i] = i;
    std::sort(id.begin(), id.end(), [&](int x, int y) {
      return a[x] < a[y]; });

    std::multiset<long long> adj_sum;
    for (int i=1;i<n;++i) { adj_sum.insert(a[i-1] + a[i]); }

    std::function<bool(long long)> valid = [&adj_sum](long long max) {
      return *adj_sum.begin() >= max; };

    long long a_max = *std::max_element(a.begin(), a.end());
    if (valid(a_max)) { return a_max; }

    for (const int i: id) {
      if (i) { adj_sum.erase(adj_sum.find(a[i-1] + a[i])); }
      if (i<n-1) { adj_sum.erase(adj_sum.find(a[i] + a[i+1])); }
      a[i] += M;
      if (i) { adj_sum.insert(a[i-1] + a[i]); }
      if (i<n-1) { adj_sum.insert(a[i] + a[i+1]); }
      if (valid(a[i])) { return a[i]; } }

    return -1;
  }
};
