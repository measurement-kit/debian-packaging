// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/report.hpp>

namespace mk {
namespace report {

/* static */ Entry Entry::array() {
    Entry entry;
    // Manually construct an empty array by pushing
    // a value and then removing it
    entry.push_back(17.0);
    entry.erase(0);
    return entry;
}

/* static */ Entry Entry::object() {
    Entry entry;
    // Manually construct an empty object by pushing
    // a value and then removing it
    entry["foo"] = "bar";
    entry.erase("foo");
    return entry;
}

Entry &Entry::operator=(std::initializer_list<nlohmann::json> t) {
    nlohmann::json::operator=(t);
    return *this;
}

void Entry::push_back(Entry value) {
    try {
        nlohmann::json::push_back(value);
    } catch (const std::domain_error &) {
        throw JsonDomainError();
    }
}

void Entry::push_back(std::initializer_list<nlohmann::json> j) {
    try {
        nlohmann::json::push_back(j);
    } catch (const std::domain_error &) {
        throw JsonDomainError();
    }
}

std::string Entry::dump(const int indent) const {
    return nlohmann::json::dump(indent);
}

Entry Entry::parse(const std::string &s) {
  return static_cast<Entry>(nlohmann::json::parse(s));
}

bool Entry::operator==(std::nullptr_t right) const noexcept {
    return static_cast<const nlohmann::json &>(*this) == right;
}

bool Entry::operator!=(std::nullptr_t right) const noexcept {
    return static_cast<const nlohmann::json &>(*this) != right;
}

} // namespace report
} // namespace mk
