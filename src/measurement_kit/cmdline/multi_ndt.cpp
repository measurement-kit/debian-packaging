// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include "../cmdline/cmdline.hpp"
#include <measurement_kit/ext/json.hpp>
#include <measurement_kit/nettests.hpp>
#include <measurement_kit/ndt.hpp>

#include <string.h>
#include <stdio.h>

#include <iostream>

namespace mk {
namespace cmdline {
namespace multi_ndt {

using namespace mk::nettests;

static const char *kv_usage =
        "usage: measurement_kit multi_ndt [-v] [-m metro]\n";

int main(const char *, int argc, char **argv) {

    MultiNdtTest test;
    int ch;
    while ((ch = mkp_getopt(argc, argv, "m:v")) != -1) {
        switch (ch) {
        case 'm':
            test.set_options("mlabns/policy", "metro");
            test.set_options("mlabns/metro", mkp_optarg);
            break;
        case 'v':
            test.increase_verbosity();
            break;
        default:
            std::cout << kv_usage;
            exit(1);
        }
    }
    argc -= mkp_optind;
    argv += mkp_optind;

    test
        .on_progress([](double prog, const char *s) {
            printf("Progress: %.1f%%: %s\n", prog * 100.0, s);
        })
        .on_event([](const char *s) {
            nlohmann::json doc = nlohmann::json::parse(s);
            if (doc["type"] != "download-speed") {
                return;
            }
            double elapsed = doc["elapsed"][0];
            std::string elapsed_unit = doc["elapsed"][1];
            double speed = doc["speed"][0];
            std::string speed_unit = doc["speed"][1];
            printf("%8.2f %s %10.2f %s\n", elapsed, elapsed_unit.c_str(),
                   speed, speed_unit.c_str());
        })
        .on_entry([](std::string s) {
            nlohmann::json doc = nlohmann::json::parse(s);
            auto simple = doc["test_keys"]["simple"];
            printf("\nTest summary\n");
            printf("------------\n");
            std::string fastest = simple["fastest_test"];
            double download = simple["download"];
            double ping = simple["ping"];
            printf("Fastest test: %s\n", fastest.c_str());
            printf("Download speed: %.2f kbit/s\n", download);
            printf("Ping: %.2f ms\n", ping);
            printf("\nAdvanced info (from single stream test)\n");
            printf("---------------------------------------\n");
            auto adv = doc["test_keys"]["advanced"];
            double AvgRTT = adv["avg_rtt"];
            double MinRTT = adv["min_rtt"];
            double MaxRTT = adv["max_rtt"];
            printf("RTT (avg/min/max): %.1f/%.1f/%.1f ms\n",
                   AvgRTT, MinRTT, MaxRTT);
            double CongestionLimited = adv["congestion_limited"];
            double ReceiverLimited = adv["receiver_limited"];
            double SenderLimited = adv["sender_limited"];
            printf("Limited (congestion/receiver/sender): %.2f/%.2f/%.2f\n",
                   CongestionLimited, ReceiverLimited, SenderLimited);
            double OutOfOrder = adv["out_of_order"];
            printf("OutOfOrder: %lf (%.3lf%%)\n",
                    OutOfOrder, OutOfOrder * 100.0);
            unsigned long MSS = adv["mss"];
            printf("MSS: %lu byte\n", MSS);
            unsigned long FastRetran = adv["fast_retran"];
            unsigned long Timeouts = adv["timeouts"];
            printf("Congestion: FastRetran: %lu; Timeo: %lu\n",
                   FastRetran, Timeouts);
            double PacketLoss = adv["packet_loss"];
            printf("Loss: %lf (%.3lf%%)\n", PacketLoss, PacketLoss * 100.0);
            printf("\n");
        })
        .set_options("geoip_country_path", "GeoIP.dat")
        .set_options("geoip_asn_path", "GeoIPASNum.dat")
        .run();

    return 0;
}

} // namespace multi_ndt
} // namespace cmdline
} // namespace mk
