#pragma once
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <string_view>

namespace fmtlog {
void output(std::string_view message);

template<typename... Args>
void log(const char* file, int line, std::string_view fmt, Args... args) {
  output(fmt::format("{}:{}: {}", file, line, fmt::format(fmt::runtime(fmt), args...)));
}
}

#define LOG_INFO(fmt_str, ...) fmtlog::log(__FILE_NAME__, __LINE__, fmt_str, ##__VA_ARGS__)