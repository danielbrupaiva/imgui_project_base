#include "app.h"
#include "database.h"
#include "filelogger.h"
#include "database.h"

std::string TAG = "MAIN";

int main(int, char**)
{
    PRINT("HELLO " + TAG);
    PRINT("APP start");
    App app(ImVec2(1280,720),"ImGUI APP", App::BACKEND::SDL3);
    //Start backend
    Database db{"localhost","5432","imgui","1234","project"};

    std::string sql_query = "CREATE TABLE IF NOT EXISTS tb_users ( \
                            id SERIAL PRIMARY KEY, \
                            username VARCHAR(50) UNIQUE NOT NULL, \
                            security_level INT CHECK (security_level IN (0, 1, 2)) NOT NULL, \
                            password VARCHAR(100) NOT NULL);\
                            INSERT INTO tb_users (username, security_level, password) VALUES('admin', 0, 'admin');\
                            INSERT INTO tb_users (username, security_level, password) VALUES('supervisor', 1, '1234');\
                            INSERT INTO tb_users (username, security_level, password) VALUES('operator 1', 2, '1234');\
                            INSERT INTO tb_users (username, security_level, password) VALUES('operator 2', 2, '1234');\
                            INSERT INTO tb_users (username, security_level, password) VALUES('operator 3', 2, '1234');";

    db.commit_query(sql_query);

    PRINT("Do-While ");
    do {//IMGUI code
        app.begin();{
        }app.render();
    } while (!app.get_is_app_done());

    PRINT("APP stop");
    return EXIT_SUCCESS;
}




