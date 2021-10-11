#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <ctime>
#include <random>
#include <algorithm>
#include <set>
#include <unordered_map>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{ 
  std::mt19937 rd(20050610);

  int n = sc.next_int();
  std::set<int> a;
  for (int i = 0; i < n; i++)
    a.insert(sc.next_int());

  std::set<int> cur_values;
  int cur_cnt = 0;

  if ((int)a.size() == n)
  {
    std::vector<int> rem[2];
    for (int x: a) rem[x % 2].push_back(x);
    if (rem[0].size() >= 3)
    {
      puts("YES"); 
      int sum = (rem[0][0] + rem[0][1] + rem[0][2]) / 2;
      printf("%d ", sum - rem[0][0]); cur_values.insert(sum - rem[0][0]); a.erase(rem[0][0]);
      printf("%d ", sum - rem[0][1]); cur_values.insert(sum - rem[0][1]); a.erase(rem[0][1]);
      printf("%d ", sum - rem[0][2]); cur_values.insert(sum - rem[0][2]); a.erase(rem[0][2]);
      cur_cnt = 3;
    }
    else if (rem[0].size() >= 1 && rem[1].size() >= 2)
    {

      puts("YES"); 
      int sum = (rem[0][0] + rem[1][0] + rem[1][1]) / 2;
      printf("%d ", sum - rem[0][0]); cur_values.insert(sum - rem[0][0]); a.erase(rem[0][0]);
      printf("%d ", sum - rem[1][0]); cur_values.insert(sum - rem[1][0]); a.erase(rem[1][0]);
      printf("%d ", sum - rem[1][1]); cur_values.insert(sum - rem[1][1]); a.erase(rem[1][1]);
      cur_cnt = 3;
    }
    else if (rem[1].size() >= 4)
    {
      std::vector<int> b = rem[1];
      std::vector<int> pa, pb;
      bool find_ans = false;
      while (static_cast<double>(clock()) / CLOCKS_PER_SEC <= 0.5)
      {
        std::shuffle(b.begin(), b.end(), rd);
        for (int l = 2; l * 2 <= (int)b.size(); l++)
        {
          std::unordered_map<int, int> psum;
          psum.reserve(b.size() * 4);
          int cur = std::accumulate(b.begin(), b.begin() + (l - 1), 0);
          for (int i = l; i <= (int)b.size(); i++)
          {
            cur += b[i - 1];
            if (psum.count(cur))
            {
              int pre = psum[cur];
              pa = std::vector<int>(b.begin() + pre, b.begin() + pre + l);
              pb = std::vector<int>(b.begin() + (i - l), b.begin() + i);
              find_ans = true;
              goto done;
            }
            psum[cur] = i - l;
            cur -= b[i - l];
          }
        }
      }
done:
      if (find_ans)
      {
        puts("YES");
        std::vector<int> p;
        for (size_t i = 0; i < pa.size(); i++)
        {
          p.push_back(pa[i]);
          p.push_back(pb[i]);
          a.erase(pa[i]);
          a.erase(pb[i]);
        }
        cur_cnt = (int)p.size();
        int cur = 0;
        printf("0 ");
        cur_values.insert(0);
        p.pop_back();
        for (int x: p)
          printf("%d ", cur = x - cur);
      }
      else
      {
        puts("NO");
        return 0;
      }
    }
    else
    {
      puts("NO");
      return 0;
    }
  }
  else
  {
    puts("YES");
    printf("0 ");
    cur_values.insert(0);
    cur_cnt = 1;
  }

  for (int x: a)
  {
    int by_pass = *cur_values.begin();
    printf("%d ", x - by_pass);
    cur_cnt++;
  }

  while (cur_cnt < n) 
  {
    printf("0 ");
    cur_cnt++;
  }

  return 0;
}

