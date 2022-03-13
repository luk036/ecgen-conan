#pragma once

#include <cppcoro/recursive_generator.hpp>

namespace ecgen {

    /**
     * @brief Generate reflexed Gray code
     *
     * @param n
     * @return cppcoro::recursive_generator<size_t>
     */
    extern auto BRGC_gen(size_t n) -> cppcoro::recursive_generator<size_t>;

    /**
     * @brief Binary Reflexed Gray Code (less efficiency)
     *
     * @tparam Container
     * @param n
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> auto BRGC(size_t n) -> cppcoro::generator<Container&> {
        auto lst = Container(n, 0);
        co_yield lst;
        for (size_t i : BRGC_gen(n)) {
            lst[i] = 1 - lst[i];  // flip
            co_yield lst;
        }
    }

}  // namespace ecgen