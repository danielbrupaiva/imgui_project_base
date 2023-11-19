#pragma once
#include <pqxx/pqxx>
#include "filelogger.h"

class Database
{
    std::string m_host;
    std::string m_port;
    std::string m_username;
    std::string m_password;
    std::string m_dbname;
    std::string m_connection_string;
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
        return connect();
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
    bool commit_query(std::string_view _sql_query)
    {
        PRINT("SQL query");
        auto conn = connect();
        pqxx::result result;

        if(conn.is_open())
        {
           PRINT("Database connected");
           pqxx::work work(conn);
           result = work.exec(_sql_query);
           // check result and treat
           work.commit();

           PRINT("Work commited");
        }
        disconnect(conn);
        return EXIT_SUCCESS;
    }

    bool setup_database()
    {

    }

};
