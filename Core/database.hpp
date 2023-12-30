#pragma once
#include <iostream>
#include <memory>
#include <thread>
#include <pqxx/pqxx>
#include "filelogger.hpp"
#include "user.hpp"

namespace Core {
class Database
{
private:
    static std::mutex s_mutex; // definition outside of class
    std::string m_host;
    std::string m_port;
    std::string m_username;
    std::string m_password;
    std::string m_dbname;
    std::string m_connection_string;
    std::unique_ptr<pqxx::connection> m_connection;

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
        INSERT INTO public.tb_users (username, security_level, password) VALUES('admin', 0, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('supervisor', 1, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_1', 2, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_2', 2, '1234');\
        INSERT INTO public.tb_users (username, security_level, password) VALUES('operator_3', 2, '1234');\
        END $$;";
        public:

                 static Database &Instance(const std::string _host,
                          const std::string _port,
                          const std::string _username,
                          const std::string _password,
                          const std::string _dbname);
    std::unique_ptr<pqxx::connection> connect();
    std::unique_ptr<pqxx::connection> connect(const std::string _connection_string);
    void disconnect();
    pqxx::result commit_query(std::string_view _sql_query);
    void print_query_result(pqxx::result& _result);
    void reset_database();

    void prepare_statements(pqxx::connection &c)
    {
        /* Create */
        c.prepare( "create_user", "INSERT INTO tb_users (username, security_level, \"password\") VALUES($1, $2, $3)");
        /* Read given usernanem*/
        c.prepare( "read_user", "SELECT * FROM tb_users WHERE username = $1");
        /* Update */
        c.prepare( "update_user", "UPDATE tb_users SET username=$2, security_level=$3, \"password\"=$4 WHERE user_id=(SELECT user_id FROM tb_users WHERE  username = $1)");
        /* Delete */
        c.prepare( "delete_user", "DELETE FROM tb_users WHERE username=$1");
        /* Check user's credentials */
        c.prepare( "check_password", "SELECT * FROM tb_users WHERE username = $1 AND password = $2");
        /* table_size - Row count at table */
        c.prepare( "tb_users_size", "SELECT COUNT(*) AS tb_size FROM tb_users");
        /* Read all data at given table */
        c.prepare( "read_all_users", "SELECT * FROM tb_users");
    }

    bool create_user(const std::string_view username, unsigned int security_level, const std::string_view password)
    {
        if(security_level < 2)
        {
            pqxx::work w(*m_connection);
            pqxx::result result = w.exec_prepared("create_user", username, security_level, password );
            w.commit();
            return true;
        }
        else
        {
            return false;
        }
    }
    pqxx::result read_user(const std::string_view username)
    {
        pqxx::work w(*m_connection);
        pqxx::result result = w.exec_prepared("read_user", username);
        w.commit();
        return result;
    }
    pqxx::result update_user(const std::string_view username, const uint8_t security_level, const std::string_view password)
    {
        pqxx::work w(*m_connection);
        pqxx::result result = w.exec_prepared("update_user", username, security_level, password);
        w.commit();
        return result;
    }
    bool delete_user(const std::string_view username, Core::User& system_user)
    {
        if(system_user.get_security_level() == Core::User::eSecurity_level::ADMIN)
        {
            pqxx::work w(*m_connection);
            pqxx::result result = w.exec_prepared("delete_user", username);
            w.commit();
            return true;
        }
        else
        {
            return false;
        }
    }
    //TODO: add encrypt password ´check
    bool check_password(const std::string_view username, const std::string_view password, Core::User& system_user)
    {
        pqxx::work w(*m_connection);
        pqxx::result result = w.exec_prepared("check_password", username, password);
        w.commit();

        if( !result.empty() )
        {
            pqxx::row row = result[0];
            system_user.set_user(row["user_id"].as<int>(),
                                 row["username"].as<std::string>(),
                                 row["password"].as<std::string>(),
                                 row["security_level"].as<int>(),
                                 true );

            return true;
        }
        else
        {
            system_user.reset();
            return false;
        }
    }
    int tb_users_size()
    {
        pqxx::work w(*m_connection);
        pqxx::result result = w.exec_prepared("tb_users_size");
        w.commit();
        pqxx::row row{result[0]};
        return row["tb_size"].as<int>();
    }
    pqxx::result read_all_users()
    {
        pqxx::work w(*m_connection);
        pqxx::result result = w.exec_prepared("read_all_users");
        w.commit();
        return result;
    }

protected:
    explicit Database(const std::string _host,
                      const std::string _port,
                      const std::string _username,
                      const std::string _password,
                      const std::string _dbname);;

    ~Database();;
private:
    // Prevent copying and assignable
    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

public:
    /** Getters and Setters **/
    inline std::string get_connection_string() const { return m_connection_string; }
    inline void set_connection_string(const std::string &newConnection_string) { m_connection_string = newConnection_string; }

    inline std::string get_host() const{ return m_host; }
    inline void set_host(const std::string &newHost){ m_host = newHost; }

    inline std::string get_port() const{ return m_port; }
    inline void set_port(const std::string &newPort){ m_port = newPort; }

    inline std::string get_username() const{ return m_username; }
    inline void set_username(const std::string &newUsername){ m_username = newUsername; }

    inline std::string get_password() const { return m_password; }
    inline void set_password(const std::string &newPassword) { m_password = newPassword; }

    inline std::string get_dbname() const { return m_dbname; }
    inline void set_dbname(const std::string &newDbname){ m_dbname = newDbname; }
};
};//namespace Core
