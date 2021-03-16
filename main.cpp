#include <cstdlib>
#include <cinatra.hpp>
#include <spdlog/spdlog.h>
#include "handler/handler.hpp"
using namespace cinatra;


void bind_http(http_server& server){
    server.set_http_handler<GET,POST>("/",handler::home_page);
}

int main() {
    const char* port = std::getenv("PORT");
    if(port == nullptr){
        port = "8080";
    }
    SPDLOG_INFO("Program starts running. The port is {}",port);
    std::size_t max_thread_num = std::thread::hardware_concurrency();
    http_server server(max_thread_num);
    server.listen("0.0.0.0", port); //maybe segment fault when there is not PORT set
    bind_http(server);

    server.run();
    return 0;
}