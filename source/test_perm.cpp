#include <doctest/doctest.h>

#include <ecgen/perm.hpp>
#include <string>
#include <vector>

TEST_CASE("Generate all permutations by SJT_gen (odd)") {
    size_t cnt = 0;  // start from 0
    for ([[maybe_unused]] auto i : ecgen::SJT_gen(5)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by SJT_gen (even)") {
    size_t cnt = 0;  // start from 0
    for ([[maybe_unused]] auto i : ecgen::SJT_gen(6)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<6>());
}

TEST_CASE("Generate all permutations by Ehr algorithm (odd)") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::Ehr_gen(5)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by Ehr algorithm (even)") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::Ehr_gen(6)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<6>());
}

TEST_CASE("Generate all permutations by SJT (odd)") {
    auto cnt = 0;  // start from 0
    auto L = std::vector{1, 3, 5, 7, 9};
    for ([[maybe_unused]] auto& l : ecgen::SJT(L)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by SJT (even)") {
    auto cnt = 0;  // start from 0
    auto S = std::string("ABCDEF");
    for ([[maybe_unused]] auto& s : ecgen::SJT(S)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<6>());
}

TEST_CASE("Generate all permutations by Ehr (odd)") {
    auto cnt = 0;  // start from 0
    auto L = std::vector{1, 3, 5, 7, 9};
    for ([[maybe_unused]] auto& l : ecgen::Ehr(L)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by Ehr (even)") {
    auto cnt = 0;  // start from 0
    auto S = std::string("ABCDEF");
    for ([[maybe_unused]] auto& s : ecgen::Ehr(S)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<6>());
}
