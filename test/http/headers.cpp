// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#define CATCH_CONFIG_MAIN
#include "../src/libmeasurement_kit/ext/catch.hpp"

#include <measurement_kit/http.hpp>

using namespace mk;

TEST_CASE("HTTP headers search is case insensitive") {
    http::Headers headers;
    headers["Location"] = "https://www.x.org/";
    REQUIRE((headers["locAtion"] == "https://www.x.org/"));
}
