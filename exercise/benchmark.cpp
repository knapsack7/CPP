#include <benchmark/benchmark.h>
#include <iostream>

// Constexpr factorial
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

// Regular recursive factorial
int r_factorial(int n) {
    return (n <= 1) ? 1 : (n * r_factorial(n - 1));
}

// Iterative factorial for comparison
int i_factorial(int n) {
    int result = 1;
    for(int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Benchmark with larger numbers
static void BM_CFactorial(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(factorial(20));  // Larger number
    }
}
BENCHMARK(BM_CFactorial);

static void BM_RFactorial(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(r_factorial(30));  // Larger number
    }
}
BENCHMARK(BM_RFactorial);

static void BM_IFactorial(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(i_factorial(30));  // Larger number
    }
}
BENCHMARK(BM_IFactorial);

BENCHMARK_MAIN();