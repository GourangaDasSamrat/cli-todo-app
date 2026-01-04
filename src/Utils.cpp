#include "../include/Utils.h"

#include <algorithm>
#include <cctype>
#include <regex>

bool Utils::isValidInteger(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) return false;
    }

    return true;
}

int Utils::stringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (...) {
        return -1;
    }
}

Priority Utils::stringToPriority(const std::string& str) {
    std::string lower = toLowerCase(str);

    if (lower == "high" || lower == "h" || lower == "3") {
        return Priority::HIGH;
    } else if (lower == "medium" || lower == "m" || lower == "2") {
        return Priority::MEDIUM;
    } else {
        return Priority::LOW;
    }
}

std::string Utils::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";

    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::string Utils::toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool Utils::isValidDate(const std::string& date) {
    std::regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return std::regex_match(date, datePattern);
}
