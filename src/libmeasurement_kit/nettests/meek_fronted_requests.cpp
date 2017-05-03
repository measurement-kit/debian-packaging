// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/nettests.hpp>
#include <measurement_kit/ooni.hpp>

namespace mk {
namespace nettests {

MeekFrontedRequestsTest::MeekFrontedRequestsTest() : BaseTest() {
    runnable.reset(new MeekFrontedRequestsRunnable);
    runnable->test_name = "meek_fronted_requests";
    runnable->test_version = "0.0.1";
    runnable->needs_input = true;
}

void MeekFrontedRequestsRunnable::main(std::string input, Settings options,
                                Callback<Var<report::Entry>> cb) {
    ooni::meek_fronted_requests(input, options, cb, reactor, logger);
}

} // namespace nettests
} // namespace mk
