#include <cassert>
#include <cctype>
#include <cstdio>
#include <ecgen/set_partition.hpp>
#include <functional>
#include <utility>

namespace ecgen {

    using namespace cppcoro;
    using ret_t = std::pair<size_t, size_t>;

    inline auto Move(size_t x, size_t y) -> recursive_generator<ret_t> {
        co_yield std::make_pair(x, y);
    }

    // The lists S(n,k,0) and S(n,k,1) satisfy the following properties.
    // 1. Successive RG sequences differ in exactly one position.
    // 2. first(S(n,k,0)) = first(S(n,k,1)) = 0^{n-k}0123...(k-1)
    // 3. last(S(n,k,0)) = 0^{n-k}12...(k-1)0
    // 4. last(S(n,k,1)) = 012...(k-1)0^{n-k}
    // Note that first(S'(n,k,p)) = last(S(n,k,p))

    auto GEN0_even(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto NEG0_even(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto GEN1_even(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto NEG1_even(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto GEN0_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto NEG0_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto GEN1_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
    auto NEG1_odd(size_t n, size_t k) -> recursive_generator<ret_t>;

    /**
     * @brief Set the partition gen object
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto set_partition_gen(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k % 2 == 0)
            co_yield GEN0_even(n, k);
        else
            co_yield GEN0_odd(n, k);
    }

    /**
     * @brief S(n,k,0) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto GEN0_even(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 0 && k < n) {
            co_yield GEN0_odd(n - 1, k - 1);  // S(n-1, k-1, 0).(k-1)
            co_yield Move(n - 1, k - 1);
            co_yield GEN1_even(n - 1, k);  // S(n-1, k, 1).(k-1)
            co_yield Move(n, k - 2);
            co_yield NEG1_even(n - 1, k);  // S'(n-1, k, 1).(k-2)

            for (size_t i = k - 2; i > 1; i -= 2) {
                co_yield Move(n, i - 1);
                co_yield GEN1_even(n - 1, k);  // S(n-1, k, 1).i
                co_yield Move(n, i - 2);
                co_yield NEG1_even(n - 1, k);  // S'(n-1, k, 1).(i-1)
            }
        }
    }

    /**
     * @brief S'(n, k, 0) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto NEG0_even(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 0 && k < n) {
            for (size_t i = 1; i < k - 2; i += 2) {
                co_yield GEN1_even(n - 1, k);  // S(n-1, k, 1).(i-1)
                co_yield Move(n, i);
                co_yield NEG1_even(n - 1, k);  // S'(n-1, k, 1).i
                co_yield Move(n, i + 1);
            }

            co_yield GEN1_even(n - 1, k);  // S(n-1, k, 1).(k-2)
            co_yield Move(n, k - 1);
            co_yield NEG1_even(n - 1, k);  // S(n-1, k, 1).(k-1)
            co_yield Move(n - 1, 0);
            co_yield NEG0_odd(n - 1, k - 1);  // S(n-1, k-1, 1).(k-1)
        }
    }

    /**
     * @brief S(n, k, 1) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto GEN1_even(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 0 && k < n) {
            co_yield GEN1_odd(n - 1, k - 1);
            co_yield Move(k, k - 1);
            co_yield NEG1_even(n - 1, k);
            co_yield Move(n, k - 2);
            co_yield GEN1_even(n - 1, k);

            for (size_t i = k - 2; i > 1; i -= 2) {
                co_yield Move(n, i - 1);
                co_yield NEG1_even(n - 1, k);
                co_yield Move(n, i - 2);
                co_yield GEN1_even(n - 1, k);
            }
        }
    }

    /**
     * @brief S'(n, k, 1) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto NEG1_even(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 0 && k < n) {
            for (size_t i = 1; i < k - 2; i += 2) {
                co_yield NEG1_even(n - 1, k);
                co_yield Move(n, i);
                co_yield GEN1_even(n - 1, k);
                co_yield Move(n, i + 1);
            }

            co_yield NEG1_even(n - 1, k);
            co_yield Move(n, k - 1);
            co_yield GEN1_even(n - 1, k);
            co_yield Move(k, 0);
            co_yield NEG1_odd(n - 1, k - 1);
        }
    }

    /**
     * @brief S(n, k, 0) odd k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto GEN0_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 1 && k < n) {
            co_yield GEN1_even(n - 1, k - 1);
            co_yield Move(k, k - 1);
            co_yield NEG1_odd(n - 1, k);

            for (size_t i = k - 1; i > 1; i -= 2) {
                co_yield Move(n, i - 1);
                co_yield GEN1_odd(n - 1, k);
                co_yield Move(n, i - 2);
                co_yield NEG1_odd(n - 1, k);
            }
        }
    }

    /**
     * @brief S'(n, k, 0) odd k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto NEG0_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 1 && k < n) {
            for (size_t i = 1; i < k - 1; i += 2) {
                co_yield GEN1_odd(n - 1, k);
                co_yield Move(n, i);
                co_yield NEG1_odd(n - 1, k);
                co_yield Move(n, i + 1);
            }

            co_yield GEN1_odd(n - 1, k);
            co_yield Move(k, 0);
            co_yield NEG1_even(n - 1, k - 1);
        }
    }

    /**
     * @brief S(n, k, 1) odd k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto GEN1_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 1 && k < n) {
            co_yield GEN0_even(n - 1, k - 1);
            co_yield Move(n - 1, k - 1);
            co_yield GEN1_odd(n - 1, k);

            for (size_t i = k - 1; i > 1; i -= 2) {
                co_yield Move(n, i - 1);
                co_yield NEG1_odd(n - 1, k);
                co_yield Move(n, i - 2);
                co_yield GEN1_odd(n - 1, k);
            }
        }
    }

    /**
     * @brief S'(n, k, 1) odd k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto NEG1_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (k > 1 && k < n) {
            for (size_t i = 1; i < k - 1; i += 2) {
                co_yield NEG1_odd(n - 1, k);
                co_yield Move(n, i);
                co_yield GEN1_odd(n - 1, k);
                co_yield Move(n, i + 1);
            }

            co_yield NEG1_odd(n - 1, k);
            co_yield Move(n - 1, 0);
            co_yield NEG0_even(n - 1, k - 1);
        }
    }

}  // namespace ecgen
