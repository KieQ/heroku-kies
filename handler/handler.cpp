#include "handler.hpp"
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include "../db/t_flow.hpp"

using namespace cinatra;


namespace handler{

void home_page(request& req, response& res){
    SPDLOG_INFO("start home page, ip={}", req.get_header_value("X-Forwarded-Host"));
    DB::record_request(std::string(req.get_header_value("X-Forwarded-Host")));
    res.set_status_and_content(status_type::ok,fmt::format("hello {}",req.get_header_value("X-Forwarded-Host")));
}


    
} // namespace handler


