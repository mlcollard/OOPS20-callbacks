/*
    stdsort_count.cpp

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
    int counter = 0;
    std::sort(v.begin(), v.end(),
        [&counter](int n1, int n2)-> bool {
            ++counter;

            return n1 < n2;
        }
    );

    // record the elapsed time
    auto elapsed = std::chrono::steady_clock::now() - start;

    std::cout << "Counter: " << counter << '\n';

    std::cout << elapsed.count() << '\n';

    // verify sorted
    assert(std::is_sorted(v.begin(), v.end()));

    return 0;
}
