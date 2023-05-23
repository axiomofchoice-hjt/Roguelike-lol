#pragma once

#include <boost/asio.hpp>

#include "tools/basic.h"

/// Socket 连接
class SocketConn : public std::enable_shared_from_this<SocketConn> {
   public:
    std::string recvBuf;
    std::function<void(SocketConn &, std::string)> receive_callback;
    std::function<void(u64)> disconnect_callback;
    uptr<boost::asio::ip::tcp::socket> socket;
    u64 id;
    bool checked;
    bool sending;

    SocketConn();
    ~SocketConn();
    void setContext(boost::asio::io_context &context);
    void receive();
    void send(std::string s);
    void start() {
        if (!receive_callback || !disconnect_callback) {
            log_panic("socket conn start fail");
        }
        receive();
    }
};
