#include "../include/admin.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <fstream>
#include <iostream>

Admin::Admin(std::shared_ptr<SqlConnector> sql_connector) : SQL_connector_(sql_connector) {
   username_hashed_ = SQL_connector_->getUsername();
   password_hashed_ = SQL_connector_->getPassword();
}

std::string Admin::computeHash(const std::string &credential) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;

    OpenSSL_add_all_digests();

    md = EVP_get_digestbyname("sha256");

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, credential.c_str(), credential.length());
    EVP_DigestFinal_ex(mdctx, hash, &hashLen);
    EVP_MD_CTX_free(mdctx);

    std::string hashedCredential;
    char hexBuffer[3]; 
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hexBuffer, "%02x", hash[i]);
        hashedCredential.append(hexBuffer);
    }
    return hashedCredential;
}

void Admin::saveCredentials(const std::string &username, const std::string &password)
{
   username_hashed_ = computeHash(username);
   password_hashed_ = computeHash(password);
   SQL_connector_->setCredentials(username_hashed_, password_hashed_);
}

bool Admin::checkUsername(const std::string &username) {
    return computeHash(username) == username_hashed_;
}

bool Admin::checkPassword(const std::string &password) {
    return computeHash(password) == password_hashed_;
}