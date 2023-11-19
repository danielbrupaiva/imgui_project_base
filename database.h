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
    }
    ~Database()
    {/** The destructor of pqxx::connection will close connection automatically.**/
        PRINT("Database handler was destructed");
    }
    pqxx::connection connect()
    {
        PRINT("Connection with database is open");
        return pqxx::connection(m_connection_string);
    }
    pqxx::connection connect(const std::string& _connection_string)
    {
        PRINT("Connection with database is open");
        return pqxx::connection(_connection_string);
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
    bool query(std::string_view _query)
    {
        PRINT("SQL query");
        return EXIT_SUCCESS;
    }
};
