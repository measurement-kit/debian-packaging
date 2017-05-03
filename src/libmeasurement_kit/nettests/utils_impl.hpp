// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef SRC_LIBMEASUREMENT_KIT_NETTESTS_UTILS_IMPL_HPP
#define SRC_LIBMEASUREMENT_KIT_NETTESTS_UTILS_IMPL_HPP

#include "../nettests/utils.hpp"

#include <measurement_kit/ooni.hpp>

#include <fstream>
#include <random>

namespace mk {
namespace nettests {

static Var<std::istream> open_file_(const std::string &path) {
    return Var<std::istream>{new std::ifstream{path}};
}

static bool readline_(std::istream &input, std::string &line) {
    return static_cast<bool>(std::getline(input, line));
}

static void randomize_input_(std::deque<std::string> &inputs) {
    // See http://en.cppreference.com/w/cpp/algorithm/shuffle
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(inputs.begin(), inputs.end(), g);
}

template <MK_MOCK(open_file_), MK_MOCK(readline_), MK_MOCK(randomize_input_)>
ErrorOr<std::deque<std::string>> process_input_filepaths_impl(
    const bool &needs_input, const std::list<std::string> &input_filepaths,
    const std::string &probe_cc, const Settings &options, Var<Logger> logger,
    std::function<void(const std::string &)> on_open_error,
    std::function<void(const std::string &)> on_io_error) {
    std::deque<std::string> inputs;
    if (needs_input) {
        if (input_filepaths.size() <= 0) {
            logger->warn("at least an input file is required");
            return ooni::MissingRequiredInputFileError();
        }
        /*
         * Note: in general the snippet below is not
         * so good because it does not work for UTF-8
         * and the like but here we are converting
         * country codes which are always ASCII.
         */
        std::string probe_cc_lowercase = "";
        std::transform(probe_cc.begin(),
                       probe_cc.end(),
                       probe_cc_lowercase.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        for (auto input_filepath : input_filepaths) {
            input_filepath = std::regex_replace(input_filepath,
                                                std::regex{R"(\$\{probe_cc\})"},
                                                probe_cc_lowercase);
            Var<std::istream> input_generator = open_file_(input_filepath);
            if (!input_generator->good()) {
                logger->warn("cannot open input file");
                if (!!on_open_error) {
                    on_open_error(input_filepath);
                }
                continue;
            }
            std::string next_input;
            while ((readline_(*input_generator, next_input))) {
                inputs.push_back(next_input);
            }
            if (!input_generator->eof()) {
                logger->warn("I/O error reading input file");
                if (!!on_io_error) {
                    on_io_error(input_filepath);
                }
                continue;
            }
        }
        if (inputs.size() <= 0) {
            logger->warn("no specified input file could be read");
            return ooni::CannotReadAnyInputFileError();
        }
        ErrorOr<bool> shuffle =
            options.get_noexcept<bool>("randomize_input", true);
        if (!shuffle) {
            logger->warn("invalid 'randomize_input' option");
            return shuffle.as_error();
        }
        if (*shuffle) {
            randomize_input_(inputs);
        }
    } else {
        // Empty string to call main() just once
        inputs.push_back("");
    }
    return inputs;
}

} // namespace nettests
} // namespace mk
#endif
