---
title: 清华集训2016 如何优雅地求和
tags:
  - Tutorial
  - Math
  - Poly
---

# [清华集训2016] 如何优雅地求和

## Description

给定 $n,x$ 和 $m$ 次多项式 $f$ （给出 $0 \cdots m$ 的点值） ，求

$$
\sum_{k=0}^n f(k) \binom{n}{k} x^k (1-x)^{n-k}
$$

## Tutorial

设 $f$ 转化为下降幂多项式时的系数为 $b_0 \cdots b_m$

使用类似于联合省选组合数问题的技巧，我们有
$$
\begin{aligned}
\sum_{k=0}^n f(k)\binom{n}{k} x^k (1-x)^{n-k}
&= \sum_{k=0}^n \sum_{i=0}^{m} b_i k^{\underline i} \binom{n}{k} x^k (1-x) ^{n-k} \\
&= \sum_{k=0}^n \sum_{i=0}^{m} b_i n^{\underline i} \binom{n-i}{k-i} x^k (1-x) ^{n-k} \\
&= \sum_{i=0}^{m} b_i n^{\underline i} \sum_{k=i}^n \binom{n-i}{k-i} x^k (1-x) ^{n-k} \\
&= \sum_{i=0}^{m} b_i n^{\underline i} x^i \sum_{k=0}^{n-i} \binom{n-i}{k} x^{k} (1-x) ^{n-i-k} \\
&= \sum_{i=0}^{m} b_i x^i n^{\underline i} &(1)
\end{aligned}
$$
接下来考虑如何求 $b_i$，当然可以先插值再转为下降幂，但出题人给点值~~显然~~不是用来恶心人的，考虑直接通过点值求 $b_i$

因为
$$
x^n = \sum_k \begin{Bmatrix} n\\k \end{Bmatrix} x^{\underline k}
$$
设 $f$ 的普通幂系数为 $a_0 \cdots a_m$，我们有
$$
\begin{aligned}
b_i &= \sum_j \begin{Bmatrix} j\\i \end{Bmatrix} a_j &(2)
\end{aligned}
$$
然后考虑一个恒等式
$$
\sum_{m} \binom{k}{m} \begin{Bmatrix} n\\m \end{Bmatrix} m! = k^n
$$
这很容易用组合意义证明

二项式反演得到
$$
\begin{aligned}
m! \begin{Bmatrix} n\\m \end{Bmatrix} &= \sum_k \binom{m}{k} k^n(-1)^{m-k} \\
   \begin{Bmatrix} n\\m \end{Bmatrix} &= \frac1{m!}\sum_k \binom{m}{k} k^n(-1)^{m-k} \\ 
\end{aligned}
$$
~~我怎么把第二类斯特林数·行的式子推了一遍~~

带入 $(2)$，得到
$$
\begin{aligned}
b_i &= \sum_j \begin{Bmatrix} j\\i \end{Bmatrix} a_j \\
&= \frac1{i!} \sum_j \sum_k \binom{i}{k}k^j(-1)^{i-k} a_j \\
&= \frac1{i!} \sum_k \binom{i}{k}(-1)^{i-k} \sum_j a_j k^j \\
&= \frac1{i!} \sum_k \binom{i}{k}(-1)^{i-k} f(k) \\
&= \sum_k \frac{f(k)}{k!} \frac{(-1)^{i-k}}{(i-k)!} \\
\end{aligned}
$$
这十分的卷积，显然可以 $O(m \log m)$ 计算

然后把算出来的$b_i$ 带回 $(1)$ 就好了

## UPD0

突然发现我好傻逼，转下降幂完全不用那么烦
$$
\begin{aligned}
f(k) &= \sum_i b_ii! \times \frac{k^{\underline i}}{i!} \\
&= \sum_i b_i i! \binom{k}{i}
\end{aligned}
$$
直接二项式反演
$$
\begin{aligned}
b_k k! &= \sum_i (-1)^{k-i} \binom{k}{i} f(i) \\
b_k &= \sum_i \frac{(-1)^{k-i}}{(k-i)!} \frac{f(i)}{i!}
\end{aligned}
$$
我之前在干什么。。。