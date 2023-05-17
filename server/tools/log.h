#pragma once

#include <fmt/core.h>
#include <glog/logging.h>

#define log_info(...) (LOG(INFO) << fmt::format(__VA_ARGS__))
#define log_warn(...) (LOG(WARNING) << fmt::format(__VA_ARGS__))
#define log_error(...) (LOG(ERROR) << fmt::format(__VA_ARGS__))
#define log_panic(...) (LOG(FATAL) << fmt::format(__VA_ARGS__))
