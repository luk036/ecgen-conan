#include <ecgen/perm.hpp>
#include <numeric>  // for iota
#include <vector>

namespace ecgen {

    /**
     * @brief Generate all permutations by adjacent transposition
     *
     * @param n
     * @return cppcoro::generator<size_t>
     */
    auto SJT_gen(size_t n) -> cppcoro::generator<size_t> {
        /** Generate the swaps for the Steinhaus-Johnson-Trotter algorithm.*/
        if (n == 2) {
            co_yield 0;
            co_yield 0;  // tricky part: return to the original list
            co_return;
        }

        auto&& gen = SJT_gen(n - 1);
        for (auto it = gen.begin(); it != gen.end(); ++it) {
            for (size_t i = n - 1; i != 0; --i) {  // downward
                co_yield i - 1;
            }
            co_yield 1 + *it;
            for (size_t i = 0; i != n - 1; ++i) {  // upward
                co_yield i;
            }
            co_yield *(++it);  // tricky part
        }
    }

    /**
     * @brief Generate all permutations by star transposition
     *
     * @param n
     * @return cppcoro::generator<size_t>
     */
    auto Ehr_gen(size_t n) -> cppcoro::generator<size_t> {
        auto c = std::vector<size_t>(n + 1, 0);  // c[0] is never used
        auto b = std::vector<size_t>(n, 0);
        std::iota(b.begin(), b.end(), 0U);  // 0, 1, ... n-1

        while (true) {
            size_t k = 1;
            do {
                if (c[k] == k) {
                    c[k] = 0;
                    k += 1;
                }
            } while (c[k] >= k);
            if (k == n) {
                break;
            }
            c[k] += 1;
            co_yield b[k];
            for (size_t i = 1, j = k - 1; i < j; ++i, --j) {
                std::swap(b[i], b[j]);
            }
        }
    }

}  // namespace ecgen
