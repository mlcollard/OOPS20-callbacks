/*
    qsort_x.cpp

    Experimenting with qsort()

    @NOTE: For demonstration purposes only. Use std::sort with C++
    as it is much easier, much safer, and much more efficient
*/

#include <iostream>
#include <array>
#include <numeric>
#include <chrono>
#include <cassert>

std::array<int, 100000000> v;

int main() {

    // fill the vector with descending ordered list
    std::iota(v.begin(), v.end(), 1);
    std::reverse(v.begin(), v.end());

    // record the start time
    auto start = std::chrono::high_resolution_clock::now();

    // sort v in ascending order

    // record the elapsed time
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    std::cout << elapsed.count() << '\n';

    // verify sorted
    assert(std::is_sorted(v.begin(), v.end()));

    return 0;
}
