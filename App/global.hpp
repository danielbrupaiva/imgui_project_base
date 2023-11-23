#pragma once
#include "string"

struct User
{
    std::string name;
    std::string password;
    std::string security_level;
    bool is_logged = false;
};
class GlobalVars
{
    User user;
};
