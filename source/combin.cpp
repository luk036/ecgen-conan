#include <cppcoro/coroutine.hpp>  // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/combin.hpp>
// #include <vector>  // for vector

namespace ecgen {

    using namespace cppcoro;

    using ret_t = std::pair<size_t, size_t>;

    /**
     * @brief Generate all combinations by homogeneous revolving-door
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto EMK_gen(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (n <= k || k == 0) {
            co_return;
        }
        if (k == 1) {
            for (size_t i = 0; i != n - 1; ++i) {
                co_yield std::make_pair(i, i + 1);
            }
        } else {
            co_yield EMK_gen(n - 1, k);
            co_yield std::make_pair(n - 2, n - 1);
            co_yield EMK_neg(n - 2, k - 1);
            co_yield std::make_pair(k - 2, n - 2);
            co_yield EMK_gen(n - 2, k - 2);
        }
    }

    /**
     * @brief Generate all combinations in reverse order by homogeneous
     * revolving-door
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto EMK_neg(size_t n, size_t k) -> recursive_generator<ret_t> {
        if (n <= k || k == 0) {
            co_return;
        }
        if (k == 1) {
            for (size_t i = n - 1; i != 0; --i) {
                co_yield std::make_pair(i, i - 1);
            }
        } else {
            co_yield EMK_neg(n - 2, k - 2);
            co_yield std::make_pair(n - 2, k - 2);
            co_yield EMK_gen(n - 2, k - 1);
            co_yield std::make_pair(n - 1, n - 2);
            co_yield EMK_neg(n - 1, k);
        }
    }

}  // namespace ecgen
