#include <ctime>
#include <filesystem>
#include <string>

#include "async/AsyncClock.h"
#include "async/SocketConn.h"
#include "async/SocketServer.h"
#include "proto/Scene.pb.h"
#include "scene/Scene.h"
#include "tools/basic.h"

int main(int argc, char **argv) {
    // std::filesystem::create_directory("log");
    // FLAGS_alsologtostderr = true;
    // FLAGS_log_dir = "log";
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    log_info("run");
    try {
        boost::asio::io_context io_context;

        AsyncClock async_clock;
        async_clock.set_context(io_context);

        Scene scene;

        SocketServer server;
        server.connect_callback = [&scene](u64 id) {
            scene.add_entity(id, EntityProto_EntityType_Player);
        };
        server.receive_callback = [&scene](SocketConn &conn, std::string msg) {
            MessageProto proto;
            proto.ParseFromString(msg);
            scene.receive(conn, proto);
        };
        server.disconnect_callback = [&scene](u64 id) {
            scene.find(id)->removed = true;
        };
        server.start(io_context);

        async_clock.set_context(io_context);
        constexpr size_t duration = 8;
        async_clock.set_duration(duration);
        async_clock.callback = [&server, &scene]() {
            scene.update(duration / 1000.f);

            if (scene.update_count % 4 == 0) {
                SceneProto proto = scene.proto();

                for (shared<SocketConn> conn : server.conn_list) {
                    if (conn->checked) {
                        scene.others_to_proto(proto, conn->id);

                        std::string message;
                        proto.SerializeToString(&message);

                        conn->send(message);
                    }
                }
            }
        };
        async_clock.run();

        io_context.run();

    } catch (std::exception &e) {
        log_error("exception: {}", e.what());
    }

    return 0;
}