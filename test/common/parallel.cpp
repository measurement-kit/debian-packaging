// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#define CATCH_CONFIG_MAIN
#include "../src/libmeasurement_kit/ext/catch.hpp"

#include <measurement_kit/common.hpp>

using namespace mk;

TEST_CASE("mk::parallel() works as expected for empty vector") {
    mk::parallel({}, [](Error error) {
        REQUIRE((error == NoError()));
    });
}

TEST_CASE("mk::parallel() works as expected with all successes") {
    loop_with_initial_event([&]() {
        std::vector<Continuation<Error>> input;
        for (size_t i = 0; i < 16; ++i) {
            input.push_back([=](Callback<Error> callback) {
                call_later(i * 0.1, [=]() {
                    callback(NoError());
                });
            });
        }
        mk::parallel(input, [](Error error) {
            REQUIRE((error == NoError()));
            for (auto &sub_error: error.child_errors) {
                REQUIRE((*sub_error == NoError()));
            }
            break_loop();
        });
    });
}

TEST_CASE("mk::parallel() works as expected with some failures") {
    loop_with_initial_event([&]() {
        std::vector<Continuation<Error>> input;
        for (size_t i = 0; i < 16; ++i) {
            input.push_back([=](Callback<Error> callback) {
                call_later(i * 0.1, [=]() {
                    if ((i % 2) == 0) {
                        callback(MockedError());
                    } else {
                        callback(NoError());
                    }
                });
            });
        }
        mk::parallel(input, [](Error error) {
            REQUIRE((error == ParallelOperationError()));
            REQUIRE((error.child_errors.size() == 16));
            for (size_t i = 0; i < error.child_errors.size(); ++i) {
                if ((i % 2) == 0) {
                    REQUIRE((*error.child_errors[i] == MockedError()));
                } else {
                    REQUIRE((*error.child_errors[i] == NoError()));
                }
            }
            break_loop();
        });
    });
}

TEST_CASE("mk::parallel() works as expected with all failures") {
    loop_with_initial_event([&]() {
        std::vector<Continuation<Error>> input;
        for (size_t i = 0; i < 16; ++i) {
            input.push_back([=](Callback<Error> callback) {
                call_later(i * 0.1, [=]() {
                    callback(MockedError());
                });
            });
        }
        mk::parallel(input, [](Error error) {
            REQUIRE((error == ParallelOperationError()));
            for (auto &sub_error: error.child_errors) {
                REQUIRE((*sub_error == MockedError()));
            }
            break_loop();
        });
    });
}

