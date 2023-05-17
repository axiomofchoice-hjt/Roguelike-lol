#include "AsyncClock.h"

#include <algorithm>

#include "tools/basic.h"

AsyncClock::AsyncClock() {}

void AsyncClock::repeat() {
    if (callback) {
        callback();
    }
    timer->expires_at(std::max(
        timer->expiry() + duration,
        std::chrono::steady_clock::now() + std::chrono::milliseconds(1)));
    timer->async_wait([this](const boost::system::error_code &error) {
        if (!error) {
            repeat();
        } else {
            log_warn("AsyncClock error: {}", error.message());
        }
    });
}

void AsyncClock::set_context(boost::asio::io_context &context) {
    timer = std::make_unique<boost::asio::steady_timer>(context);
}

void AsyncClock::set_duration(size_t ms) {
    duration = std::chrono::milliseconds(ms);
}

void AsyncClock::run() {
    if (!timer || !callback || duration.count() == 0) {
        log_panic("error: XTimer not inited");
    }
    timer->expires_after(duration);
    timer->async_wait([this](const boost::system::error_code &error) {
        if (!error) {
            repeat();
        } else {
            log_warn("AsyncClock error2: {}", error.message());
        }
    });
}

void AsyncClock::stop() { timer->cancel(); }