// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#define CATCH_CONFIG_MAIN
#include "../src/libmeasurement_kit/ext/catch.hpp"

#include "../src/libmeasurement_kit/dns/system_resolver.hpp"

using namespace mk;
using namespace mk::dns;

static const char *null_inet_ntop(int, const void *, char *, socklen_t) {
    return nullptr;
}

static int null_getaddrinfo(const char *, const char *, const struct addrinfo *,
                            struct addrinfo **) {
    return EAI_FAIL;
}

TEST_CASE("the system resolver can handle a getaddrinfo error") {
    loop_with_initial_event([]() {
        system_resolver<null_getaddrinfo>(
            "IN", "A", "www.neubot.org",
            [](Error e, Var<Message>) {
                REQUIRE(e == NonRecoverableFailureError());
                break_loop();
            },
            {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver can handle a inet_ntop error") {
    loop_with_initial_event([]() {
        system_resolver<getaddrinfo, null_inet_ntop>(
            "IN", "A", "neubot.org",
            [](Error e, Var<Message>) {
                REQUIRE(e == InetNtopFailureError());
                break_loop();
            },
            {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver can handle an unsupported class") {
    loop_with_initial_event([]() {
        system_resolver("CS", "A", "neubot.org",
                        [](Error e, Var<Message>) {
                            REQUIRE(e == UnsupportedClassError());
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver can handle an unsupported query type") {
    loop_with_initial_event([]() {
        system_resolver("IN", "NS", "neubot.org",
                        [](Error e, Var<Message>) {
                            REQUIRE(e == UnsupportedTypeError());
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

#ifdef ENABLE_INTEGRATION_TESTS

TEST_CASE("the system resolver returns an error with an invalid_site") {
    loop_with_initial_event([]() {
        system_resolver("IN", "A", "invalid_site",
                        [](Error e, Var<Message>) {
                            REQUIRE(
                                e == HostOrServiceNotProvidedOrNotKnownError());
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver is able to resolve an ipv4 address") {
    loop_with_initial_event([]() {
        system_resolver("IN", "A", "www.neubot.org",
                        [](Error e, Var<Message> message) {
                            REQUIRE(!e);
                            REQUIRE(message->answers.size() == 1);
                            REQUIRE(message->answers[0].ipv4 ==
                                    "130.192.16.172");
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver is able to resolve an ipv6 address") {
    loop_with_initial_event([]() {
        system_resolver(
            "IN", "AAAA", "ooni.torproject.org",
            [](Error e, Var<Message> message) {
                REQUIRE(!e);
                REQUIRE(message->answers.size() > 0);
                auto found = false;
                for (auto answer : message->answers) {
                    /*
                     * Note: mapped IP address added because that is the reply
                     * received from Politecnico di Torino DNS.
                     */
                    if (answer.ipv6 == "2001:858:2:2:aabb::563b:1e28" or
                        answer.ipv6 == "2001:858:2:2:aabb:0:563b:1e28" or
                        answer.ipv6 == "::ffff:154.35.132.70") {
                        found = true;
                    }
                }
                REQUIRE(found);
                break_loop();
            },
            {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver can handle errors with a CNAME query") {
    loop_with_initial_event([]() {
        system_resolver("IN", "CNAME", "invalid",
                        [](Error e, Var<Message>) {
                            REQUIRE(e
                                == HostOrServiceNotProvidedOrNotKnownError());
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE(
    "the system resolver doesn't resolve the canonical name with A query") {
    loop_with_initial_event([]() {
        system_resolver("IN", "A", "ipv4.google.com",
                        [](Error e, Var<Message> message) {
                            REQUIRE(!e);
                            REQUIRE(message->answers.size() > 0);
                            REQUIRE(message->answers[0].hostname == "");
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

TEST_CASE("the system resolver is able to resolve the canonical name with "
          "CNAME query") {
    loop_with_initial_event([]() {
        system_resolver("IN", "CNAME", "ipv4.google.com",
                        [](Error e, Var<Message> message) {
                            REQUIRE(!e);
                            REQUIRE(message->answers.size() > 0);
                            REQUIRE(message->answers[0].hostname ==
                                    "ipv4.l.google.com");
                            break_loop();
                        },
                        {}, Reactor::global(), Logger::global());
    });
}

#endif
