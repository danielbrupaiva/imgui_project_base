#pragma once
#include <iostream>

class User
{
private:
    enum class eSecurity_level{ADMIN,SUPERVISOR,USER};
private:
    std::string name;
    std::string password = "1234";
    eSecurity_level security_level = eSecurity_level::USER;
    bool is_logged = false;
public:
    explicit User(){ std::cout << "User constructor\n"; }
    ~User(){ std::cout << "User destructor\n"; }
    /*Getters and setters*/
    inline bool get_is_logged() const { return is_logged; }
    inline void set_is_logged(bool newIs_logged) { is_logged = newIs_logged; }

    inline std::string get_name() const { return name; }
    inline void set_name(const std::string &_name) { name = _name; }

    inline std::string get_password() const { return password; }
    inline void set_password(const std::string &_password) { password = _password; }

    inline User::eSecurity_level get_security_level() const { return security_level; }
    inline void set_security_level(User::eSecurity_level _security_level) { security_level = _security_level; }
};
