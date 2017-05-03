// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#define CATCH_CONFIG_MAIN
#include "../src/libmeasurement_kit/ext/catch.hpp"

#include <measurement_kit/common.hpp>

#include <string>

using namespace mk;

TEST_CASE("By default the logger is quiet") {
    std::string buffer;

    mk::on_log([&buffer](uint32_t, const char *s) {
        buffer += s;
        buffer += "\n";
    });

    mk::debug("Antani");
    mk::info("Foo");

    REQUIRE(buffer == "");
}

TEST_CASE("It is possible to make the logger verbose") {
    std::string buffer;

    mk::on_log([&buffer](uint32_t, const char *s) {
        buffer += s;
        buffer += "\n";
    });

    mk::set_verbosity(MK_LOG_INFO);

    mk::debug("Antani");
    mk::info("Foo");

    REQUIRE(buffer == "Foo\n");
}

TEST_CASE("Verbosity can be further increased") {
    std::string buffer;

    mk::on_log([&buffer](uint32_t, const char *s) {
        buffer += s;
        buffer += "\n";
    });

    mk::set_verbosity(MK_LOG_DEBUG);

    mk::debug("Antani");
    mk::info("Foo");

    REQUIRE(buffer == "Antani\nFoo\n");
}

TEST_CASE("We can log on a logfile") {
    {
        Var<Logger> logger = Logger::make();
        logger->set_logfile("logfile.log");
        logger->set_verbosity(MK_LOG_DEBUG);
        logger->on_log(nullptr);
        logger->warn("foo");
        logger->warn("foobar");
        logger->warn("bar");
    }
    std::ifstream file("logfile.log");
    std::string line;
    std::string whole_file;
    while ((std::getline(file, line))) {
        whole_file += line;
        whole_file += "\n";
    }
    REQUIRE(whole_file == "foo\nfoobar\nbar\n");
}

TEST_CASE("A logger without file and without callback works") {
    Var<Logger> logger = Logger::make();
    logger->set_verbosity(MK_LOG_DEBUG);
    logger->on_log(nullptr);
    logger->warn("foo");
    logger->warn("foobar");
}

TEST_CASE("The logger's EOF handler works") {
    auto called = 0;
    {
        Var<Logger> logger = Logger::make();
        logger->on_eof([&]() { called += 1; });
        logger->on_eof([&]() { called += 2; });
    }
    REQUIRE(called == 3);
}

TEST_CASE("We pass MK_LOG_EVENT to logger if event-handler not set") {
    Var<Logger> logger = Logger::make();
    auto called = false;
    logger->on_log([&](uint32_t v, const char *s) {
        REQUIRE(v == (MK_LOG_WARNING|MK_LOG_EVENT));
        REQUIRE(s == std::string{"{}"});
        called = true;
    });
    logger->log(MK_LOG_WARNING|MK_LOG_EVENT, "{}");
    REQUIRE(called);
}

TEST_CASE("We pass MK_LOG_EVENT only to event-handler if it is set") {
    Var<Logger> logger = Logger::make();
    auto log_called = false;
    auto eh_called = false;
    logger->on_log([&](uint32_t, const char *) {
        log_called = true;
    });
    logger->on_event([&](const char *s) {
        REQUIRE(s == std::string{"{}"});
        eh_called = true;
    });
    logger->log(MK_LOG_WARNING|MK_LOG_EVENT, "{}");
    REQUIRE(!log_called);
    REQUIRE(eh_called);
}
