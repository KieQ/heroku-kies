#include <pqxx/pqxx>
#include <iostream>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
namespace DB{

    void record_request(std::string ip){

        SPDLOG_INFO("insert request, ip={}",ip);
        try{
            const char *url = std::getenv("DATABASE_URL");
            if (url == nullptr){
                SPDLOG_ERROR("can not get database url");
            }
            SPDLOG_DEBUG("DATABASE_URL={}",url);

            pqxx::connection conn(url);
            if (!conn.is_open()){
                SPDLOG_WARN("something wrong with openning the database");
                return;
            }

            pqxx::work worker(conn);
            auto result = worker.exec0(R"SQL(CREATE TABLE IF NOT EXISTS t_flow (id SERIAL PRIMARY KEY, request_time TIMESTAMP WITHOUT TIME ZONE DEFAULT (now() AT TIME ZONE 'utc'), ip_addr VARCHAR(30) DEFAULT '<UNKNOWN>'))SQL","create table");
            result = worker.exec(fmt::format(R"SQL(INSERT INTO t_flow(ip_addr) VALUES ('{}'))SQL", ip));
            
            SPDLOG_INFO("{}", result.affected_rows());
            worker.commit();

            conn.disconnect();
        }
        catch (const std::exception &e){
            SPDLOG_ERROR("{}",e.what());
            return;
        }
    }

}