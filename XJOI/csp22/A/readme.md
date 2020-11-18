+ choose exactly $k$ numbers out of $n$ numbers.

consider each position

calculate number of ways to make it 1

then it came to:

to sort of balls, choose odd number of ball-A(bit is 1).

$$
\sum_{k} { \binom{x}{2k} \times \binom{y}{n-2k} }
$$

Oops, it is allowed to calculate this $O(n)$

Then the total complexity is $O(n \log a)$

Good.
