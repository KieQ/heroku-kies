#include <cstdlib>
#include "cinatra.hpp"
#include <spdlog/spdlog.h>
#include <fmt/ranges.h>
#include <boost/algorithm/string.hpp>
#include "db/t_flow.hpp"
using namespace cinatra;


int main() {
    const char* port = std::getenv("PORT");
    if(port == nullptr){
        port = "8080";
    }
    SPDLOG_INFO("Program starts running. The port is {}",port);
    std::size_t max_thread_num = std::thread::hardware_concurrency();
    http_server server(max_thread_num);
    server.listen("0.0.0.0", port); //maybe segment fault when there is not PORT set
    server.set_http_handler<GET, POST>("/", [](request& req, response& res) {
        DB::insertRequest(req.get_conn<NonSSL>()->remote_address());
        res.set_status_and_content(status_type::ok, req.get_conn<NonSSL>()->remote_address());
    });

    server.run();
    return 0;
}