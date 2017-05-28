#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <memory>

#include <grpc++/grpc++.h>

#include "pswmgr.grpc.pb.h"

#include "conf.h"
#include "db.h"
#include "auth_token_info.h"
#include "token_auth_metadata_processor.h"

class PasswordManagerServer final : public pswmgr::PasswordManager::Service, public pswmgr::UserManagement::Service, public pswmgr::Authentication::Service
{
public:
    static PasswordManagerServer* Instance();
    bool Init(conf& conf_file);
    bool Run(conf& conf_file);
    void Destroy();

    bool IsStrongPassword(const std::string& password) const;

protected:
    PasswordManagerServer();
    ~PasswordManagerServer();

private:
    bool InitPid(conf& conf_file);
    void DestroyPid();

private:
    //Authentication Service
    grpc::Status Authenticate(grpc::ServerContext* context, const pswmgr::AuthenticationRequest* request, pswmgr::AuthReply* response) override;

    //Password Service
    grpc::Status ListPasswords(grpc::ServerContext* context, const pswmgr::SimpleRequest* request, pswmgr::PasswordList* response) override;
    grpc::Status AddPassword(grpc::ServerContext* context, const pswmgr::PasswordEntry* request, pswmgr::SimpleReply* response) override;
    grpc::Status DeletePassword(grpc::ServerContext* context, const pswmgr::PasswordEntry* request, pswmgr::SimpleReply* response) override;
    grpc::Status ModifyPassword(grpc::ServerContext* context, const pswmgr::PasswordEntry* request, pswmgr::SimpleReply* response) override;

    // User Management Service
    grpc::Status CreateUser(grpc::ServerContext* context, const pswmgr::UserCreationRequest* request, pswmgr::UserCreationReply* response) override;
    grpc::Status UpdateUserPassword(grpc::ServerContext* context, const pswmgr::UserPasswordUpdateRequest* request, pswmgr::SimpleReply* response) override;

private:
    static PasswordManagerServer* ms_Instance;

    bool m_IsRunning;
    db* m_Database;
    std::map<std::string, std::shared_ptr<auth_token_info>> m_AuthTokens;
    
    std::shared_ptr<TokenAuthMetadataProcessor> m_TokenAuthMetadataProcessor;

    std::string m_PublicKey;
    std::string m_PrivateKey;
    std::string pid_filename;
};
