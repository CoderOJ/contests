## dp

think of brute force

when we visit a stop, update the information of the stops that it can reach.

and then i find $\max_c \leq 10$

and $\gcd(1,2,\cdots,10)$ is only $2520$

**Time limit: 2s**

maybe $O(n \times 2520)$ -> 60pts

Consider of maintaining $O({\max_c} ^2)$ queues

each is index as $(m, r)$, which means $\text{id} \equiv r \pmod{m}$

hard to code...

~~and complexity is $O(n \times {\max_c}^2)$~~

~~about $10^8$~~

oh no,

each time we only modify 1, and query 10

so its $O(n \times {\max_c})$

$10^7$

std may be

## About details

```cpp
const int C = 11;

struct Point;

struct Line
{
  Point intersect(Line& B);
};

struct Lmin
{
  vector <Line> a;

  void insert();
  int get(int x);
};

Lmin go[C][C];
```

## After pass local judging

Actually it's far more than i think above.

It's a stack, not queue

And it's really differentiated from other similar problems.

i have those lines with `k` decreasing, and at this point there height
 increasing

when i insert one line, pop until cannot pop or two standards above are met

after i move the position right, pop some to meet the second standard

it's on query when it moves the position right, so after move, the top is the
line i need
