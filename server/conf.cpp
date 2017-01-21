#include "conf.h"

#include <iostream>
#include <fstream>
#include <sstream>

conf::conf(const std::string& conf_path)
: conf()
{
    std::ifstream file(conf_path, std::ifstream::in);
    std::string line;
    while(std::getline(file, line))
    {
        std::string key;
        std::string value;
        {
            std::istringstream is_line(line);
            if(std::getline(is_line, key, '#') && key.size() != line.size())
            {
                continue;
            }
        }
        {
            std::istringstream is_line(line);
            if(std::getline(is_line, key, ' ') && std::getline(is_line, value) && key.size() != line.size() && value.size() != line.size())
            {
                std::cout << key << "=" << value << std::endl;
                m_Values[key] = value;
            }
        }
    }
}

conf::conf()
{
    m_Values["Database"] = "pswmgr.db";
    m_Values["Log"] = "pswmgr.log";
    m_Values["PasswordManagerAddress"] = "0.0.0.0";
    m_Values["PasswordManagerPort"] = "5050";
    m_Values["UserManagementAddress"] = "127.0.0.1";
    m_Values["UserManagementPort"] = "6060";
}

const std::string conf::get_user_mangement_address_and_port() const
{
    std::stringstream ss;
    std::string address;
    std::string port;
    get_key_value("UserManagementAddress", address);
    get_key_value("UserManagementPort", port);
    ss << address << ":" << port;
    return ss.str();
}

const std::string conf::get_password_manager_address_and_port() const
{
    std::stringstream ss;
    std::string address;
    std::string port;
    get_key_value("PasswordManagerAddress", address);
    get_key_value("PasswordManagerPort", port);
    ss << address << ":" << port;
    return ss.str();

}
