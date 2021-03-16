#include <pqxx/pqxx>
#include <iostream>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
namespace DB{

    void insertRequest(std::string ip){
        try{
            const char *url = std::getenv("DATABASE_URL");
            if (url == nullptr){
                url = "dbname = testdb user = postgres password = cohondob hostaddr = 127.0.0.1 port = 5432";
            }

            pqxx::connection conn(url);
            if (conn.is_open()){
                SPDLOG_INFO("open database successful, name={}",conn.dbname());
            }
            else{
                SPDLOG_WARN("something wrong with openning the database");
                return;
            }


            pqxx::work worker(conn);
            auto result = worker.exec0(R"SQL(CREATE TABLE IF NOT EXISTS t_flow (id SERIAL PRIMARY KEY, request_time TIMESTAMP WITHOUT TIME ZONE DEFAULT (now() AT TIME ZONE 'utc'), ip_addr VARCHAR(30) DEFAULT '<UNKNOWN>'))SQL","create table");
            for(auto col=0;col<result.columns();col++){
                SPDLOG_DEBUG("{}", result.column_name(col));
            }

            result = worker.exec(fmt::format(R"SQL(INSERT INTO t_flow(ip_addr) VALUES ('{}'))SQL", ip));
            SPDLOG_DEBUG("{}", result.affected_rows);
            worker.commit();

            conn.disconnect();
        }
        catch (const std::exception &e){
            SPDLOG_ERROR("{}",e.what());
            return;
        }
    }

}