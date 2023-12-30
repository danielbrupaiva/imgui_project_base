#include "database.hpp"

std::mutex Core::Database::s_mutex;

Core::Database &Core::Database::Instance(const std::string _host, const std::string _port, const std::string _username, const std::string _password, const std::string _dbname)
{
    PRINT("Database instance created");
    std::lock_guard<std::mutex> lock(s_mutex);
    static Database* s_instance = new Database(_host,_port,_username,_password,_dbname);
    return *s_instance;
}

std::unique_ptr<pqxx::connection> Core::Database::connect()
{
    try {
        auto _connection = std::make_unique<pqxx::connection>(m_connection_string);
        if(_connection->is_open())
        {
            PRINT("Connection with "+static_cast<std::string>( _connection->dbname())+" database was opened");
            return std::move(_connection);
        }else
        {
            PRINT("Fail to connect at database");
            _connection = nullptr;
            return _connection;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

std::unique_ptr<pqxx::connection> Core::Database::connect(const std::string _connection_string)
{
    set_connection_string(_connection_string);
    return connect();
}

void Core::Database::disconnect()
{
    if(m_connection->is_open())
    {
        m_connection->close();
        PRINT("Connection closed")
    }
}

pqxx::result Core::Database::commit_query(std::string_view _sql_query)
{
    PRINT("Commit SQL query");
    pqxx::result result;
    try {
        if(m_connection->is_open())
        {
            pqxx::work work(*m_connection);
            result = work.exec(_sql_query);
            work.commit();
        }
        return result;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Core::Database::print_query_result(pqxx::result &_result)
{
    // Using ranged-based for loop and modern iterators to print the result
    for (const auto& row : _result) {
        for (const auto& field : row) {
            std::cout << field.c_str() << " ";
        }
        std::cout << std::endl;
    }
}

void Core::Database::reset_database()
{
    commit_query(initial_setup_query);
}

Core::Database::Database(const std::string _host, const std::string _port, const std::string _username, const std::string _password, const std::string _dbname)
    : m_host{_host}, m_port{_port}, m_username{_username}, m_password{_password}, m_dbname{_dbname}
{
    PRINT("Database constructor");
    set_connection_string("host="+_host+" port="+_port+" user="+_username+" password="+_password+" dbname="+_dbname);
    m_connection = connect();
    prepare_statements(*m_connection);
}

Core::Database::~Database()
{/** The destructor of pqxx::connection will close connection automatically.**/
    PRINT("Database destructor");
    disconnect();
}
