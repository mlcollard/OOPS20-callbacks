/*
    stdsort_x.cpp

    Experimenting with std::sort()
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
    auto start = std::chrono::steady_clock::now();

    // sort the vector
    std::sort(v.begin(), v.end(),
        [](int n1, int n2)-> bool {
            return n1 < n2;
        }
     );

    // record the elapsed time
    auto elapsed = std::chrono::steady_clock::now() - start;

    std::cout << elapsed.count() << '\n';

    // verify sorted
    assert(std::is_sorted(v.begin(), v.end()));

    return 0;
}
