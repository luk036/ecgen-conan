#include <doctest/doctest.h>

#include <ecgen/set_partition.hpp>

TEST_CASE("set partition") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(5, 3)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Stirling2nd<5, 3>());
}
