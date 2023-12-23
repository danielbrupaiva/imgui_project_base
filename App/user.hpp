#pragma once
#include <iostream>

class User
{
public:
    enum class eSecurity_level{ADMIN,SUPERVISOR,USER};
private:
    std::string name;
    std::string password;
    eSecurity_level security_level = eSecurity_level::USER;
    bool is_logged = false;
public:
    explicit User(){ std::cout << "User constructor\n"; }
    ~User(){ std::cout << "User destructor\n"; }

    void set_user(const std::string& _name,
                  const std::string& _password,
                  const bool _is_logged = false,
                  const eSecurity_level _security_level = eSecurity_level::USER )
    {
        set_name(_name);
        set_password(_password);
        set_security_level(_security_level);
        set_is_logged(_is_logged);
    }
    void reset(){
        set_name("");
        set_password("");
        set_security_level(eSecurity_level::USER);
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
};
