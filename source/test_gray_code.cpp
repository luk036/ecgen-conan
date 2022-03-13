#include <doctest/doctest.h>

#include <algorithm>  // for fill_n
#include <ecgen/combin.hpp>
#include <ecgen/gray_code.hpp>
#include <string>
#include <vector>

TEST_CASE("Generate Gray code by BRGC_gen (odd)") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::BRGC_gen(5)) {
        ++cnt;
    }
    CHECK(cnt == 32);
}

TEST_CASE("Generate Gray code by BRGC_gen (even)") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::BRGC_gen(6)) {
        ++cnt;
    }
    CHECK(cnt == 64);
}

TEST_CASE("Generate all combinations by EMK_gen") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::EMK_gen(5, 3)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Combination<5, 3>());
}

TEST_CASE("Generate Gray code (odd)") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto& l : ecgen::BRGC<std::vector<bool>>(5)) {
        ++cnt;
    }
    CHECK(cnt == 32);
}

TEST_CASE("Generate Gray code (even)") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto& l : ecgen::BRGC<std::vector<size_t>>(6)) {
        ++cnt;
    }
    CHECK(cnt == 64);
}

TEST_CASE("Generate all combinations (odd)") {
    size_t cnt = 0;
    auto S = std::string("11100");
    for ([[maybe_unused]] auto& s : ecgen::EMK(5, 3, S)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Combination<5, 3>());
}

TEST_CASE("Generate all combinations (even)") {
    constexpr size_t N = 6;
    constexpr size_t K = 3;
    size_t cnt = 0;
    auto lst = std::vector<size_t>(N, 0);
    std::fill_n(lst.begin(), K, 1);
    for ([[maybe_unused]] auto& l : ecgen::EMK(N, K, lst)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Combination<N, K>());
}
