#pragma once

#include <cppcoro/generator.hpp>
#include <type_traits>  // for integral_constant

namespace ecgen {

    /**
     * @brief SJT
     *
     * @param n
     * @return cppcoro::generator<size_t>
     */
    extern auto SJT_gen(size_t n) -> cppcoro::generator<size_t>;

    /**
     * @brief Ehr
     *
     * @param n
     * @return cppcoro::generator<size_t>
     */
    extern auto Ehr_gen(size_t n) -> cppcoro::generator<size_t>;

    /**
     * @brief Factorial, N!, the number of permutations
     *
     * @tparam N
     * @return constexpr auto
     */
    template <size_t N> constexpr auto Factorial() {
        if constexpr (N <= 1) {
            return std::integral_constant<size_t, 1U>{};
        } else {
            return std::integral_constant<size_t, N * Factorial<N - 1>()>{};
        }
    }

    /**
     * @brief SJT permutation by adjacent transposition (less efficiency)
     *
     * @tparam Container
     * @param perm
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> auto SJT(Container& perm) -> cppcoro::generator<Container&> {
        const auto n = perm.size();
        for (size_t i : ecgen::SJT_gen(n)) {
            co_yield perm;
            auto temp = perm[i];  // swap
            perm[i] = perm[i + 1];
            perm[i + 1] = temp;
        }
    }

    /**
     * @brief Ehr permutation by star transposition (less efficiency)
     *
     * @tparam Container
     * @param perm
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> auto Ehr(Container& perm) -> cppcoro::generator<Container&> {
        const auto n = perm.size();
        co_yield perm;
        for (size_t i : ecgen::Ehr_gen(n)) {
            auto temp = perm[0];  // swap
            perm[0] = perm[i];
            perm[i] = temp;
            co_yield perm;
        }
    }

}  // namespace ecgen
