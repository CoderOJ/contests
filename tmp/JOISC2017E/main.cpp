#include "Broken_device_lib.h"
#include <algorithm>

constexpr int N = 150;

void Anna(int, long long x, int k, int p[])
{
  static bool good[N];
  std::fill(good, good + N, true);
  for (int i = 0; i < k; i++)
    good[p[i]] = false;

  int broken_block_cnt = 0;
  for (int i = 0; i < N; i += 3)
  {
    bool is_good_block = (good[i] + good[i + 1] + good[i + 2]) >= 2;
    if (!is_good_block)
      broken_block_cnt += 1;
  }

  if (broken_block_cnt <= 12)
  {
    for (int i = 0; i < N; i += 3)
    {
      bool is_good_block = (good[i] + good[i + 1] + good[i + 2]) >= 2;
      if (is_good_block)
      {
        int c = x % 3 + 1;
        x /= 3;

        int mask = !good[i] | (!good[i + 1] << 1) | (!good[i + 2] << 2);
        if (c & mask)
          c = 7 ^ c;

        for (int y = 0; y < 3; y++)
          Set(i + y, (c >> y) & 1);
      }
      else
      {
        for (int y = 0; y < 3; y++)
          Set(i + y, 0);
      }
    }
  }
  else
  {
    for (int i = 0; i < N; i += 3)
    {
      bool is_good_block = (good[i] + good[i + 1] + good[i + 2]) >= 3;
      if (is_good_block)
      {
        int c = x % 7 + 1;
        x /= 7;
        for (int y = 0; y < 3; y++)
          Set(i + y, (c >> y) & 1);
      }
      else
      {
        for (int y = 0; y < 3; y++)
          Set(i + y, 0);
      }
    }
  }
}

long long Bruno(int, int a[])
{
  int broken_block_cnt = 0;
  for (int i = 0; i < N; i += 3)
  {
    bool is_good_block = a[i] || a[i + 1] || a[i + 2];
    if (!is_good_block)
      broken_block_cnt += 1;
  }
  if (broken_block_cnt <= 12)
  {
    long long r = 0;
    for (int i = N - 3; i >= 0; i -= 3)
    {
      bool is_good_block = a[i] || a[i + 1] || a[i + 2];
      if (is_good_block)
      {
        int c = a[i] | (a[i + 1] << 1) | (a[i + 2] << 2);
        c     = std::min(c, 7 ^ c);
        r     = r * 3 + (c - 1);
      }
    }
    return r;
  }
  else
  {
    long long r = 0;
    for (int i = N - 3; i >= 0; i -= 3)
    {
      bool is_good_block = a[i] || a[i + 1] || a[i + 2];
      if (is_good_block)
      {
        int c = a[i] | (a[i + 1] << 1) | (a[i + 2] << 2);
        r     = r * 7 + (c - 1);
      }
    }
    return r;
  }
}
