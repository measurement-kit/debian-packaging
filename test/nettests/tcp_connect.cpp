// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifdef ENABLE_INTEGRATION_TESTS

#define CATCH_CONFIG_MAIN
#include "../src/libmeasurement_kit/ext/catch.hpp"

#include "../nettests/utils.hpp"

using namespace mk::nettests;

TEST_CASE("Synchronous tcp-connect test") {
    test::nettests::make_test<TcpConnectTest>("hosts.txt")
        .set_options("port", "80")
        .run();
}

TEST_CASE("Asynchronous tcp-connect test") {
    test::nettests::run_async(
        test::nettests::make_test<TcpConnectTest>("hosts.txt")
            .set_options("port", "80")
    );
}

#else
int main() {}
#endif
