#include <cstdlib>
#include "cinatra.hpp"
using namespace cinatra;

int main() {
    auto port = std::getenv("PORT");
    std::size_t max_thread_num = std::thread::hardware_concurrency();
    http_server server(max_thread_num);
    server.listen("0.0.0.0", port); //maybe segment fault when there is not PORT set
    server.set_http_handler<GET, POST>("/", [](request& req, response& res) {
        res.set_status_and_content(status_type::ok, "hello world");
    });

    server.run();
    return 0;
}