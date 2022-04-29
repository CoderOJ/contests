#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 30;

void iaddml(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}

void isubml(int &x, int y)
{
	x -= y;
	if (x < 0) x += MOD;
}

int inv(int x)
{
	if (x == 1)
		return 1;
	else
		return static_cast<int64_t>(inv(MOD % x)) * (MOD - MOD / x) % MOD;
}

int n, m, ws;
bool has_tone[N][N];
int tone_list[N];
char s[N + 1];

void init()
{
	scanf("%d%d", &n, &m);
	ws = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s);
		std::fill(has_tone[i], has_tone[i] + 26, false);
		for (char *c = s; *c; c++)
		{
			has_tone[i][*c - 'a'] = true;
			ws += 1;
		}
	}
	scanf("%s", s);
	for (int i = 0; i < m; i++)
		tone_list[i] = s[i] - 'a';
}


void rmain()
{
	init();

	bool has_solution = [&]{
		for (int i = 0; i < n - m + 1; i++)
		{
			bool valid = [&]{
				for (int j = 0; j < m; j++)
					if (!has_tone[i + j][tone_list[j]])
						return false;
				return true;
			}();
			if (valid)
				return true;
		}
		return false;
	}();
	if (!has_solution)
	{
		puts("-1");
		return;
	}

	const int pre_len = n - m + 1;
	const int max_ws = n * 15;

	static int _dp[2][1 << 15][N * 15];
	static int (*dp[N + 1])[N * 15];
	for (int i = 0; i <= n; i++)
		dp[i] = _dp[i % 2];
	memset(dp[0], 0, sizeof(_dp[0][0]));
	dp[0][0][0] = MOD - 1;

	for (int i = 0; i < pre_len; i++)
	{
		// printf("extending %d:\n", i);
		int cur_len = std::min(i + 1, m);
		memset(dp[i + 1], 0, sizeof(_dp[0][0]) * (1 << cur_len));
		for (int cm = 0; cm < (1 << cur_len); cm++)
		{
			int cnt = [&]{
				static bool need_tone[26];
				std::fill(need_tone, need_tone + 26, false);
				for (int j = 0; j < cur_len; j++)
					if (cm & (1 << j))
						need_tone[tone_list[j]] = true;
				int res = 0;
				for (int c = 0; c < 26; c++)
					if (need_tone[c])
					{
						if (!has_tone[i][c])
							return -1;
						else
							res += 1;
					}
				return res;
			}();

			if (cnt != -1)
			{
				const int pm = cm >> 1;
				const int nm = cm & ((1 << (m - 1)) - 1);
				// printf("mask: %d -> %d: delta_cnt = %d\n", pm, nm, cnt);
				if (cm & 1)
				{
					for (int t = 0; t < max_ws; t++)
						if (dp[i][pm][t] > 0)
							isubml(dp[i + 1][nm][t + cnt], dp[i][pm][t]);
				}
				else
				{
					for (int t = 0; t < max_ws; t++)
						if (dp[i][pm][t] > 0)
							iaddml(dp[i + 1][nm][t + cnt], dp[i][pm][t]);
				}
			}
		}
	}

	static int ans_cnt[N * 15];
	memset(ans_cnt, 0, sizeof(ans_cnt));
	for (int pm = 0; pm < (1 << std::min(m - 1, pre_len)); pm++)
		for (int pt = 0; pt < max_ws; pt++)
			if (dp[pre_len][pm][pt] > 0)
			{
				int suf_cnt = [&]{
					int res = 0;
					for (int si = pre_len, sm = pm << 1; si < n; si++, sm <<= 1)
					{
						static bool need_tone[26];
						std::fill(need_tone, need_tone + 26, false);
						for (int i = 0; i < m; i++)
							if (sm & (1 << i))
								need_tone[tone_list[i]] = true;
						for (int c = 0; c < 26; c++)
							if (need_tone[c])
							{
								if (!has_tone[si][c])
									return -1;
								else
									res += 1;
							}
					}
					return res;
				}();

				if (suf_cnt != -1)
					iaddml(ans_cnt[pt + suf_cnt], dp[pre_len][pm][pt]);
			}

	int ans = 0;
	int cur = 0;
	for (int i = 1; i < max_ws; i++)
	{
		// printf("ans_cnt[%d] = %d\n", i, ans_cnt[i]);
		cur = (cur + (int64_t)(ws) * inv(i)) % MOD;
		ans = (ans + (int64_t)(cur) * ans_cnt[i]) % MOD;
	}

	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		rmain();
	return 0;
}
