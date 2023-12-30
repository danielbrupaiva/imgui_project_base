#pragma once
#include <iostream>
#include <map>

namespace Core {
class User
{
public:
    enum class eSecurity_level{ADMIN,SUPERVISOR,USER};
private:
    int id;
    std::string name;
    std::string password;
    eSecurity_level security_level = eSecurity_level::USER;
    bool is_logged = false;
public:
    explicit User(){ std::cout << "User constructor\n"; }
    ~User(){ std::cout << "User destructor\n"; }

    void set_user(const int _id,
                  const std::string& _name,
                  const std::string& _password,
                  const eSecurity_level _security_level,
                  const bool _is_logged = false )
    {
        set_id(_id);
        set_name(_name);
        set_password(_password);
        set_security_level(_security_level);
        set_is_logged(_is_logged);
    }
    void set_user(const int _id,
                  const std::string& _name,
                  const std::string& _password,
                  const unsigned int _security_level,
                  const bool _is_logged = false )
    {
        set_id(_id);
        set_name(_name);
        set_password(_password);
        set_security_level(_security_level);
        set_is_logged(_is_logged);
    }
    void reset(){
        set_id(0);
        set_name("");
        set_password("");
        set_security_level(User::eSecurity_level::USER);
        set_is_logged(false);
    }
    /*Getters and setters*/
    inline bool get_is_logged() const { return is_logged; }
    inline void set_is_logged(bool newIs_logged) { is_logged = newIs_logged; }

    inline std::string get_name() const { return name; }
    inline void set_name(const std::string &_name) { name = _name; }

    inline std::string get_password() const { return password; }
    inline void set_password(const std::string &_password) { password = _password; }

    inline User::eSecurity_level get_security_level() const { return security_level; }
    inline void set_security_level(User::eSecurity_level _security_level) { security_level = _security_level; }
    inline void set_security_level(unsigned int _security_level)
    {
        std::map<int, User::eSecurity_level> security_level_map = {
            { 0, User::eSecurity_level::ADMIN     },
            { 1, User::eSecurity_level::SUPERVISOR},
            { 2, User::eSecurity_level::USER      }};

        security_level = security_level_map[_security_level];
    }

    inline int get_id() const { return id; }
    inline void set_id(int newId) { id = newId; }
};
};//namespace Core
