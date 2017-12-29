#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

extern int collatz(int);
extern int collatz_c(int);

int done = 0;

void
alrm(int x)
{
	done = 1; // triggered by SIGALRM
}

// benched using a macro b/c I'm unsure if calling via a function pointer incurs overhead
#define do_bench(fn, arg) do { \
	long nanos, count = 0; \
	struct timespec start, end; \
\
	done = 0; \
	alarm(1); \
	clock_gettime(CLOCK_MONOTONIC_RAW, &start); \
	while(!done) { \
		fn(arg); \
		++count; \
	} \
	clock_gettime(CLOCK_MONOTONIC_RAW, &end); \
	nanos = 1000000000L * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec); \
	printf("%14s(%d): %7ld ops in %ldns = %5.1fns/op\n", #fn, arg, count, nanos, nanos/(double)count); \
} while (0)


int
main(int argc, char **argv)
{
	struct sigaction sa = {0};
	sa.sa_handler = alrm;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGALRM, &sa, NULL);

	int input = argc < 2 ? 2223 : atoi(argv[1]);

	do_bench(collatz, input);
	do_bench(collatz_c, input);

	/*
	printf("\n");
	// I was using these extra runs to check for cache effects; didn't find any

	do_bench(collatz, input);
	do_bench(collatz, input);
	do_bench(collatz, input);
	do_bench(collatz_c, input);
	do_bench(collatz_c, input);
	do_bench(collatz_c, input);
	*/

	return 0;
}
