#include "SocketServer.h"

#include "tools/UUID.h"
#include "tools/basic.h"

SocketServer::SocketServer() : context(nullptr) {}

void SocketServer::start(boost::asio::io_context &ctx) {
    if (!receive_callback || !connect_callback || !disconnect_callback) {
        log_panic("socket server start fail");
    }
    context = &ctx;
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
        ctx, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6688));
    accept();
}

void SocketServer::accept() {
    shared<SocketConn> conn = std::make_shared<SocketConn>();
    conn->setContext(*context);
    acceptor->async_accept(
        *conn->socket, [this, conn](const boost::system::error_code &error) {
            if (!error) {
                conn->id = UUID::get();
                log_info("connected, id={}\n", conn->id);
                conn->receive_callback = receive_callback;
                conn->disconnect_callback = [this](u64 id) {
                    disconnect_callback(id);
                    conn_list.erase(
                        std::find_if(conn_list.begin(), conn_list.end(),
                                     [id](const shared<SocketConn> &conn) {
                                         return conn->id == id;
                                     }));
                };
                conn->start();
                conn_list.push_back(conn);

                connect_callback(conn->id);

                accept();
            } else {
                log_error("error: {}", error.message());
            }
        });
}