#pragma once

/**
 Set Partition

 A set partition of the set [n] = {1,2,3,...,n} is a collection B0,
 B1, ... Bj of disjoint subsets of [n] whose union is [n]. Each Bj
 is called a block. Below we show the partitions of [4]. The periods
 separtate the individual sets so that, for example, 1.23.4 is the
 partition {{1},{2,3},{4}}.
   1 block:  1234
   2 blocks: 123.4   124.3   134.2   1.234   12.34   13.24   14.23
   3 blocks: 1.2.34  1.24.3  14.2.3  13.2.4  12.3.4
   4 blocks: 1.2.3.4

 Each partition above has its blocks listed in increasing order of
 smallest element; thus block 0 contains element 1, block1 contains
 the smallest element not in block 0, and so on. A Restricted Growth
 string (or RG string) is a sring a[1..n] where a[i] is the block in
 whcih element i occurs. Restricted Growth strings are often called
 restricted growth functions. Here are the RG strings corresponding
 to the partitions shown above.

   1 block:  0000
   2 blocks: 0001, 0010, 0100, 0111, 0011, 0101, 0110
   3 blocks: 0122, 0121, 0112, 0120, 0102,

 ...more

 Reference:
 Frank Ruskey. Simple combinatorial Gray codes constructed by
 reversing sublists. Lecture Notes in Computer Science, #762,
 201-208. Also downloadable from
 http://webhome.cs.uvic.ca/~ruskey/Publications/SimpleGray/SimpleGray.html

**/

#include <cppcoro/recursive_generator.hpp>
#include <type_traits>
#include <utility>

namespace ecgen {

    /**
     * @brief Stirling number of second kind.
     *
     * @tparam N
     * @tparam K
     * @return constexpr auto
     */
    template <size_t N, size_t K> constexpr auto Stirling2nd() {
        if constexpr (K >= N || K <= 1) {
            return std::integral_constant<size_t, 1>{};
        } else {
            return std::integral_constant<size_t, Stirling2nd<N - 1, K - 1>()
                                                      + K * Stirling2nd<N - 1, K>()>{};
        }
    }

    /**
     * @brief Set the partition gen object
     *
     * @param n
     * @param k
     * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
     */
    extern auto set_partition_gen(size_t n, size_t k)
        -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;

}  // namespace ecgen