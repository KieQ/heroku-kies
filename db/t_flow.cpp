#include <pqxx/pqxx>
#include <iostream>

void insertRequest(std::string ip){
    try{
        const char *url = std::getenv("DATABASE_URL");
        if (url == nullptr){
            url = "dbname = testdb user = postgres password = cohondob hostaddr = 127.0.0.1 port = 5432";
        }

        pqxx::connection C(url);
        if (C.is_open()){
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        }
        else{
            std::cout << "Can't open database" << std::endl;
            return;
        }
        C.disconnect();
    }
    catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return;
    }
}