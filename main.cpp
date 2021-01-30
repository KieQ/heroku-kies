#include <cstdlib>
#include "cinatra.hpp"
#include <spdlog/spdlog.h>
using namespace cinatra;

int main() {
    auto port = std::getenv("PORT");
    SPDLOG_INFO("Program starts running. The port is {}",port);
    std::size_t max_thread_num = std::thread::hardware_concurrency();
    http_server server(max_thread_num);
    server.listen("0.0.0.0", port); //maybe segment fault when there is not PORT set
    server.set_http_handler<GET, POST>("/", [](request& req, response& res) {
        res.set_status_and_content(status_type::ok, R"(<html>
<head>
</head>
<body>
<h1 style="color:red">Hello World</h1>
<img src="https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fattachments.gfan.com%2Fforum%2Fattachments2%2Fday_110406%2F1104062007632ac27fcb66edc7.jpg&refer=http%3A%2F%2Fattachments.gfan.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg?sec=1614614386&t=371f7734ca6d7a12a9261bac641824a6">
</body>
</html>)");
    });

    server.run();
    return 0;
}