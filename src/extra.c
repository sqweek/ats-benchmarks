/* naïve recursion */
int
collatz_cr(int n)
{
	if (n % 2 == 0)
		return 1 + collatz_cr(n/2);
	else if (n == 1)
		return 1;
	else
		return 1 + collatz_cr(3*n + 1);
}

/* tail recursion */
static int
collatz_ctr_loop(int n, int count)
{
	if (n % 2 == 0)
		return collatz_ctr_loop(n/2, count + 1);
	else if (n == 1)
		return count;
	else
		return collatz_ctr_loop(3*n + 1, count + 1);
}

int
collatz_ctr(int n)
{
	return collatz_ctr_loop(n, 1);
}

/* a copy of collatz_c, for control */
int collatz_c2(int n) {
  int l = 1;
  while (n != 1) {
    if (n % 2 == 0)
      n = n / 2;
    else
      n = 3 * n + 1;
    l++;
  }
  return l;
}
