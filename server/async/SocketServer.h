#pragma once

#include <memory>

#include "SocketConn.h"
#include "tools/basic.h"

/// Socket 服务器
class SocketServer {
   public:
    uptr<boost::asio::ip::tcp::acceptor> acceptor;
    boost::asio::io_context *context;

    std::function<void(u64)> connectCallback;
    std::function<void(u64)> disconnect_callback;
    std::function<void(u64, std::string)> receive_callback;
    std::vector<shared<SocketConn>> conn_list;
    SocketServer();
    void start(boost::asio::io_context &ctx);
    void accept();
};
