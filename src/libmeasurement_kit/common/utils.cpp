// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <ctype.h>
#include <math.h>

#include <iomanip>
#include <random>

#include <event2/util.h>
#include <openssl/sha.h>

#include "../common/utils_impl.hpp"

namespace mk {

void timeval_now(timeval *tv) {
    if (gettimeofday(tv, nullptr) != 0) {
        throw std::runtime_error("gettimeofday()");
    }
}

double time_now() {
    timeval tv;
    timeval_now(&tv);
    double result = tv.tv_sec + tv.tv_usec / (double)1000000.0;
    return result;
}

void utc_time_now(struct tm *utc) {
    time_t tv;
    tv = time(nullptr);
    gmtime_r(&tv, utc);
}

ErrorOr<std::string> timestamp(const struct tm *t) {
    char result[30];
    if (strftime(result, sizeof(result), "%Y-%m-%d %H:%M:%S", t) == 0) {
        return ValueError();
    }
    return std::string(result);
}

timeval *timeval_init(timeval *tv, double delta) {
    if (delta < 0) {
        return nullptr;
    }
    tv->tv_sec = (time_t)floor(delta);
    tv->tv_usec = (suseconds_t)((delta - floor(delta)) * 1000000);
    return tv;
}

// See <http://stackoverflow.com/questions/440133/>
std::string random_within_charset(const std::string charset, size_t length) {
    if (charset.size() < 1) {
        throw ValueError();
    }
    auto randchar = [&charset]() {
        int rand = 0;
        evutil_secure_rng_get_bytes(&rand, sizeof (rand));
        return charset[rand % charset.size()];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

std::string random_printable(size_t length) {
    static const std::string ascii =
            " !\"#$%&\'()*+,-./"         // before numbers
            "0123456789"                 // numbers
            ":;<=>?@"                    // after numbers
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ" // uppercase
            "[\\]^_`"                    // between upper and lower
            "abcdefghijklmnopqrstuvwxyz" // lowercase
            "{|}~"                       // final
        ;
    return random_within_charset(ascii, length);
}

std::string random_str(size_t length) {
    static const std::string alnum =
            "0123456789"                 // numbers
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ" // uppercase
            "abcdefghijklmnopqrstuvwxyz" // lowercase
        ;
    return random_within_charset(alnum, length);
}

std::string random_str_uppercase(size_t length) {
    static const std::string num_upper =
            "0123456789"                  // numbers
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  // uppercase
        ;
    return random_within_charset(num_upper, length);
}

void dump_settings(Settings &s, std::string prefix, Var<Logger> logger) {
    logger->debug("%s: {", prefix.c_str());
    for (auto pair : s) {
        logger->debug("%s:     %s => %s", prefix.c_str(), pair.first.c_str(),
                      pair.second.c_str());
    }
    logger->debug("%s: }", prefix.c_str());
}

// Adapted from <http://code.activestate.com/recipes/511478/>
double percentile(std::vector<double> v, double percent) {
    if (v.size() <= 0) {
        throw std::runtime_error("zero length vector");
    }
    std::sort(v.begin(), v.end());
    auto pivot = (v.size() - 1) * percent;
    auto pivot_floor = floor(pivot);
    auto pivot_ceil = ceil(pivot);
    if (pivot_floor == pivot_ceil) {
        return v[int(pivot)];
    }
    auto val0 = v[int(pivot_floor)] * (pivot_ceil - pivot);
    auto val1 = v[int(pivot_ceil)] * (pivot - pivot_floor);
    return val0 + val1;
}

// See: <http://stackoverflow.com/questions/2262386/>
std::string sha256_of(std::string input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    constexpr size_t hash_size = sizeof(hash) / sizeof(hash[0]);
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, input.data(), input.size());
    SHA256_Final(hash, &ctx);
    std::stringstream ss;
    for (size_t i = 0; i < hash_size; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0')
           << (unsigned)hash[i];
    }
    return ss.str();
}

ErrorOr<std::vector<char>> slurpv(std::string path) {
    return slurpv_impl<char>(path);
}

ErrorOr<std::string> slurp(std::string path) {
    ErrorOr<std::vector<char>> v = slurpv_impl<char>(path);
    if (!v) {
        return v.as_error();
    }
    std::string s{v->begin(), v->end()};  /* Note that here we make a copy */
    return s;
}

bool startswith(std::string s, std::string p) {
    return s.find(p) == 0;
}

/*-
 *     0 1 2 3 4 5 6
 * s: |f|o|o|b|a|r|
 * p:       |b|a|r|
 *           0 1 2 3
 *
 * s.size() - p.size() = 3
 */
bool endswith(std::string s, std::string p) {
    return s.size() >= p.size() ? s.rfind(p) == (s.size() - p.size()) : false;
}

std::string random_choice(std::vector<std::string> inputs) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(inputs.begin(), inputs.end(), g);
    return inputs[0];
}

std::string randomly_capitalize(std::string input) {
    std::random_device rd;
    std::mt19937 g(rd());
    for (auto &c: input) {
        if (g() % 2 == 0) {
            c = toupper(c);
        } else {
            c = tolower(c);
        }
    }
    return input;
}


} // namespace mk
