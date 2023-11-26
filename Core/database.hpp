#pragma once
#include <pqxx/pqxx>
#include "filelogger.hpp"

namespace Core {

class Database
{
    std::string m_host;
    std::string m_port;
    std::string m_username;
    std::string m_password;
    std::string m_dbname;
    std::string m_connection_string;

    std::string initial_setup_query =
    "CREATE EXTENSION IF NOT EXISTS pgcrypto;\
     DO $$ \
         BEGIN \
             IF EXISTS (SELECT 1 FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'tb_users') THEN \
                 DROP TABLE public.tb_users; \
             END IF;\
     CREATE TABLE IF NOT EXISTS public.tb_users ( \
            user_id SERIAL PRIMARY KEY, \
            username VARCHAR(50) UNIQUE NOT NULL, \
            security_level INT CHECK (security_level IN (0, 1, 2)) NOT NULL, \
            password VARCHAR(100) NOT NULL);\
     INSERT INTO public.tb_users (username, security_level, password) VALUES('admin', 0, 'admin');\
     INSERT INTO public.tb_users (username, security_level, password) VALUES('supervisor', 1, '1234');\
     INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_1', 2, '1234');\
     INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_2', 2, '1234');\
     INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_3', 2, '1234');\
     END $$;";

public:
    Database(const std::string _host,
             const std::string _port,
             const std::string _username,
             const std::string _password,
             const std::string _dbname)
        : m_host{_host}, m_port{_port}, m_username{_username}, m_password{_password}, m_dbname{_dbname}
    {
        PRINT("Database handler constructed");
        m_connection_string = "host="+_host+" port="+_port+" user="+_username+" password="+_password+" dbname="+_dbname;

        //Check if tables exists if not create
        commit_query(initial_setup_query);
    }
    ~Database()
    {/** The destructor of pqxx::connection will close connection automatically.**/
        PRINT("Database handler was destructed");
    }
    pqxx::connection connect()
    {
        return pqxx::connection(m_connection_string);
    }
    pqxx::connection connect(const std::string& _connection_string)
    {
        m_connection_string = _connection_string;
        return pqxx::connection(m_connection_string);
    }
    bool disconnect(pqxx::connection& _conn)
    {
        if(_conn.is_open())
        {
           _conn.close();
           PRINT("Connection with database was closed");
           return EXIT_SUCCESS;
        }
        else
        {
           PRINT("Connection with database was not opened");
           return EXIT_FAILURE;
        }
    }
    pqxx::result commit_query(std::string_view _sql_query)
    {
        PRINT("SQL query");
        pqxx::connection conn = connect();
        pqxx::result result;
        if(conn.is_open())
        {
           PRINT("Database connected");
           pqxx::work work(conn);
           result = work.exec(_sql_query);
           work.commit();
           PRINT("Work commited");
        }
        disconnect(conn);
        return result;
    }
    void print_query_result(pqxx::result& _result)
    {
        // Using ranged-based for loop and modern iterators to print the result
        for (const auto& row : _result) {
           for (const auto& field : row) {
               std::cout << field.c_str() << " ";
           }
           std::cout << std::endl;
        }
    }
    //TODO
    // Access other columns similarly using their names
    void process_result(pqxx::result& _result)
    {
        for (const auto& row : _result) {
           std::cout << "ID: " << row["user_id"].as<int>() << ", Name: " << row["username"].as<std::string>() << std::endl;

        }
    }
};

}
