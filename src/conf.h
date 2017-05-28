#pragma once

#include <string>
#include <map>

class conf
{
public:
    conf(const std::string& conf_path);
    conf();
 
    const std::string get_database_file() const { std::string value; get_key_value("Database", value); return value; }
    const std::string get_log_file()      const { std::string value; get_key_value("Log", value); return value; }
    const std::string get_authentication_address_and_port() const;
    const std::string get_user_mangement_address_and_port() const;
    const std::string get_password_manager_address_and_port() const;
    const std::string get_server_certificate_file() const { std::string value; get_key_value("ServerCertificate", value); return value; }
    const std::string get_server_key_file() const { std::string value; get_key_value("ServerKey", value); return value; }
    const std::string get_user_server_certificate_file() const { std::string value; get_key_value("UserServerCertificate", value); return value; }
    const std::string get_user_server_key_file() const { std::string value; get_key_value("UserServerKey", value); return value; }
    const std::string get_server_ca_file() const { std::string value; get_key_value("ServerCA", value); return value; }
    const std::string get_public_key_filename() const { std::string value; get_key_value("PublicEncryptionKey", value); return value; }
    const std::string get_private_key_filename() const { std::string value; get_key_value("PrivateEncryptionKey", value); return value; }
    const std::string get_pid_filename() const { std::string value; get_key_value("PID", value); return value; }

    bool get_key_value(const std::string& key, std::string& value) const
    {
        auto it = m_Values.find(key);
        if(it != m_Values.end())
        {
            value = it->second;
            return true;
        }
        return false;
    }
private:
    std::map<std::string, std::string> m_Values;
};
