#pragma once

#include <boost/asio.hpp>
#include <chrono>
#include <functional>
#include <memory>

#include "tools/basic.h"

/// 时钟
class AsyncClock {
   private:
    using Func = std::function<void()>;
    uptr<boost::asio::steady_timer> timer;
    std::chrono::duration<int64_t, std::milli> duration;

   public:
    Func callback;
    AsyncClock();
    void repeat();
    void set_context(boost::asio::io_context &context);
    void set_duration(size_t ms);
    void run();
    void stop();
};
