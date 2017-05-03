// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef MEASUREMENT_KIT_COMMON_FMAP_HPP
#define MEASUREMENT_KIT_COMMON_FMAP_HPP

#include <algorithm>
#include <functional>
#include <vector>

namespace mk {

// See <http://programmers.stackexchange.com/a/170474>
template <typename A, typename B>
std::vector<B> fmap(std::vector<A> i, std::function<B(A)> f) {
    std::vector<B> o;
    std::transform(i.begin(), i.end(), std::back_inserter(o), f);
    return std::move(o);
}

} // namespace mk
#endif
