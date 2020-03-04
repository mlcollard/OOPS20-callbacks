/*
    callback_x.cpp

    Experiments with different implementations of callbacks
*/

#include <iostream>
#include <iomanip>
#include <array>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <functional>

typedef std::array<int, 100000> Container_t;

// count of elements that don't get moved
int count(const Container_t::const_iterator begin,
          const Container_t::const_iterator end) {

    int count = 0;
    for (auto p = begin; p != end; ++p) {
        for (auto p2 = p; p2 != end; ++p2) {
            if (*p < *p2)
                ++count;
        }
    }

    return count;
}

// count of elements that don't get moved
int count(const Container_t::const_iterator begin,
          const Container_t::const_iterator end,
          bool (*compar)(int n1, int n2)) {

    int count = 0;
    for (auto p = begin; p != end; ++p) {
        for (auto p2 = p; p2 != end; ++p2) {
            if (compar(*p, *p2))
                ++count;
        }
    }

    return count;
}

// count of elements that don't get moved
template <typename Compare_t>
int count_template(const Container_t::const_iterator begin,
                   const Container_t::const_iterator end,
                   Compare_t compar) {

    int count = 0;
    for (auto p = begin; p != end; ++p) {
        for (auto p2 = p; p2 != end; ++p2) {
            if (compar(*p, *p2))
                ++count;
        }
    }

    return count;
}

// count of elements that don't get moved
int count_stdfunction(const Container_t::const_iterator begin,
          const Container_t::const_iterator end,
          std::function<bool(int n1, int n2)> compar) {

    int count = 0;
    for (auto p = begin; p != end; ++p) {
        for (auto p2 = p; p2 != end; ++p2) {
            if (compar(*p, *p2))
                ++count;
        }
    }

    return count;
}

Container_t ar;

// less-than compare
bool compare(int n1, int n2) {
    return n1 < n2;
}

int main() {

    // fill the array
    std::iota(ar.begin(), ar.end(), 1);

    {
        auto start = std::chrono::steady_clock::now();

        // @NOTE count using operator<
        auto counter = count(ar.begin(), ar.end());

        auto elapsed = std::chrono::steady_clock::now() - start;
        std::cout << counter << '\n';
        std::cout << std::setw(12) << elapsed.count() << ": operator<" << '\n';
    }

    {
        auto start = std::chrono::steady_clock::now();

        // @NOTE count using function pointer
        auto counter = count(ar.begin(), ar.end(), compare);

        auto elapsed = std::chrono::steady_clock::now() - start;
        std::cout << counter << '\n';
        std::cout << std::setw(12) << elapsed.count() << ": function pointer" << '\n';
    }

    {
        auto start = std::chrono::steady_clock::now();

        // @NOTE count using lambda
        auto counter = count(ar.begin(), ar.end(), 
            [](int n1, int n2) {
                return n1 < n2;
            }
        );

        auto elapsed = std::chrono::steady_clock::now() - start;
        std::cout << counter << '\n';
        std::cout << std::setw(12) << elapsed.count() << ": lambda function pointer" << '\n';
    }

    {
        auto start = std::chrono::steady_clock::now();

        // @NOTE count using lambda to template
        auto counter = count_template(ar.begin(), ar.end(), 
            [](int n1, int n2) {
                return n1 < n2;
            }
        );

        auto elapsed = std::chrono::steady_clock::now() - start;
        std::cout << counter << '\n';
        std::cout << std::setw(12) << elapsed.count() << ": lambda function template" << '\n';
    }

    {
        auto start = std::chrono::steady_clock::now();

        // @NOTE count using lambda to std::function
        auto counter = count_stdfunction(ar.begin(), ar.end(), 
            [](int n1, int n2) {
                return n1 < n2;
            }
        );

        auto elapsed = std::chrono::steady_clock::now() - start;
        std::cout << counter << '\n';
        std::cout << std::setw(12) << elapsed.count() << ": lambda std::function" << '\n';
    }

    return 0;
}
