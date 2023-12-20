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
    std::string get_name() const;
    void set_name(const std::string &newName);

    std::string get_password() const;
    void set_password(const std::string &newPassword);

    eSecurity_level get_security_level() const;
    void set_security_level(eSecurity_level newSecurity_level);

    bool get_user_log_state() const;
    void set_user_log_state(bool newIs_logged);
};
/*Getters and setters*/
inline std::string User::get_name() const { return name; }
inline void User::set_name(const std::string &_name) { name = _name; }

inline std::string User::get_password() const { return password; }
inline void User::set_password(const std::string &_password) { password = _password; }

inline User::eSecurity_level User::get_security_level() const { return security_level; }
inline void User::set_security_level(User::eSecurity_level _security_level) { security_level = _security_level; }

inline bool User::get_user_log_state() const { return is_logged; }
inline void User::set_user_log_state(bool _is_logged) { is_logged = _is_logged; }
