// qsort-median3.cpp

#include "stdafx.h"

using namespace std;

template <typename T> size_t MedianOfThree(T &a, T &b, T &c,
        size_t ai, size_t bi, size_t ci)
{
    // Implement your code here
    return ci;
}

template <typename T> size_t QuicksortPartition(vector<T> &A, size_t lo, size_t hi)
{
    size_t ci = (int)(0.5*(lo + hi) + 0.5);
    size_t pivotIndex = MedianOfThree(A[lo], A[ci], A[hi], lo, ci, hi);
    T pivot = A[pivotIndex];

    size_t i = lo;
    size_t j = hi;
    while (true)
    {
        while (A[i] <= pivot && i < pivotIndex) i++;
        while (A[j] >= pivot && j > pivotIndex) j--;
        if (i == pivotIndex && j == pivotIndex)
            return pivotIndex;

        T tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;

        if (i == pivotIndex)
            pivotIndex = j;
        else if (j == pivotIndex)
            pivotIndex = i;
    }
}

template <typename T> void Quicksort(vector<T> &A, size_t lo, size_t hi)
{
    if (lo < hi)
    {
        size_t p = QuicksortPartition<T>(A, lo, hi);
        if (p > 0) //p is unsigned, so prevent negative
            Quicksort<T>(A, lo, p - 1);
        Quicksort<T>(A, p + 1, hi);
    }
}

template <typename T> void Quicksort(vector<T> &A)
{
    if (A.size() <= 1)
        return; //Nothing to do
    Quicksort(A, 0, A.size() - 1);
}


int main()
{
    seed_seq seed{ 2016 };
    default_random_engine generator{ seed };
    uniform_int_distribution<> distribution(1, 10);

    vector<int> nums(100000);
    for (auto& n : nums)
        n = distribution(generator);

    clock_t startTime{ clock() };

    Quicksort(nums);

    clock_t stopTime{ clock() };

    double totalTime{ ((double)(stopTime - startTime)
                       / CLOCKS_PER_SEC) * 1000 };

    cout.imbue(std::locale(""));
    cout << "Total run time (ms): "
         << totalTime << endl;

    return 0;
}

