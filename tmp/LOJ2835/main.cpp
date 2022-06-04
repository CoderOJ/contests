#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <mutex>
#include <queue>
#include <random>
#include <thread>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

std::vector<std::vector<int>> e;

int         n, k, w;
const char *fn_ans;

int rand_range(int l, int r)
{
  thread_local std::random_device                 rd;
  thread_local std::mt19937                       rng(rd());
  thread_local std::uniform_int_distribution<int> uid;
  return uid(rng, decltype(uid)::param_type{l, r - 1});
}

int calc_dis(int u, const std::vector<int> &vs, int s)
{
  thread_local std::vector<std::vector<int>> e;
  if (e.empty())
    e = ::e;

  for (int v : vs)
  {
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<int> dis(n);
  std::queue<int>  que;

  auto calc = [&](int s) {
    int res = 0;
    std::fill(dis.begin(), dis.end(), std::numeric_limits<int>::max());
    dis[s] = 0;
    que.emplace(s);
    while (!que.empty())
    {
      int u = que.front();
      que.pop();
      res += dis[u];
      for (int v : e[u])
        if (check_min(dis[v], dis[u] + 1))
          que.push(v);
    }
    return res;
  };

  int res = 0;
  if (s != -1)
    res = calc(s);
  else
  {
    for (int s = 0; s < n; s++)
      res += calc(s);
    res = res / 2;
  }

  for (int v : vs)
  {
    e[u].pop_back();
    e[v].pop_back();
  }

  return res;
}

struct answer_t
{
  int              val0, val;
  int              u;
  std::mutex       mu;
  std::vector<int> vs;

  void init(int k)
  {
    FILE *f_ans = fopen(fn_ans, "r");

    bool success = [&] {
      if (f_ans == nullptr)
        return false;

      for (int i = 0; i < k; i++)
      {
        int v;
        int rc = fscanf(f_ans, "%d%d", &u, &v);
        if (rc != 2)
          return false;
        u -= 1;
        vs.push_back(v - 1);
      }

      return true;
    }();
    if (!success)
    {
      u = 0;
      vs.clear();
      for (int i = 0; i < k; i++)
        vs.push_back(i);
    }
    val0 = calc_dis(u, vs, u);
    val  = calc_dis(u, vs, -1);

    if (f_ans)
      fclose(f_ans);
  }

  void copy(int &u, std::vector<int> &vs)
  {
    std::lock_guard<std::mutex> lg{mu};
    u  = this->u;
    vs = this->vs;
  }

  void check(int u, std::vector<int> vs)
  {
    int cur_val0 = calc_dis(u, vs, u);
    if (cur_val0 < val0)
    {
      std::lock_guard<std::mutex> lg{mu};
      int                         cur_val = calc_dis(u, vs, -1);
      if (cur_val < val)
      {
        printf("update: val = %d\n", cur_val);
        this->val0 = cur_val0;
        this->val  = cur_val;
        this->u    = u;
        this->vs   = std::move(vs);

        FILE *f_ans = fopen(fn_ans, "w");
        for (int v : this->vs)
          fprintf(f_ans, "%d %d\n", u + 1, v + 1);
        fflush(f_ans);
        fclose(f_ans);
      }
    }
  }
};

answer_t answer;

void attempt()
{
  int              u;
  std::vector<int> vs;
  answer.copy(u, vs);

  if (rand_range(0, 10) == 0)
    u = rand_range(0, n);
  else
  {
    vs[rand_range(0, k)] = rand_range(0, n);
    vs[rand_range(0, k)] = rand_range(0, n);
  }

  answer.check(u, std::move(vs));
}

int main(int argc, char **argv)
{
  if (argc < 2)
    fn_ans = "ans";
  else
    fn_ans = argv[1];

  n = sc.next_int();
  k = sc.next_int();
  w = sc.next_int();
  printf("goal: %d\n", w);

  e.resize(n);
  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  answer.init(k);

  std::vector<std::thread> jobs;
  for (int i = 0; i < 8; i++)
  {
    jobs.emplace_back([] {
      while (answer.val > w)
        attempt();
    });
  }
  for (auto &t : jobs)
    t.join();

  return 0;
}
