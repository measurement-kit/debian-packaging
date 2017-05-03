// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef SRC_LIBMEASUREMENT_KIT_NDT_RUN_IMPL_HPP
#define SRC_LIBMEASUREMENT_KIT_NDT_RUN_IMPL_HPP

#include "../ndt/internal.hpp"
#include <measurement_kit/mlabns.hpp>

namespace mk {
namespace ndt {

using Phase = void (*)(Var<Context>, Callback<Error>);
using Cleanup = void (*)(Var<Context>, Error);

template <Phase connect, Phase send_login, Phase recv_and_ignore_kickoff,
          Phase wait_in_queue, Phase recv_version, Phase recv_tests_id,
          Phase run_tests, Phase recv_results_and_logout, Phase wait_close,
          Cleanup disconnect_and_callback>
void run_with_specific_server_impl(Var<Entry> entry, std::string address, int port,
                                   Callback<Error> callback, Settings settings,
                                   Var<Reactor> reactor, Var<Logger> logger) {

    // Note: this implementation is a template because that allows us to
    // easily change the functions implementing each phase of the protocol
    // thus enabling quick experimentation and unit testing.

    Var<Context> ctx(new Context);
    ctx->address = address;
    ctx->callback = callback;
    ctx->entry = entry;
    ctx->logger = logger;
    ctx->reactor = reactor;
    ctx->port = port;
    ctx->settings = settings;

    // If the user has not configured the test_suite to run, default with
    // running the download and the uploade phases of the test.
    ctx->test_suite |= settings.get("test_suite", TEST_C2S|TEST_S2C);

    dump_settings(ctx->settings, "ndt", ctx->logger);

    // Initialize entry keys that may be set by this routine
    (*ctx->entry)["client_resolver"] = nullptr; /* Set later by parent */
    (*ctx->entry)["failure"] = nullptr;
    (*ctx->entry)["server_address"] = address;
    (*ctx->entry)["server_port"] = port;
    (*ctx->entry)["server_version"] = nullptr;
    (*ctx->entry)["summary_data"] = Entry::object();
    (*ctx->entry)["test_c2s"] = Entry::array();
    (*ctx->entry)["test_s2c"] = Entry::array();
    (*ctx->entry)["test_suite"] = ctx->test_suite;

    // The following code implements this sequence diagram:
    // https://raw.githubusercontent.com/wiki/ndt-project/ndt/NDTProtocol.images/ndt_10.png

#define TRAP_ERRORS(e)                                                         \
    if (e) {                                                                   \
        disconnect_and_callback(ctx, e);                                       \
        return;                                                                \
    }

    connect(ctx, [ctx](Error err) {
        TRAP_ERRORS(err);
        ctx->logger->progress(0.1, "Connected to test server");

        send_login(ctx, [ctx](Error err) {
            TRAP_ERRORS(err);
            ctx->logger->progress(0.2, "Logged in with test server");

            recv_and_ignore_kickoff(ctx, [ctx](Error err) {
                TRAP_ERRORS(err);
                ctx->logger->progress(0.3, "Waiting for our turn in queue");

                wait_in_queue(ctx, [ctx](Error err) {
                    TRAP_ERRORS(err);
                    ctx->logger->progress(0.4, "Authorized to run test");

                    recv_version(ctx, [ctx](Error err) {
                        TRAP_ERRORS(err);
                        ctx->logger->progress(0.5, "Got server version");

                        recv_tests_id(ctx, [ctx](Error err) {
                            TRAP_ERRORS(err);
                            ctx->logger->progress(0.6,
                                "Got authorized tests identifiers");

                            run_tests(ctx, [ctx](Error err) {
                                TRAP_ERRORS(err);
                                // Progress printed by run_tests()

                                recv_results_and_logout(ctx, [ctx](Error err) {
                                    TRAP_ERRORS(err);
                                    ctx->logger->progress(0.8,
                                        "Received results from server");

                                    wait_close(ctx, [ctx](Error err) {
                                        ctx->logger->progress(0.9,
                                            "Connection with server closed");
                                        disconnect_and_callback(ctx, err);
                                    });
                                });
                            });
                        });
                    });
                });
            });
        });
    });

#undef TRAP_ERRORS
}

template <MK_MOCK(run_with_specific_server),
          MK_MOCK_AS(mlabns::query, mlabns_query)>
void run_impl(Var<Entry> entry, Callback<Error> callback, Settings settings,
              Var<Reactor> reactor, Var<Logger> logger) {
    ErrorOr<int> port = settings.get_noexcept<int>("port", NDT_PORT);
    if (!port) {
        callback(InvalidPortError(port.as_error()));
        return;
    }
    std::string address = settings.get<std::string>("address", "");
    if (address != "") {
        run_with_specific_server(entry, address, *port, callback, settings,
                                 reactor, logger);
        return;
    }
    mlabns_query(settings.get<std::string>("mlabns_tool_name", "ndt"),
                 [=](Error err, mlabns::Reply reply) {
                     if (err) {
                         callback(MlabnsQueryError(err));
                         return;
                     }
                     run_with_specific_server(entry, reply.fqdn, *port, callback,
                                              settings, reactor, logger);
                 },
                 settings, reactor, logger);
}

} // namespace mk
} // namespace ndt
#endif
