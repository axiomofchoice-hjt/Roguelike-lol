#include "SocketConn.h"

#include "tools/IntSerialize.h"
#include "tools/basic.h"

SocketConn::SocketConn() : id(ULLONG_MAX), checked(false), sending(false) {}

SocketConn::~SocketConn() { log_info("disconnected, id={}", id); }

void SocketConn::setContext(boost::asio::io_context &context) {
    socket = std::make_unique<boost::asio::ip::tcp::socket>(context);
}

void SocketConn::receive() {
    shared<std::string> s = std::make_shared<std::string>(456, 0);
    shared<SocketConn> ptr = shared_from_this();
    socket->async_read_some(
        boost::asio::buffer(*s),
        [ptr, s](const boost::system::error_code &error, size_t n) {
            if (!error) {
                s->resize(n);
                ptr->recvBuf += *s;
                if (!ptr->checked) {
                    if (ptr->recvBuf.size() > 100) {
                        ptr->recvBuf.clear();
                    };
                }
                while (IntSerialize::completed(ptr->recvBuf)) {
                    if (!ptr->checked) {
                        auto s = IntSerialize::popFront(ptr->recvBuf);
                        if (s ==
                            "ED3l)3V@eAh*0(Lk7nBgAmdwJA4QpWVgexay(9CyjmwzE3!"
                            "Om1XQ#+8Ks15") {
                            ptr->checked = true;
                            log_info("checked id={}", ptr->id);
                        } else {
                            ptr->socket->close();
                        }
                    } else {
                        ptr->receive_callback(
                            *ptr, IntSerialize::popFront(ptr->recvBuf));
                    }
                }
                ptr->receive();
            } else {
                // log_info("receive error: {}", error.message());
                ptr->disconnect_callback(ptr->id);
            }
        });
}

void SocketConn::send(std::string s) {
    log_info("send length={}", s.length());
    IntSerialize::putSize(s);
    shared<std::string> s1 = std::make_shared<std::string>(std::move(s));
    sending = true;
    shared<SocketConn> ptr = shared_from_this();
    socket->async_write_some(
        boost::asio::buffer(*s1),
        [ptr, s1](const boost::system::error_code &error, size_t n) {
            ptr->sending = false;
            if (!error) {
            } else {
                log_warn("async_write error: {}", error.message());
            }
        });
}
