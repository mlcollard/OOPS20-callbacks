/*
    qsort_named.cpp

    Experimenting with qsort()

    @NOTE: For demonstration purposes only. Use std::sort with C++
    as it is much easier, much safer, and much more efficient
*/

#include <iostream>
#include <array>
#include <numeric>
#include <chrono>
#include <cassert>
#include <cstdlib>

std::array<int, 100000000> v;

int main() {

    // fill the vector with descending ordered list
    std::iota(v.begin(), v.end(), 1);
    std::reverse(v.begin(), v.end());

    // record the start time
    auto start = std::chrono::steady_clock::now();

    // sort v in ascending order
    auto compare = [](const void* v1, const void* v2) {

        auto n1 = static_cast<const int*>(v1);
        auto n2 = static_cast<const int*>(v2);

        if (*n1 < *n2)
            return -1;
        else if (*n1 > *n2)
            return 1;
        else
            return 0;
    };

    qsort(v.data(), v.size(), sizeof(v[0]), compare);

    // record the elapsed time
    auto elapsed = std::chrono::steady_clock::now() - start;

    std::cout << elapsed.count() << '\n';

    // verify sorted
    assert(std::is_sorted(v.begin(), v.end()));

    return 0;
}
