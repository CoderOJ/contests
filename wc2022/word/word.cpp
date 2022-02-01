#include "word.h"
#include <algorithm>
#include <bitset>
#include <random>

#define N 8869

std::mt19937 rd(114514);

char dict[N][6];
int  n;

std::bitset<128> determined[5];
int              existance[128];

char *last_guess;

void init(int num_scramble, const char *scramble)
{
  n = num_scramble;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 5; j++)
      dict[i][j] = scramble[i * 5 + j];
}

const char *guess(
    int, int remaining_guesses, char initial_letter, bool *gold, bool *silver)
{
  if (remaining_guesses == 5)
  {
    last_guess = nullptr;
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 128; j++)
        determined[i][j] = 1;
    for (int i = 0; i < 128; i++)
      existance[i] = -1;
    determined[0].reset();
    determined[0].set(initial_letter, true);
  }
  else
  {
    for (int i = 0; i < 5; i++)
    {
      if (gold[i])
      {
        determined[i].reset();
        determined[i].set(last_guess[i], true);
        existance[(int)last_guess[i]] = 1;
      }
      else
      {
        determined[i].set(last_guess[i], false);
      }
    }
    for (int i = 0; i < 5; i++)
    {
      if (silver[i])
      {
        existance[(int)last_guess[i]] = 1;
      }
      else if (existance[(int)last_guess[i]] == -1)
      {
        existance[(int)last_guess[i]] = 0;
      }
    }
  }

  std::vector<int> candidates;
  for (int i = 0; i < n; i++)
  {
    bool valid = true;
    for (int j = 0; j < 5; j++)
      if (!determined[j][dict[i][j]] || existance[(int)dict[i][j]] == 0)
      {
        valid = false;
        break;
      }
    for (int j = 0; j < 128; j++)
      if (existance[j] == 1)
      {
        bool existed = false;
        for (int k = 0; k < 5; k++)
          if (dict[i][k] == j)
            existed = true;
        if (existed == false)
          valid = false;
      }
    if (valid)
    {
      candidates.push_back(i);
    }
  }

  if (candidates.empty())
  {
    // fprintf(stderr, "not valid %d\n", remaining_guesses);
    return dict[0];
  }

  std::shuffle(candidates.begin(), candidates.end(), rd);
  last_guess = dict[candidates[0]];
  return last_guess;
}
